#shader vertex
#version 410 core

layout(location = 0) in vec3 vp;
layout(location = 1) in vec2 texCoord;

out vec2 v_texCoord;

void main() {
  gl_Position = vec4(vp, 1.0);
  v_texCoord = texCoord;
}

#shader fragment
#version 410 core

layout(location = 0) out vec4 frag_color;

in vec2 v_texCoord;

uniform sampler2D u_texture;
uniform vec4 u_tint;

void main() {
  vec4 texColor = texture(u_texture, v_texCoord);
  frag_color = texColor * u_tint;
}
