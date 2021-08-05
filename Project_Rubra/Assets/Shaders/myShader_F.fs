#version 330 core


in vec3 vertexColor; // the input variable from the vertex shader (same name and same type)
in vec2 texCoord;

uniform sampler2D myTexture;

out vec4 FragColor;
out vec2 tex;



void main()
{

    FragColor = texture(myTexture, texCoord) * vec4(vertexColor, 1.0);
}
