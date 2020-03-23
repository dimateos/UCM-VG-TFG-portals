#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform vec3 color;
uniform sampler2D texture0;

void main()
{
    FragColor = texture(texture0, TexCoord);
    FragColor *= vec4(color, 1.0);
}
