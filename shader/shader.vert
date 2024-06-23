#version 460 core

layout (location = 0) in vec3 aPos;

uniform float dx = 0;
uniform float dy = 0;

void main()
{
   gl_Position = vec4(aPos.x + dx, aPos.y + dy, aPos.z, 1.0);
}
