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

	return camera;
}

void pn_camera_update() {
	f32 aspect = (f32)__pn_window_instance->m_width / (f32)__pn_window_instance->m_height;
	glm_perspective(glm_rad(45.0f), aspect, 0.1f, 100.0f, __pn_cam_instance->m_projection);

	glm_mat4_identity(__pn_cam_instance->m_view);
	
	vec3 lookdir;
	glm_vec3_add(__pn_cam_instance->m_pos, __pn_cam_instance->m_forward, lookdir);

	// glm_translate(__pn_cam_instance->m_view, __pn_cam_instance->m_pos);
	glm_lookat(__pn_cam_instance->m_pos, lookdir, __pn_cam_instance->m_up, __pn_cam_instance->m_view);
}

void pn_free_camera(pn_camera_t* camera) {
	free(camera);
}