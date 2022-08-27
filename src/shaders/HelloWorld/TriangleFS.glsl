#version 450 core

// in GS_OUT {
//   vec4 color;
// } fs_in;

// Output to the framebuffer
out vec4 color;

void main(){
  color = vec4(0.0,0.8,1.0,1.0);
  // color = fs_in.color;
}