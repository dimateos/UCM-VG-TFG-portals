#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
out float w;

uniform int option;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // note that we read the multiplication from right to left
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    //atm some options for tex coords
    if (option == 0) {
        TexCoord = aTexCoord;
    }
    else if (option == 1) {
        //just normalize from [-w, w] to [0, w]
        TexCoord = (gl_Position.xy + gl_Position.w) / 2.0;
        w = gl_Position.w;

        //do not normalize to [0, 1] screen per vertex
            //it only works if polygons are facing the camera
        // TexCoord /= w;
    }
}
