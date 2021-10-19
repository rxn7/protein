#pragma once

// TODO: Write a tool that will automatically copy the shaders from files.
const char __pn_shaded_vert_shader[] = 
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
	"	v_normal = mat3(transpose(inverse(u_model))) * a_normal;\n"
	"}\n";

const char __pn_shaded_frag_shader[] = 
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

	"	vec3 object_color;\n"
	"	if(u_has_texture) 	object_color = vec3(texture(u_texture, v_uv)) * u_color; \n"
	"	else 				object_color = u_color;\n"

	"	vec3 result;\n"
	"	if(u_use_light) {\n"
			
	// Ambient
	"		float ambient_strength = 0.1;\n"
	"		vec3 ambient = ambient_strength * u_light_color;\n"

	// Diffuse
	"		vec3 norm = normalize(v_normal);\n"
	"		vec3 light_dir = normalize(u_light_pos - v_frag_pos);\n"
	"		float diff = max(dot(norm, light_dir), 0.0);\n"
	"		vec3 diffuse = diff * u_light_color;\n"

	// Specular
	"		float specular_strength = 1.0;\n"
	"		vec3 view_dir = normalize(u_camera_pos - v_frag_pos);\n"
	"		vec3 reflect_dir = reflect(-light_dir, norm);\n"
	"		float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);\n"
	"		vec3 specular = specular_strength * spec * u_light_color;\n"

	// Attenuation
	"		float distance = length(u_light_pos - v_frag_pos);\n"
	"		float attenuation = clamp(30 / distance, 0, 1);\n"
	"		ambient *= attenuation;\n"
	"		specular *= attenuation;\n"
	"		diffuse *= attenuation;\n"
	"		result = (ambient + diffuse + specular) * object_color * attenuation;\n"
	"	} else {\n"
	"		result = object_color;\n"
	"	}\n"
	"	f_color = vec4(result, 1.0);\n"
	"}\n";