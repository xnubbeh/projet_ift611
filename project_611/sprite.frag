#version 460

layout (location = 0) in vec2 textureCoordsOut;

layout (location = 0) out vec4 fragColor;

//layout (location = 0) uniform sampler2D textureAtlas;/


void main()
{
	//vec4 textureColor = texelFetch(textureAtlas, ivec2(textureCoords), 0);
	fragColor = vec4(1.0);
}