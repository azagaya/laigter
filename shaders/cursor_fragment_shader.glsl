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
varying vec2 texCoord;
uniform vec3 lightColor;
uniform sampler2D tex;
uniform vec2 pixelSize;
uniform bool selected;
uniform float scale;
uniform bool pixelated;
uniform float zoom;

void main()
{

  vec2 texCoords = texCoord;
  if (pixelated)
  {

    vec2 d = vec2(float(1.0 / pixelSize.x), float(1.0 / pixelSize.y));
    vec2 coords = texCoords * d;

    texCoords = (floor(coords+0.5)) / d;
  }

  vec4 color = texture2D(tex, texCoords);
  float alpha = color.a;

  float l = length(texCoord - 0.75);

//  if (l < 0.5 && l > 0.5 - 1.0 * (pixelSize.x / scale / zoom))
//    color = vec4(0.6, 0.6, 1.0, 1.0);
//  if (l < 0.5 - 2.0 * (pixelSize.x / scale / zoom) &&
//      l > 0.5 - 3.0 * (pixelSize.x / scale / zoom))
//    color = vec4(0.0, 0.0, 0.4, 1.0);

  gl_FragColor = vec4(color);
}
