#version 460
// In
layout (location = 0) in ivec2 textureCoordsOut;

// Out
layout (location = 0) out vec4 fragColor;

// SpriteSheet
layout (location = 0) uniform sampler2D textureAtlas;


void main()
{
	vec4 textureColor = texelFetch(textureAtlas, textureCoordsOut, 0);
//	fragColor = vec4(textureCoordsOut.x);
}