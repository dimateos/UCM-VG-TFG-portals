#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
out float w;
out float gl_ClipDistance[1]; //needed?

uniform int option;
uniform vec4 clipPlane;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // note that we read the multiplication from right to left
    vec4 worldPos = model * vec4(aPos, 1.0);
    gl_Position = projection * view * worldPos;

    if (option == 0) {
        TexCoord = aTexCoord;
    }

    //screen coordinates as uv output to fragment
    else if (option == 1) {
        //just normalize from [-w, w] to [0, w]
        TexCoord = (gl_Position.xy + gl_Position.w) / 2.0;
        w = gl_Position.w;

        //do not normalize to [0, 1] screen per vertex
            //it only works if polygons are facing the camera
        // TexCoord /= w; //w needs interpolation
    }

    //user defined clipping plane
    else if (option == 2) {
        TexCoord = aTexCoord;
        gl_ClipDistance[0] = dot (worldPos, clipPlane);
    }
}
