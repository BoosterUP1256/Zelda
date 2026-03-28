#shader vertex
#version 410 core

in vec3 vp;
void main() {
  gl_Position = vec4(vp, 1.0);
}

#shader fragment
#version 410 core

out vec4 frag_color;

uniform vec4 u_color;

void main() {
  frag_color = u_color;
}
