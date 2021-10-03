#include "pn_camera.h"
#include "pn_vars.h"
#include <GL/glew.h>

pn_camera_t* pn_create_camera(vec3 pos, float fov, float znear, float zfar) {
	pn_camera_t* camera = malloc(sizeof(pn_camera_t));
	
	__pn_cam_instance = camera;

	glm_vec3_copy(pos, camera->m_pos);
	
	vec3 forward = {0, 0, 1};
	glm_vec3_copy(forward, camera->m_forward);

	vec3 up = {0, 1, 0};
	glm_vec3_copy(up, camera->m_up);

	f32 aspect = (f32)__pn_window_instance->m_width / (f32)__pn_window_instance->m_height;

	glm_perspective(fov, aspect, znear, zfar, camera->m_perspective);

	return camera;
}

void pn_calculate_view_projection(mat4 dest) {
	vec3 direction;
	glm_vec3_add(__pn_cam_instance->m_pos, __pn_cam_instance->m_forward, direction);
	glm_lookat(__pn_cam_instance->m_pos, direction, __pn_cam_instance->m_up, dest);
}

void pn_free_camera(pn_camera_t* camera) {
	free(camera);
}