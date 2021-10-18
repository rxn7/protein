#include "pn_render.h"
#include "pn_color.h"
#include "pn_math.h"
#include "pn_shader.h"
#include "pn_vars.h"
#include "pn_log.h"
#include <pn/pn_log.h>

pn_render_object_t* pn_create_render_object(pn_vertex_t* vertices, u32 vertex_count) {
	pn_render_object_t* render_object = malloc(sizeof(pn_render_object_t));

	pn_init_transform(&render_object->m_transform);

	render_object->m_color = (pn_color_t){255, 255, 255, 255};
    render_object->m_vertex_count = vertex_count;
	render_object->m_use_light = true;
	
	// Generate and bind the VAO.
	glGenVertexArrays(1, &render_object->m_vao);
	glBindVertexArray(render_object->m_vao);

	// Generate and bind the VBO.
	glGenBuffers(1, &render_object->m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, render_object->m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(pn_vertex_t), vertices, GL_STATIC_DRAW);
	
	// Position attrib array.
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(pn_vertex_t), (void*)offsetof(pn_vertex_t, m_pos));

    // Normal attrib array.
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(pn_vertex_t), (void*)offsetof(pn_vertex_t, m_normal));
	
	// UV attrib array.
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(pn_vertex_t), (void*)offsetof(pn_vertex_t, m_uv));

	// Unbind the VAO.
	glBindVertexArray(0);

	return render_object;
}

pn_render_object_t* pn_create_primitive_render_object(pn_primite_t type) {
	pn_vertex_t* vertices;
	u32* indices;
	u32 vertex_count;
	u32 index_count;

	switch(type){
		case PN_TRIANGLE: {
			vertices = (pn_vertex_t[]) {
				{{-1.0f, -1.0f, 0.0f}, {0,0,-1}, {0.0f, 0.0f}},
				{{ 0.0f,  1.0f, 0.0f}, {0,0,-1}, {0.5f, 1.0f}},
				{{ 1.0f, -1.0f, 0.0f}, {0,0,-1}, {1.0f, 0.0f}},

				{{ 1.0f, -1.0f, 0.0f}, {0,0,1}, {0.0f, 0.0f}},
				{{ 0.0f,  1.0f, 0.0f}, {0,0,1}, {0.5f, 1.0f}},
				{{-1.0f, -1.0f, 0.0f}, {0,0,1}, {1.0f, 0.0f}},
			};

			vertex_count = 6;

			break;
		}

        case PN_TRIANGLE_ONE_FACE:
            vertices = (pn_vertex_t[]) {
				{{-1.0f, -1.0f, 0.0f}, {0,0,-1}, {0.0f, 0.0f}},
				{{ 0.0f,  1.0f, 0.0f}, {0,0,-1}, {0.5f, 1.0f}},
				{{ 1.0f, -1.0f, 0.0f}, {0,0,-1}, {1.0f, 0.0f}},
            };

            vertex_count = 3;

            break;

		case PN_QUAD_ONE_FACE: {
			vertices = (pn_vertex_t[]) {
                {{-1.0f, -1.0f, 0.0f}, {0,0,-1}, {0.0f, 0.0f}},
                {{-1.0f,  1.0f, 0.0f}, {0,0,-1}, {0.0f, 1.0f}},
                {{ 1.0f, -1.0f, 0.0f}, {0,0,-1}, {1.0f, 0.0f}},
                    
                {{-1.0f,  1.0f, 0.0f}, {0,0,-1}, {0.0f, 1.0f}},
                {{ 1.0f,  1.0f, 0.0f}, {0,0,-1}, {1.0f, 1.0f}},
                {{ 1.0f, -1.0f, 0.0f}, {0,0,-1}, {1.0f, 0.0f}}
            };
            
			vertex_count = 6;

			break;
		}

		case PN_QUAD: {
			vertices = (pn_vertex_t[]) {
                {{-1.0f, -1.0f, 0.0f}, {0,0,-1}, {0.0f, 0.0f}},
                {{-1.0f,  1.0f, 0.0f}, {0,0,-1}, {0.0f, 1.0f}},
                {{ 1.0f, -1.0f, 0.0f}, {0,0,-1}, {1.0f, 0.0f}},
                    
                {{-1.0f,  1.0f, 0.0f}, {0,0,-1}, {0.0f, 1.0f}},
                {{ 1.0f,  1.0f, 0.0f}, {0,0,-1}, {1.0f, 1.0f}},
                {{ 1.0f, -1.0f, 0.0f}, {0,0,-1}, {1.0f, 0.0f}},
            
                
                {{ 1.0f, -1.0f, 0.0f}, {0,0,1}, {1.0f, 0.0f}},
                {{ 1.0f,  1.0f, 0.0f}, {0,0,1}, {1.0f, 1.0f}},
                {{-1.0f,  1.0f, 0.0f}, {0,0,1}, {0.0f, 1.0f}},
                {{ 1.0f, -1.0f, 0.0f}, {0,0,1}, {1.0f, 0.0f}},
                {{-1.0f,  1.0f, 0.0f}, {0,0,1}, {0.0f, 1.0f}},
                {{-1.0f, -1.0f, 0.0f}, {0,0,1}, {0.0f, 0.0f}},
                    
            };
            
			vertex_count = 12;

			break;
		}

		case PN_PYRAMID: {
			vertices = (pn_vertex_t[]) {
			};

			vertex_count = 5;

			break;
		}

        case PN_CUBE: {
			vertices = (pn_vertex_t[]) {
            };

			vertex_count = 36;

            break;
        }

		default:
			pn_error("Unknown primitive: %u", type);
			return 0;
	}

	return pn_create_render_object(vertices, vertex_count);
}

