#version 130

in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 out_color;

uniform sampler2D mySampler;

void main(){
    vec4 textureColor = texture(mySampler,fragmentUV);
    out_color = textureColor * fragmentColor;
}
