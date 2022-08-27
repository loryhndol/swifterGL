#version 450 core

// Input from the Vertex Shader
in VS_OUT {
  vec4 color;
} fs_in;

// Output to the framebuffer
out vec4 color;

void main(){
  color = fs_in.color;
}