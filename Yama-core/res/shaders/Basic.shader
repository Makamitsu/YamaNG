#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

void main() {
	v_TexCoord = texCoord;
	gl_Position = position;
}
#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec2 v_TexCoord;
uniform sampler2D u_Texture;
void main() {
	color = texture(u_Texture, v_TexCoord);
}