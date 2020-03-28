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
        // w is interpolated too
        // float f = 1024.0f / 100.0f;
        // FragColor = vec4(w / f, w / f, w / f, 1.0);

        FragColor = texture(texture0, uv);
        FragColor *= vec4(color, 1.0);
    }
    else {
        FragColor = texture(texture0, uv);
        FragColor *= vec4(color, 1.0);
    }
}
