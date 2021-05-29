#version 330

in vec4 vertColor;
out vec4 outColor;

void main(){
    if (dot(gl_PointCoord - 0.8, gl_PointCoord - 0.8) > 0.25)       //makes points rounded
        discard;
    else
        outColor = vertColor;
}
