#version 460

float screenWidth = 800;
float screenHeight = 600;

uniform mat4 orthoProjection;

// In
layout (location = 1) in vec4 positionOffset_size;
layout (location = 2) in vec4 atlasOffset_spriteSize;
layout (location = 3) in float zBuffer;
layout (location = 4) in float flipped;

// Out
out vec2 textureCoordsOut;
out gl_PerVertex {
     vec4 gl_Position;
};

// # # # # MAIN # # # #
void main()
{
    vec2 positionOffset = positionOffset_size.xy;
    vec2 size = positionOffset_size.zw;
    vec2 atlasOffset = atlasOffset_spriteSize.xy;
    vec2 spriteSize = atlasOffset_spriteSize.zw;

    float left = atlasOffset.x;
    float bottom = atlasOffset.y;
    float right = atlasOffset.x + spriteSize.x;
    float top = atlasOffset.y + spriteSize.y;

    // POSITION CALCULATION
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
    gl_Position = orthoProjection * vec4(vertexPos, zBuffer, 1.0);

    // TEXCOORD CALCULATION
    vec2 textureCoords[12] = 
    {
    // # # # USE THESE TO FACE RIGHT
    //1er triangle
        vec2(left, top),
        vec2(left, bottom),
        vec2(right, top),
    //2e triangle
        vec2(right, top),
        vec2(left, bottom),
        vec2(right, bottom),

    // # # # USE THESE TO FACE LEFT
    //1er triangle
        vec2(right, top),
        vec2(right, bottom),
        vec2(left, top),
    //2e triangle
        vec2(left, top),
        vec2(right, bottom),
        vec2(left, bottom),
    };

    textureCoordsOut = textureCoords[gl_VertexID + int(flipped)];
}