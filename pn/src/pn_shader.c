#include "pn_shader.h"
#include "pn_log.h"

pn_shader_program_t* pn_create_shader_program(const char* vert_src, const char* frag_src) {
	pn_shader_program_t* program = malloc(sizeof(pn_shader_program_t));
	int success;
	char info_log[512];

	program->m_vert_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(program->m_vert_shader, 1, &vert_src, NULL);
	glCompileShader(program->m_vert_shader);

	glGetShaderiv(program->m_vert_shader, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(program->m_vert_shader, 512, NULL, info_log);
		pn_error("Failed to compile vertex shader: %s", info_log);
	}

	program->m_frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(program->m_frag_shader, 1, &frag_src, NULL);
	glCompileShader(program->m_frag_shader);

	glGetShaderiv(program->m_frag_shader, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(program->m_frag_shader, 512, NULL, info_log);
		pn_error("Failed to compile fragment shader: %s", info_log);
	}

	program->m_id = glCreateProgram();
	glAttachShader(program->m_id, program->m_vert_shader);
	glAttachShader(program->m_id, program->m_frag_shader);
	glLinkProgram(program->m_id);

	glGetProgramiv(program->m_id, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(program->m_id, 512, NULL, info_log);
		pn_error("Failed to link shader program: %s", info_log);
	}

	glValidateProgram(program->m_id);
	glGetProgramiv(program->m_id, GL_VALIDATE_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(program->m_id, 512, NULL, info_log);
		pn_error("Failed to validate shader program: %s", info_log);
	}

	program->m_uniforms[UNI_MODEL] = glGetUniformLocation(program->m_id, "u_model");
	program->m_uniforms[UNI_VIEW] = glGetUniformLocation(program->m_id, "u_view");
	program->m_uniforms[UNI_PROJECTION] = glGetUniformLocation(program->m_id, "u_projection");

	glDeleteShader(program->m_vert_shader);
	glDeleteShader(program->m_frag_shader);

	return program;
}

void pn_bind_shader_program(pn_shader_program_t* program) {
	if(program) {
		glUseProgram(program->m_id);
	}else {
		pn_error("Failed to bind shader program! Shader program doesn't exist!");
	}
}

void pn_unbind_shader_program() {
	glUseProgram(0);
}

void pn_free_shader_program(pn_shader_program_t* program) {
	glDeleteProgram(program->m_id);
	free(program);
}