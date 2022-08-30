#version 450 core

in vec4 position;

out VS_OUT{
  vec4 color;
} vs_out;

layout (location = 0)uniform mat4 mv_matrix;
layout (location = 1)uniform mat4 proj_matrix;

void main(){
  gl_Position = proj_matrix * mv_matrix * position;
  vs_out.color = position * 2.0 + vec4(0.5, 0.5, 0.5, 0.0);
}