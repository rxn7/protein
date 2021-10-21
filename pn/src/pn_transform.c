#include "pn_transform.h"
#include "pn_log.h"
#include "pn_vars.h"

void pn_transform_init(pn_transform_t* transform) {
	glm_vec3_one(transform->m_scale);
	glm_vec3_zero(transform->m_pos);
	glm_vec3_zero(transform->m_rot);
}

void pn_transform_get_model(pn_transform_t* transform, mat4 dest) {
	mat4 pos_matrix;
	glm_mat4_identity(pos_matrix);
	glm_translate(pos_matrix, transform->m_pos);
	
	mat4 rot_matrix_x;
	glm_mat4_identity(rot_matrix_x);
	glm_rotate(rot_matrix_x, transform->m_rot[0], (vec3){1, 0, 0});

	mat4 rot_matrix_y;
	glm_mat4_identity(rot_matrix_y);
	glm_rotate(rot_matrix_y, transform->m_rot[1], (vec3){0, 1, 0});

	mat4 rot_matrix_z;
	glm_mat4_identity(rot_matrix_z);
	glm_rotate(rot_matrix_z, transform->m_rot[2], (vec3){0, 0, 1});

	mat4 rot_matrix;
	glm_mat4_identity(rot_matrix);
	glm_mat4_mulN((mat4* []){&rot_matrix_z, &rot_matrix_y, &rot_matrix_x}, 3, rot_matrix);

	mat4 scale_matrix; 
	glm_mat4_identity(scale_matrix);
	glm_scale(scale_matrix, transform->m_scale);

	glm_mat4_mulN((mat4* []){&pos_matrix, &rot_matrix, &scale_matrix}, 3, dest);
}
