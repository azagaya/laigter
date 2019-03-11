#version 330 core


in vec2 texCoord;
out vec4 FragColor;

uniform sampler2D texture;

void main()
{
    FragColor = texture2D(texture,texCoord);
}
