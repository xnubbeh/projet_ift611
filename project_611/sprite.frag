#version 460

in vec2 TexCoords;
layout (location = 0) out vec4 Color;

uniform sampler2D image;
uniform vec3 spriteColor;

void main()
{    
    Color = vec4(1.0,1.0,1.0, 1.0);// * texture(image, TexCoords);
}