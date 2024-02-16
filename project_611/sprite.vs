#version 460

float screenWidth = 800;
float screenHeight = 600;

uniform mat4 orthoProjection;

// In
layout (location = 1) in vec4 positionOffset_size;
layout (location = 2) in ivec4 atlasOffset_spriteSize;
layout (location = 3) in float zBuffer;

// Out
out vec2 textureCoordsOut;
out gl_PerVertex {
     vec4 gl_Position;
};


void main()
{
    vec2 positionOffset = positionOffset_size.xy;
    vec2 size = positionOffset_size.zw;
    ivec2 atlasOffset = atlasOffset_spriteSize.xy;
    ivec2 spriteSize = atlasOffset_spriteSize.zw;

    int left = atlasOffset.x;
    int top = atlasOffset.y;
    int right = atlasOffset.x + spriteSize.x;
    int bottom = atlasOffset.y + spriteSize.y;

    // vertex position calculation
    vec2 vertices[6] =
    {
        positionOffset,                              // Top Left
        vec2(positionOffset + vec2(0.0, size.y)),    // Bottom Left
        vec2(positionOffset + vec2(size.x, 0.0)),    // Top Right
        vec2(positionOffset + vec2(size.x, 0.0)),    // Top Right
        vec2(positionOffset + vec2(0.0, size.y)),    // Bottom Left
        positionOffset + size,                       // Bottom Right
    };

    vec2 vertexPos = vertices[gl_VertexID];

    // texcoord calculation
    ivec2 textureCoords[6] = 
    {
        ivec2(left, top),
        ivec2(left, bottom),
        ivec2(right, top),
        ivec2(right, top),
        ivec2(left, bottom),
        ivec2(right, bottom),
    };

   textureCoordsOut = textureCoords[gl_VertexID];

}