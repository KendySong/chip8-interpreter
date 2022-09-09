#version 450 core
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 texUV;
layout (location = 2) in vec3 vecNormal;
layout (location = 3) in float texID;

uniform mat4 projection;
uniform mat4 view;

out vec2 v_texUV;
out float v_texID;

out vec3 v_normal;
out vec3 v_fragPosition;

void main()
{
    v_texUV = texUV;
    v_texID = texID;
    v_normal = vecNormal;
    v_fragPosition = vertex;
    gl_Position = projection * view * vec4(vertex, 1);
}