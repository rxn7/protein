#include "pn_render.h"
#include "pn_vars.h"
#include "pn_log.h"

pn_render_object_t* pn_create_render_object(pn_vertex_t* vertices, u32 vertex_count, u32* indices, u32 index_count) {
	pn_render_object_t* render_object = malloc(sizeof(pn_render_object_t));

	pn_init_transform(&render_object->m_transform);
	render_object->m_index_count = index_count;
	render_object->m_color = (pn_color_t){255, 255, 255, 255};

	// Generate and bind the VAO.
	glGenVertexArrays(1, &render_object->m_vao);
	glBindVertexArray(render_object->m_vao);

	// Generate and bind the VBO.
	glGenBuffers(1, &render_object->m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, render_object->m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(pn_vertex_t), vertices, GL_STATIC_DRAW);
	
	// Generate and bind the EBO.
	glGenBuffers(1, &render_object->m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render_object->m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(u32), indices, GL_STATIC_DRAW);

	// Position attrib array.
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(pn_vertex_t), (void*)offsetof(pn_vertex_t, m_pos));

	// UV attrib array.
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(pn_vertex_t), (void*)offsetof(pn_vertex_t, m_uv));

	// Unbind the VAO.
	glBindVertexArray(0);

	return render_object;
}

pn_render_object_t* pn_create_primitive(pn_primite_t type) {
	pn_vertex_t* vertices;
	u32* indices;
	u32 vertex_count;
	u32 index_count;

	switch(type){
		case PN_TRIANGLE:
			vertices = (pn_vertex_t[]) {
				{{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
				{{ 0.0f,  1.0f, 0.0f}, {0.5f, 1.0f}},
				{{ 1.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
			};

			indices = (u32[]) {0,1,2};

			vertex_count = 3;
			index_count = 3;

			break;

		case PN_QUAD:
			vertices = (pn_vertex_t[]) {
				{{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
				{{-1.0f,  1.0f, 0.0f}, {0.0f, 1.0f}},
				{{ 1.0f,  1.0f, 0.0f}, {1.0f, 1.0f}},
				{{ 1.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
			};

			indices = (u32[]) {0,1,2, 2,3,0};

			vertex_count = 4;
			index_count = 6;

			break;

		default:
			pn_error("Unknown primitive: %u", type);
			return 0;
	}

	return pn_create_render_object(vertices, vertex_count, indices, index_count);
}

void pn_render_render_object(pn_render_object_t* render_object, pn_shader_program_t* shader_program) {
	if(!shader_program) shader_program = __pn_default_shader_program;

	pn_bind_shader_program(shader_program);

	mat4 model; pn_calculate_transform_model(&render_object->m_transform, model);

	// Set the model matrix uniform.
	glUniformMatrix4fv(shader_program->m_uniforms[UNI_MODEL], 1, GL_FALSE, (float*)model);
	// Set the view matrix uniform.
	glUniformMatrix4fv(shader_program->m_uniforms[UNI_VIEW], 1, GL_FALSE, (float*)__pn_cam_instance->m_view);
	// Set the projection matrix uniform.
	glUniformMatrix4fv(shader_program->m_uniforms[UNI_PROJECTION], 1, GL_FALSE, (float*)__pn_cam_instance->m_projection);
	// Set the color uniform.
	glUniform4fv(shader_program->m_uniforms[UNI_COLOR], 1, (vec4){PN_RGBA_F32(render_object->m_color)});

	// Bind the VAO.
	glBindVertexArray(render_object->m_vao);
		glDrawElements(GL_TRIANGLES, render_object->m_index_count, GL_UNSIGNED_INT, 0);
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