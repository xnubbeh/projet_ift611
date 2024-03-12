#version 460
// In
in vec2 textureCoordsOut;

out vec4 fragColor;

layout (location = 0) uniform sampler2D textureAtlas;

void main()
{
	// texelFetch requires a vector of ints. This is why we cast here
	int texCoordX = int (textureCoordsOut.x);
	int texCoordY = int (textureCoordsOut.y);

	vec4 textureColor = texelFetch(textureAtlas, ivec2(texCoordX, texCoordY), 0);
	if(textureColor.a == 0.0)
	{
		discard;
	}
	fragColor = textureColor;
}