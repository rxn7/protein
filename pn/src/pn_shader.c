#include "pn_shader.h"
#include "pn_log.h"

static void pn_compile_shader(GLenum type, u32* id, const char* src) {
	*id = glCreateShader(type);
	glShaderSource(*id, 1, &src, NULL);
	glCompileShader(*id);

	int success;
	glGetShaderiv(*id, GL_COMPILE_STATUS, &success);
	if(!success) {
		char info_log[512];
		glGetShaderInfoLog(*id, 512, NULL, info_log);
		pn_error("Failed to compile %s shader: %s", type == GL_VERTEX_SHADER ? "vertex" : "fragment", info_log);
	}
}

pn_shader_program_t* pn_create_shader_program(const char* vert_src, const char* frag_src) {
	pn_shader_program_t* program = malloc(sizeof(pn_shader_program_t));
	int success;
	char info_log[512];

	pn_compile_shader(GL_VERTEX_SHADER, &program->m_vert_shader, vert_src);
	pn_compile_shader(GL_FRAGMENT_SHADER, &program->m_frag_shader, frag_src);

	program->m_id = glCreateProgram();

	// Attach the shaders to the program.
	glAttachShader(program->m_id, program->m_vert_shader);
	glAttachShader(program->m_id, program->m_frag_shader);
	
	// Link the program.
	glLinkProgram(program->m_id);
	glGetProgramiv(program->m_id, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(program->m_id, 512, NULL, info_log);
		pn_error("Failed to link shader program: %s", info_log);
	}

	// Validate the program.
	glValidateProgram(program->m_id);
	glGetProgramiv(program->m_id, GL_VALIDATE_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(program->m_id, 512, NULL, info_log);
		pn_error("Failed to validate shader program: %s", info_log);
	}

	// Get the uniforms locations.
	program->m_uniforms[UNI_MODEL] = glGetUniformLocation(program->m_id, "u_model");
	program->m_uniforms[UNI_VIEW] = glGetUniformLocation(program->m_id, "u_view");
	program->m_uniforms[UNI_PROJECTION] = glGetUniformLocation(program->m_id, "u_projection");
	program->m_uniforms[UNI_COLOR] = glGetUniformLocation(program->m_id, "u_color");

	// Delete the shaders.
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