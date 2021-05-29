#version 330

uniform sampler2DRect particles0;

uniform mat4 modelViewProjectionMatrix;

in vec4  position;
in vec2  texcoord;

out vec4 vertColor;

void main(){
    vec4 texel0 = texture(particles0, texcoord);
    vec4 pos = vec4(texel0.xyz, 0.75);

    gl_Position = modelViewProjectionMatrix * pos;
    
    vertColor = vec4(0.1, 0.60, 0.50, 0.125);
    
    gl_PointSize = 1.5;
}
