#version 460
// In
layout (location = 0) in ivec2 textureCoordsOut;

in vec2 textureCoordsOut;

out vec4 fragColor;

layout (location = 0) uniform sampler2D textureAtlas;


void main()
{
	vec4 textureColor = texelFetch(textureAtlas, ivec2(0, 0), 0);
	//fragColor = vec4(textureCoordsOut.x);
	//fragColor = texelFetch(textureAtlas, ivec2(textureCoords), 0);
	fragColor = vec4(1.0, textureColor.x, 1.0,1.0);

}