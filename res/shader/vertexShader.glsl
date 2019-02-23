#version 130

in vec2 vertexPositions;
in vec4 vertexColor;
in vec2 vertexUV;

out vec4 fragmentColor;
out vec2 fragmentUV;

uniform mat4 P; 

void main(){
    gl_Position = P*vec4(vertexPositions,0.0,1.0);
    fragmentColor = vertexColor;
    fragmentUV  = vec2(vertexUV.x , 1.0 - vertexUV.y);
}