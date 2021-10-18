#include "pn_shader.h"
#include "pn_log.h"
#include "pn_render.h"
#include "pn_vars.h"

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

void pn_init_default_shaders() {
	// If default shader already exists, return.
	if(__pn_default_shader_program) return;

    // TODO: Write this in file and include it in compile-time.
	const char* default_vert_shader = 	
		"#version 330 core\n"
		"layout (location = 0) in vec3 a_pos;\n"
		"layout (location = 1) in vec3 a_normal;\n"
		"layout (location = 2) in vec2 a_uv;\n"
		
		"uniform mat4 u_model;\n"
		"uniform mat4 u_view;\n"
		"uniform mat4 u_projection;\n"
		
		"out vec2 v_uv;\n"
		"out vec3 v_normal;\n"
		"out vec3 v_frag_pos;\n"
		
		"void main() {\n"
		"	gl_Position = u_projection * u_view * u_model * vec4(a_pos, 1.0);\n"
		"	v_uv = a_uv;\n"
		"	v_frag_pos = vec3(u_model * vec4(a_pos, 1.0));\n"
		"	v_normal = mat3(transpose(inverse(u_model))) * a_normal;"
		"}";

	const char* default_frag_shader =
		"#version 330 core\n"
										
		"uniform vec3 u_color;\n"
		"uniform bool u_has_texture;\n"
		"uniform bool u_use_light;\n"
		"uniform vec3 u_light_pos;\n"
		"uniform vec3 u_light_color;\n"
		"uniform sampler2D u_texture;\n"
		"uniform vec3 u_camera_pos;\n"
		
		"out vec4 f_color;\n"
		
		"in vec2 v_uv;\n"
		"in vec3 v_normal;\n"
		"in vec3 v_frag_pos;\n"
		
		"void main() {\n"
			// Calculate object color.
		"	vec3 object_color;\n"
		"	if(u_has_texture) {\n"
		"		object_color = vec3(texture(u_texture, v_uv)) * u_color;\n"
		"	} else {\n" 
		"		object_color = u_color;\n"
		"	}\n"

		"	vec3 result;\n"

		"	if(u_use_light) {\n"
		// Ambient.
		"		float ambient_strength = 0.1;\n"
		"		vec3 ambient = ambient_strength * u_light_color;"

		// Diffuse.
		"		vec3 norm = normalize(v_normal);\n"
		"		vec3 light_dir = normalize(u_light_pos - v_frag_pos);\n"
		"		float diff = max(dot(norm, light_dir), 0.0);\n"
		"		vec3 diffuse = diff * u_light_color;\n"

		// Specular.
		"		float specular_strength = 1.0;\n"
		"		vec3 view_dir = normalize(u_camera_pos - v_frag_pos);\n"
		"		vec3 reflect_dir = reflect(-light_dir, norm);\n"
		"		float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);\n"
		"		vec3 specular = specular_strength * spec * u_light_color;\n"

		// Attenuation.
		"		float distance = length(u_light_pos - v_frag_pos);\n"
		"		float attenuation = clamp(30 / distance, 0, 1);\n"

		"		ambient *= attenuation;\n"
		"		specular *= attenuation;\n"
		"		diffuse *= attenuation;\n"
		"		result = (ambient + diffuse + specular) * object_color * attenuation;\n"
		"	} else {\n"
		"		result = object_color;"
		"	}"

		"	f_color = vec4(result, 1.0);"
		"}\n";

	__pn_default_shader_program = pn_create_shader_program(default_vert_shader, default_frag_shader);

	pn_set_light_color((pn_color_t){255, 255, 255, 255});
	pn_set_light_pos((v3){0, 0, 0});
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
	program->m_uniforms[UNI_HAS_TEXTURE] = glGetUniformLocation(program->m_id, "u_has_texture");
	program->m_uniforms[UNI_LIGHT_COLOR] = glGetUniformLocation(program->m_id, "u_light_color");
	program->m_uniforms[UNI_LIGHT_POS] = glGetUniformLocation(program->m_id, "u_light_pos");
	program->m_uniforms[UNI_CAMERA_POS] = glGetUniformLocation(program->m_id, "u_camera_pos");
	program->m_uniforms[UNI_USE_LIGHT] = glGetUniformLocation(program->m_id, "u_use_light");

	// Delete the shaders.
	glDeleteShader(program->m_vert_shader);
	glDeleteShader(program->m_frag_shader);

	return program;
}

void pn_bind_shader_program(pn_shader_program_t* program) {
	if(program) {
		glUseProgram(program->m_id);
	} else {
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
