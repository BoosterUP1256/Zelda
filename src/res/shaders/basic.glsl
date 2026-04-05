#shader vertex
#version 410 core

layout(location = 0) in vec3 vp;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 color;

out vec2 v_texCoord;
out vec3 v_color;

//uniform mat4 u_mvp;

uniform mat4 u_transform;

void main() {
  //gl_Position = u_mvp * vec4(vp, 1.0);

  gl_Position = u_transform * vec4(vp, 1.0);
  v_texCoord = texCoord;
  v_color = color;
}

#shader fragment
#version 410 core

layout(location = 0) out vec4 frag_color;

in vec2 v_texCoord;
in vec3 v_color;

uniform sampler2D u_texture;
uniform vec4 u_tint;

void main() {
  vec4 texColor = texture(u_texture, v_texCoord);
  frag_color = frag_color = texColor * u_tint * vec4(v_color, 1.0);
}
