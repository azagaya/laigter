#version 130


in vec2 texCoord;
in vec3 FragPos;
out vec4 FragColor;

uniform sampler2D texture;
uniform sampler2D normalMap;
uniform sampler2D parallaxMap;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform bool light;
uniform vec3 lightColor;
uniform float diffIntensity;
uniform float ambientIntensity;
uniform vec3 ambientColor;
uniform vec2 ratio;
uniform bool parallax;
uniform bool pixelated;
uniform float height_scale;
uniform int pixelsX, pixelsY;

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir);

void main()
{
    vec3 viewDir = normalize(viewPos-FragPos);

    float dx = 0.5/pixelsX/ratio.x;
    float dy = 0.5/pixelsY/ratio.y;

    vec2 texCoords = texCoord;
    if (pixelated){
        texCoords = vec2(dx * round(texCoord.x / dx),
                         dy * round(texCoord.y / dy));
    }
    if (parallax){
        texCoords = ParallaxMapping(texCoords,  viewDir);

        if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
            discard;
    }

    texCoords *= ratio;

    vec3 normal = normalize(texture2D(normalMap,texCoords).xyz*2-1);
    vec3 lightDir = normalize(lightPos - vec3(FragPos.xy,0.0));
    float diff = max(dot(normal,lightDir),0.0);
    vec3 diffuse = diff * lightColor * diffIntensity;
    vec4 tex = texture2D(texture,texCoords);
    vec4 l_color = tex*(vec4(diffuse,tex.w)+vec4(ambientColor,1.0)*ambientIntensity);
    if (light){
        FragColor = l_color;
    }else{
        FragColor = tex;
    }
}

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{
    // number of depth layers

    const float minLayers = 100.0;
    const float maxLayers = 320.0;
    float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));
    // calculate the size of each layer
    float layerDepth = 1.0 / numLayers;
    // depth of current layer
    float currentLayerDepth = 0.0;
    // the amount to shift the texture coordinates per layer (from vector P)
    vec2 P = viewDir.xy * height_scale;
    vec2 deltaTexCoords = P / numLayers;


    // get initial values
    vec2  currentTexCoords     = texCoords;
    float currentDepthMapValue = texture2D(parallaxMap, currentTexCoords*ratio).r;
    vec2 finalTexCoords;
    while(currentLayerDepth < currentDepthMapValue)
    {
        // shift texture coordinates along direction of P
        currentTexCoords.y += deltaTexCoords.y;
        currentTexCoords.x -= deltaTexCoords.x;
        // get depthmap value at current texture coordinates
        currentDepthMapValue = texture2D(parallaxMap, currentTexCoords*ratio).r;
        // get depth of next layer
        currentLayerDepth += layerDepth;

    }

    // get texture coordinates before collision (reverse operations)
    vec2 prevTexCoords = vec2(currentTexCoords.x + deltaTexCoords.x, currentTexCoords.y - deltaTexCoords.y);

    // get depth after and before collision for linear interpolation
    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture2D(parallaxMap, prevTexCoords*ratio).r - currentLayerDepth + layerDepth;

    // interpolation of texture coordinates
    float weight = afterDepth / (afterDepth - beforeDepth);
    finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);
    return finalTexCoords;

    return currentTexCoords;
    //    float r = texture2D(parallaxMap, texCoords*ratio).r;
    //    float b =texture2D(parallaxMap, texCoords*ratio).b;
    //    float g = texture2D(parallaxMap, texCoords*ratio).g;
    //    float height =  (r+g+b)/3;
    //    vec2 p = viewDir.xy / viewDir.z * (height*height_scale);
    //    return texCoords + p;
}
