#include "pn_camera.h"
#include "pn_common.h"
#include "pn_shader.h"
#include "pn_vars.h"
#include "pn_log.h"
#include "pn_math.h"
#include <cglm/cglm.h>
#include <GL/glew.h>

pn_camera_t* pn_camera_create(vec3 pos, f32 fov, f32 znear, f32 zfar) {
	pn_camera_t* camera = malloc(sizeof(pn_camera_t));
	camera->m_fov = fov;
	camera->m_pitch = 0.f;
	camera->m_yaw = 0.f;
	camera->m_znear = znear;
	camera->m_zfar = zfar;

	__pn_cam_instance = camera;

	pn_v3_set(camera->m_pos, pos);
	pn_v3_set(camera->m_forward, PN_V3_FRONT);
	pn_v3_set(camera->m_up, PN_V3_UP);

	__pn_camera_update_queued = true;

	return camera;
}

void pn_camera_update(void) {
	if(!__pn_camera_update_queued) return;

	__pn_camera_update_queued = false;

	// Calulate the projection matrix.
	f32 aspect = (f32)__pn_window_instance->m_width / (f32)__pn_window_instance->m_height;
	glm_perspective(PN_DEG_TO_RAD(__pn_cam_instance->m_fov), aspect, __pn_cam_instance->m_znear, __pn_cam_instance->m_zfar, __pn_cam_instance->m_projection);

	// Calculate the forward direction based on pitch and yaw.
	f32 yaw_rad = glm_rad(__pn_cam_instance->m_yaw);
	f32 pitch_rad = glm_rad(__pn_cam_instance->m_pitch);

	__pn_cam_instance->m_forward[0] = cosf(yaw_rad) * cosf(pitch_rad);
	__pn_cam_instance->m_forward[1] = sinf(pitch_rad);
	__pn_cam_instance->m_forward[2] = sinf(yaw_rad) * cosf(pitch_rad);

	pn_v3_normalize(__pn_cam_instance->m_forward);
	pn_v3_cross(__pn_cam_instance->m_forward, __pn_cam_instance->m_up, __pn_cam_instance->m_right);
	pn_v3_normalize(__pn_cam_instance->m_right);

	// Calculate the look direction.	
	vec3 look_dir; 
	pn_v3_add(__pn_cam_instance->m_pos, __pn_cam_instance->m_forward, look_dir);

	// Calculate the view matrix.
	glm_mat4_identity(__pn_cam_instance->m_view);
	glm_lookat(__pn_cam_instance->m_pos, look_dir, __pn_cam_instance->m_up, __pn_cam_instance->m_view);

	pn_shader_program_bind(__pn_default_shader_program);
		glUniform3fv(__pn_default_shader_program->m_uniforms[UNI_CAMERA_POS], 1, __pn_cam_instance->m_pos);
	pn_shader_program_unbind();
}

void pn_camera_free(pn_camera_t* camera) {
	if(camera) {
		free(camera);
	}
}

void pn_camera_move(vec3 move_dir) {
	pn_v3_add(__pn_cam_instance->m_pos, move_dir, __pn_cam_instance->m_pos);

	__pn_camera_update_queued = true;
}

void pn_camera_rotate(f32 yaw, f32 pitch) {
	__pn_cam_instance->m_yaw += yaw;
	__pn_cam_instance->m_pitch += pitch;

	while(__pn_cam_instance->m_yaw > 360) __pn_cam_instance->m_yaw -= 360;
	while(__pn_cam_instance->m_yaw < -360) __pn_cam_instance->m_yaw += 360;

	if(__pn_cam_instance->m_pitch > 89.99f) __pn_cam_instance->m_pitch = 89.99f;
	if(__pn_cam_instance->m_pitch < -89.99f) __pn_cam_instance->m_pitch = -89.99f;

	__pn_camera_update_queued = true;
}
