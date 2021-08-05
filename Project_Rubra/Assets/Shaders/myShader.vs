#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec2 uvTex;

uniform mat4 projectionMat;
uniform vec3 myColor;

out vec3 vertexColor; // specify a color output to the fragment shader
out vec2 texCoord;

void main()
{
    // see how we directly give a vec3 to vec4's constructor
    gl_Position = projectionMat * vec4(aPos, 1.0);

    vertexColor = vColor; // set the output variable to a dark-red color
    texCoord = uvTex;
}
 