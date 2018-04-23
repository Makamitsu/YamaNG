#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec2 v_TexCoord;
out vec3 v_Normal;

uniform mat4 u_MVP;

void main() {
	v_TexCoord = texCoord;
	v_Normal = normal;
	gl_Position = u_MVP * vec4(position, 1.0);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_Normal;

uniform sampler2D u_Texture;

void main() {
	vec3 upVector = vec3(0.5, 0.5, 0.0);

	//color = texture(u_Texture, v_TexCoord);
	float dotprod = dot(upVector, v_Normal);
	color = vec4(vec3(dotprod), 1.0);
}