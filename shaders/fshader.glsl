/*
 * Laigter: an automatic map generator for lighting effects.
 * Copyright (C) 2019  Pablo Ivan Fonovich
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * Contact: azagaya.games@gmail.com
 */
#version 110
#define DIFFUSE 0

struct lightSource
{
  vec3 lightPos;
  vec3 lightColor;
  float diffIntensity;
  vec3 specColor;
  float specIntensity;
  float specScatter;
};

uniform float zoom;

uniform lightSource Light[32];
uniform int lightNum;

varying vec2 texCoord;
varying vec3 FragPos;

uniform sampler2D diffuse;
uniform sampler2D normalMap;
uniform sampler2D parallaxMap;
uniform sampler2D specularMap;
uniform sampler2D occlussionMap;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform bool light;
uniform vec3 lightColor;
uniform vec3 specColor;
uniform float diffIntensity;
uniform float specIntensity;
uniform float specScatter;
uniform float ambientIntensity;
uniform vec3 ambientColor;
uniform vec2 ratio;
uniform float textureScale;
uniform bool parallax;
uniform bool pixelated;
uniform bool toon;
uniform bool selected;
uniform bool useAlpha;
uniform float height_scale;
uniform float rotation_angle;
uniform int pixelsX, pixelsY;
uniform int view_mode;
uniform float blend_factor;

uniform vec2 coordOffset;
uniform vec3 outlineColor;

uniform vec4 rect;

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir);
mat4 rotationZ(float angle);

void main()
{

  if (selected &&
      (texCoord.x <= rect.x + 1.0 / float(pixelsX) / textureScale / ratio.x / zoom||
       texCoord.x >= rect.y - 1.0 / float(pixelsX) / textureScale / ratio.x / zoom ||
       texCoord.y <= rect.z + 1.0 / float(pixelsY) / textureScale / ratio.y / zoom ||
       texCoord.y >= rect.w - 1.0 / float(pixelsY) / textureScale / ratio.y / zoom))
  {
    gl_FragColor.xyz = 1.0 - outlineColor;
    gl_FragColor.a = 0.5;
    return;
  }

  vec2 dis;
  vec3 viewDir = normalize(viewPos - FragPos);

  vec2 texCoords = texCoord + coordOffset;

  if (pixelated)
  {

    vec2 d = vec2(float(pixelsX), float(pixelsY)) * ratio;
    vec2 coords = texCoords * d;

    texCoords = (floor(coords) / d + 0.5 / d);
  }
  if (parallax)
  {
    texCoords = ParallaxMapping(texCoords, viewDir);

    if (texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 ||
        texCoords.y < 0.0)
      discard;
  }

  texCoords *= ratio;

  vec4 tex = texture2D(diffuse, texCoords);

  bool blend = true;

  if (view_mode == 0)
  {
    gl_FragColor = texture2D(diffuse, texCoords);
    blend = false;
  }
  else if (view_mode == 1)
  {
    gl_FragColor = texture2D(normalMap, texCoords);
  }
  else if (view_mode == 2)
  {
    gl_FragColor = texture2D(specularMap, texCoords);
  }
  else if (view_mode == 3)
  {
    gl_FragColor = texture2D(parallaxMap, texCoords);
  }
  else if (view_mode == 4)
  {
    gl_FragColor = texture2D(occlussionMap, texCoords);
  }
  else if (view_mode == 5)
  {
    blend = false;
    vec3 normal =
        normalize(vec4(texture2D(normalMap, texCoords).xyz * 2.0 - 1.0, 0.0) * rotationZ(rotation_angle)).xyz;
    vec3 specMap = texture2D(specularMap, texCoords).xyz;
    vec4 l_color = vec4(0.0);
    float occlusion = texture2D(occlussionMap, texCoords).x;

    for (int i = 0; i < lightNum; i++)
    {
      vec3 lightDir =
          normalize(Light[i].lightPos - vec3(FragPos.xy, 0.0));

      vec3 reflectDir = reflect(-lightDir, normal);

      float nl = dot(viewDir, reflectDir);
      float spec =
          pow(max(dot(viewDir, reflectDir), 0.0), Light[i].specScatter);
      if (toon)
      {
        spec = smoothstep(0.005, 0.01, spec);
      }
      vec3 specular =
          Light[i].specIntensity * spec * Light[i].specColor * specMap;

      nl = dot(lightDir, normal);
      float diff = max(nl, 0.0);
      if (toon)
      {
        diff = smoothstep(0.495, 0.505, diff);
      }
      vec3 diffuse = diff * Light[i].lightColor * Light[i].diffIntensity;

      l_color += vec4(diffuse, 1.0) + vec4(specular, 1.0);
    }
//    if (toon)
//    {
//      occlusion = smoothstep(0.495, 0.505, occlusion);
//    }
    l_color = tex * (l_color + vec4(ambientColor, 1.0) * ambientIntensity *
                     occlusion);
    l_color.a = tex.a;
    gl_FragColor = l_color;
  }
  if (useAlpha)
  {
      gl_FragColor.a = tex.a;
  }
  if (blend)
  {
    float src_a = tex.a * blend_factor;
    gl_FragColor = (tex*src_a + gl_FragColor*(1.0-src_a));
  }
}

mat4 rotationZ(in float angle)
{
  return mat4(cos(angle), -sin(angle), 0, 0, sin(angle), cos(angle), 0, 0, 0,
              0, 1, 0, 0, 0, 0, 1);
}

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{
  // number of depth layers

  const float minLayers = 10.0;
  const float maxLayers = 100.0;
  float numLayers =
      mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));
  // calculate the size of each layer
  float layerDepth = 1.0 / numLayers;
  // depth of current layer
  float currentLayerDepth = 0.0;
  // the amount to shift the texture coordinates per layer (from vector P)
  vec2 P = viewDir.xy * height_scale;
  vec2 deltaTexCoords = P / numLayers;

  // get initial values
  vec2 currentTexCoords = texCoords;
  float currentDepthMapValue =
      texture2D(parallaxMap, currentTexCoords * ratio).r;
  vec2 finalTexCoords;
  while (currentLayerDepth < currentDepthMapValue)
  {
    // shift texture coordinates along direction of P
    currentTexCoords.y += deltaTexCoords.y;
    currentTexCoords.x -= deltaTexCoords.x;
    // get depthmap value at current texture coordinates
    currentDepthMapValue =
        texture2D(parallaxMap, currentTexCoords * ratio).r;
    // get depth of next layer
    currentLayerDepth += layerDepth;
  }

  // get texture coordinates before collision (reverse operations)
  vec2 prevTexCoords = vec2(currentTexCoords.x + deltaTexCoords.x,
                            currentTexCoords.y - deltaTexCoords.y);

  // get depth after and before collision for linear interpolation
  float afterDepth = currentDepthMapValue - currentLayerDepth;
  float beforeDepth = texture2D(parallaxMap, prevTexCoords * ratio).r -
      currentLayerDepth + layerDepth;

  // interpolation of texture coordinates
  float weight = afterDepth / (afterDepth - beforeDepth);
  finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);
  return finalTexCoords;
}
