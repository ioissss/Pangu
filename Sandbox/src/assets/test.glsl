
#type vertex
#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 v_TexCord;
uniform mat4 viewProjectionMatrix;
uniform mat4 transform;
out vec3 position;
out vec2 f_TexCord;
void main() {
	gl_Position = viewProjectionMatrix * transform * vec4(a_Position, 1.0);	//齐次坐标，四维的
	position = a_Position;
	f_TexCord = v_TexCord;
}



#type fragment
#version 330 core
in vec3 position;
in vec2 f_TexCord;
out vec4 FragColor;
uniform sampler2D v_texture;

void main() {
	FragColor = texture(v_texture, f_TexCord);
}
