#version 130


in vec2 texCoord;
in vec3 FragPos;
out vec4 FragColor;

uniform sampler2D texture;
uniform sampler2D normalMap;
uniform vec3 lightPos;
uniform bool light;
uniform vec3 lightColor;
uniform float diffIntensity;
uniform float ambientIntensity;
uniform vec3 ambientColor;

void main()
{
    vec3 normal = normalize(texture2D(normalMap,texCoord).xyz*vec3(2.0,2.0,1.0)-vec3(1.0,1.0,0.0));
    vec3 lightDir = normalize(lightPos - vec3(FragPos.xy,0.0));
    float diff = max(dot(normal,lightDir),0.0);
    vec3 diffuse = diff * lightColor * diffIntensity;
    vec4 tex = texture2D(texture,texCoord);
    if (light){
        FragColor = tex*(vec4(diffuse,tex.w)+vec4(ambientColor,1.0)*ambientIntensity);
    }else{
        FragColor = tex;
    }
}
