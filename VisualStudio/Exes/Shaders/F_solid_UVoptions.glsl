#version 330 core
in vec2 TexCoord;
in float w;
out vec4 FragColor;

uniform int option;

uniform vec3 color;
uniform sampler2D texture0;

void main()
{
    vec2 uv = TexCoord;

    //atm some options for tex coords
    if (option == 1) {
        uv /= w;
    }

    FragColor = texture(texture0, uv);
    FragColor *= vec4(color, 1.0);
}
