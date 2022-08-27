#version 450 core

layout (triangles) in;
layout (points, max_vertices = 3) out;

// in TES_OUT {
//   vec4 color;
// } gs_in;

// // Output to the TES
// out GS_OUT {
//   vec4 color;
// } gs_out;

void main(){
  for(int i = 0; i < gl_in.length(); i++){
    gl_Position = gl_in[i].gl_Position;
    EmitVertex();
  }

  // gs_out.color = gs_in.color;
}