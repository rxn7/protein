#include "pn_camera.h"
#include "pn_vars.h"

void pn_calc_cam_perspective(f32 fov, f32 znear, f32 zfar, pn_camera_t* cam) {
	if(cam == 0) cam = __pn_camera_instance;

	f32 aspect = (f32)__pn_window_instance->m_width / __pn_window_instance->m_height;
	glm_perspective(pn_deg2rad(fov), aspect, znear, zfar, cam->m_proj_mat);
}