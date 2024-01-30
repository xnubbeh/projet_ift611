#version 460

in vec2 TexCoords;
layout (location = 0) out vec4 Color;

uniform sampler2D image;
uniform vec3 spriteColor;

void main()
{    
    Color = vec4(1.0,1.0,1.0, 1.0) * texture(image, TexCoords);
}


/*
#version 460

layout (location = 0) out vec4 Color;
in vec2 TexCoords;


vec3 posToRGB(vec2 pos)
{
	float a = 0.5*atan(pos.y, pos.x)/3.14159;
	if (a < 0.0)
		a+=1.0;
	float l = length(pos);
	vec3 rgb = clamp(abs(mod(a*6.0+vec3(0.0,4.0,2.0),6.0)- 3.0)-1.0, 0.0, 1.0 );
	return mix(vec3(1.0), rgb, l);
}

void main()
{
	Color = vec4(posToRGB(TexCoords), 1.0f);
}*/
