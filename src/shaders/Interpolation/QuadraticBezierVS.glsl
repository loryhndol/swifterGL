#version 450 core

vec4 quadratic_bezier(vec4 A, vec4 B, vec4 C, float t){
  vec4 D = mix(A, B, t);
  vec4 E = mix(B, C, t);
  vec4 P = mix(D, E, t);
  return P;
}

layout(location = 0) uniform float t = 0.5f;

void main(){
  vec4 a = vec4(-1.0, -1.0, 0.5, 1.0);
  vec4 b = vec4(0.0, 1.0, 0.5, 1.0);
  vec4 c = vec4(1.0, -1.0, 0.5, 1.0);

  gl_Position = quadratic_bezier(a, b, c, t);
}