#include "pn_camera.h"
#include "pn_vars.h"
#include "pn_log.h"
#include <GL/glew.h>

pn_camera_t* pn_create_camera(vec3 pos, f32 fov, f32 znear, f32 zfar) {
	pn_camera_t* camera = malloc(sizeof(pn_camera_t));
	camera->m_yaw = 90.f;
	camera->m_pitch = 0.f;
  
	__pn_cam_instance = camera;

	glm_vec3_copy(pos, camera->m_pos);
	glm_vec3_copy((vec3){0,0,1}, camera->m_forward);
	glm_vec3_copy((vec3){0,1,0}, camera->m_up);

	__pn_camera_update_queued = true;

	return camera;
}

void pn_update_camera() {
	if(!__pn_camera_update_queued) return;

	__pn_camera_update_queued = false;

	// Calulate the projection matrix.
	f32 aspect = (f32)__pn_window_instance->m_width / (f32)__pn_window_instance->m_height;
	glm_perspective(glm_rad(90.0f), aspect, 0.1f, 1000.0f, __pn_cam_instance->m_projection);

	// Calculate the forward direction based on pitch and yaw.
	f32 yaw_rad = glm_rad(__pn_cam_instance->m_yaw);
	f32 pitch_rad = glm_rad(__pn_cam_instance->m_pitch);

	__pn_cam_instance->m_forward[0] = cosf(yaw_rad) * cosf(pitch_rad);
	__pn_cam_instance->m_forward[1] = sinf(pitch_rad);
	__pn_cam_instance->m_forward[2] = sinf(yaw_rad) * cosf(pitch_rad);

	glm_vec3_normalize(__pn_cam_instance->m_forward);
	glm_vec3_cross(__pn_cam_instance->m_forward, __pn_cam_instance->m_up, __pn_cam_instance->m_right);
	glm_vec3_normalize(__pn_cam_instance->m_right);

	// Calculate the look direction.	
	vec3 look_dir; glm_vec3_add(__pn_cam_instance->m_pos, __pn_cam_instance->m_forward, look_dir);

	// Calculate the view matrix.
	glm_mat4_identity(__pn_cam_instance->m_view);
	glm_lookat(__pn_cam_instance->m_pos, look_dir, __pn_cam_instance->m_up, __pn_cam_instance->m_view);
}

void pn_free_camera(pn_camera_t* camera) {
	free(camera);
}

void pn_move_camera(vec3 move_dir) {
	glm_vec3_add(__pn_cam_instance->m_pos, move_dir, __pn_cam_instance->m_pos);

	__pn_camera_update_queued = true;
}

void pn_rotate_camera(f32 yaw, f32 pitch) {
	__pn_cam_instance->m_yaw += yaw;
	__pn_cam_instance->m_pitch += pitch;

	while(__pn_cam_instance->m_yaw > 360) __pn_cam_instance->m_yaw -= 360;
	while(__pn_cam_instance->m_yaw < -360) __pn_cam_instance->m_yaw += 360;

	if(__pn_cam_instance->m_pitch > 89.99f) __pn_cam_instance->m_pitch = 89.99f;
	if(__pn_cam_instance->m_pitch < -89.99f) __pn_cam_instance->m_pitch = -89.99f;

	__pn_camera_update_queued = true;
}
