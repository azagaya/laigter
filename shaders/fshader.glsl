#version 330 core


in vec2 texCoord;
in vec3 FragPos;
out vec4 FragColor;

uniform sampler2D texture;
uniform sampler2D normalMap;
uniform vec3 lightPos;
uniform bool light;

void main()
{
    vec3 normal = normalize(texture2D(normalMap,texCoord).xyz*vec3(2.0,2.0,1.0)-vec3(1.0,1.0,0.0));
    vec3 lightDir = normalize(lightPos - vec3(FragPos.xy,0.0));
    float diff = max(dot(normal,lightDir),0.0);
    vec3 diffuse = diff * vec3(0.0,0.4,0.3);
    vec4 tex = texture2D(texture,texCoord);
    if (light){
        FragColor = tex*(vec4(diffuse,tex.w)+vec4(0.8,0.8,0.8,1.0));
    }else{
        FragColor = tex;
    }
}