void pn_render_render_object(pn_render_object_t* render_object, pn_shader_program_t* shader_program, pn_texture_t* texture) {
	pn_update_camera();
	
	if(!shader_program) shader_program = __pn_default_shader_program;
	pn_bind_shader_program(shader_program);
	
	if(texture) { 
		pn_bind_texture(texture);
		glUniform1i(shader_program->m_uniforms[UNI_HAS_TEXTURE], 1);
	} else {
		pn_unbind_texture();
		glUniform1i(shader_program->m_uniforms[UNI_HAS_TEXTURE], 0);
	}

	glUniform1i(shader_program->m_uniforms[UNI_USE_LIGHT], render_object->m_use_light);

	mat4 model; pn_calculate_transform_model(&render_object->m_transform, model);

	// Set the model matrix uniform.
	glUniformMatrix4fv(shader_program->m_uniforms[UNI_MODEL], 1, GL_FALSE, (float*)model);
	// Set the view matrix uniform.
	glUniformMatrix4fv(shader_program->m_uniforms[UNI_VIEW], 1, GL_FALSE, (float*)__pn_cam_instance->m_view);
	// Set the projection matrix uniform.
	glUniformMatrix4fv(shader_program->m_uniforms[UNI_PROJECTION], 1, GL_FALSE, (float*)__pn_cam_instance->m_projection);
	// Set the color uniform.
	glUniform3fv(shader_program->m_uniforms[UNI_COLOR], 1, (v3){PN_RGB_F32(render_object->m_color)});

	// Bind the VAO.
	glBindVertexArray(render_object->m_vao);
		glDrawArrays(GL_TRIANGLES, 0, render_object->m_vertex_count);
	// Unbind the VAO.
	glBindVertexArray(0);

	pn_unbind_shader_program();
}

void pn_free_render_object(pn_render_object_t* render_object) {
	// Delete the VAO.
	glDeleteVertexArrays(1, &render_object->m_vao);
	// Delete the VBO.
	glDeleteBuffers(1, &render_object->m_vbo);

	free(render_object);
}

void pn_set_clear_color(pn_color_t color) {
	glClearColor(PN_RGBA_F32(color));
}

void pn_set_light_pos(v3 pos) {
	pn_bind_shader_program(__pn_default_shader_program);
		glUniform3fv(__pn_default_shader_program->m_uniforms[UNI_LIGHT_POS], 1, pos);
	pn_unbind_shader_program();
}

void pn_set_light_color(pn_color_t color) {
	pn_bind_shader_program(__pn_default_shader_program);
		glUniform3fv(__pn_default_shader_program->m_uniforms[UNI_LIGHT_COLOR], 1, (v3){PN_RGB_F32(color)});
	pn_unbind_shader_program();
}
