#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

//other cool config uniforms
uniform int option = 0; //switch post filter
uniform float time = 1.0f; //cool effects

const float offset = 1.0 / 300.0;
const vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right
    );

const float kernel_sharpen[9] = float[](
    1, 1, 1,
    1, 8, 1,
    1, 1, 1
);

const float kernel_edges[9] = float[](
    -1, -1, -1,
    -1,  9, -1,
    -1, -1, -1
);

const float amount = 16;
const float kernel_blur[9] = float[](
    1.0 / amount, 2.0 / amount, 1.0 / amount,
    2.0 / amount, 4.0 / amount, 2.0 / amount,
    1.0 / amount, 2.0 / amount, 1.0 / amount
);

void main()
{
    //no effect
    if (option == 0) FragColor = texture(screenTexture, TexCoords);

    //grayscale
    if (option == 1) {
        FragColor = texture(screenTexture, TexCoords);
        float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
        FragColor = vec4(average, average, average, 1.0);
    }

    //negative
    if (option == 2) {
        FragColor = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);
    }

    //weird bubbles
    if (option == 3) {
        FragColor = texture(screenTexture,
            TexCoords + 0.005*vec2( sin(time+1024.0*TexCoords.x),cos(time+768.0*TexCoords.y)));
    }

    //kernel usage
    if (option == 4) {
    vec3 color = vec3(0.0);
    for(int i = 0; i < 9; i++)
        color += vec3(texture(screenTexture, TexCoords.st + offsets[i])) * kernel_edges[i];

    FragColor = vec4(color, 1.0);
    }

}


