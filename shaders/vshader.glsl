#version 330 core
in vec3 aPos;
in vec2 aTexCoord;
out vec2 texCoord;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    texCoord = aTexCoord;
}
