#version 460


uniform mat4 model;
uniform mat4 projection;

layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>
out vec2 TexCoords;
out gl_PerVertex {
     vec4 gl_Position;
};

void main()
{
    TexCoords = vertex.zw;
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}