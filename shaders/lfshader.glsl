#version 330 core

in vec2 texCoord;
out vec4 FragColor;
uniform vec3 lightColor;
uniform sampler2D texture;

void main()
{
    vec4 tex = texture2D(texture,texCoord);
    FragColor = tex*(vec4(lightColor,tex.a)+vec4(0.8,0.8,0.8,1.0));
}
