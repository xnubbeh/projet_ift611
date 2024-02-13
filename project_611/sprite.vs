#version 460

struct RenderData {
	vec2 pos;  // Top left of the sprite
	vec2 size; // vec2(width, height);
	ivec2 atlasOffset;
	ivec2 spriteSize; // vec2(numPix_width, numPix_height);
	float z;
};

float screenWidth = 800;
float screenHeight = 600;


uniform mat4 model;
uniform mat4 orthoProjection;
//
//layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>
//out vec2 TexCoords;
out gl_PerVertex {
     vec4 gl_Position;
};


// Out
layout (location = 0) out vec2 textureCoordsOut;

// Buffers
layout (std430, binding = 0) buffer TransformSBO
{
  RenderData data[];
};

void main()
{
    RenderData sprite = data[gl_InstanceID];

    int left = sprite.atlasOffset.x;
    int top = sprite.atlasOffset.y;
    int right = sprite.atlasOffset.x + sprite.spriteSize.x;
    int bottom = sprite.atlasOffset.y + sprite.spriteSize.y;

    // position
    vec2 vertices[6] =
    {
        sprite.pos,                                        // Top Left
        vec2(sprite.pos + vec2(0.0, sprite.size.y)),    // Bottom Left
        vec2(sprite.pos + vec2(sprite.size.x, 0.0)),    // Top Right
        vec2(sprite.pos + vec2(sprite.size.x, 0.0)),    // Top Right
        vec2(sprite.pos + vec2(0.0, sprite.size.y)),    // Bottom Left
        sprite.pos + sprite.size                        // Bottom Right
    };

      // Normalize Position
    {
        vec2 vertexPos = vertices[gl_VertexID];

        // ######################### REMETTRE CETTE LIGNE FONCTIONNELLE UN JOUR
        gl_Position = orthoProjection * vec4(vertexPos, sprite.z, 1.0);

     //   gl_Position = vec4(vertexPos, sprite.z, 1.0);

    }

    // texcoord
    vec2 textureCoords[6] = 
    {
        vec2(left, top),
        vec2(left, bottom),
        vec2(right, top),
        vec2(right, top),
        vec2(left, bottom),
        vec2(right, bottom),
    };

    textureCoordsOut = textureCoords[gl_VertexID];
}