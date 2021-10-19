#pragma once

#include "pn_window.h"
#include "pn_camera.h"
#include "pn_shader.h"
#include <stdbool.h> 

extern pn_camera_t* __pn_cam_instance;
extern pn_window_t* __pn_window_instance;
extern pn_shader_program_t* __pn_default_shader_program;
extern bool __pn_pre_inited;
extern bool __pn_post_inited;
extern bool __pn_camera_update_queued;
extern bool __pn_should_run;
extern bool __pn_camera_mouse_movement;
extern f32 __pn_last_frame;
extern f32 __pn_delta_time;
extern f32 __pn_mouse_x;
extern f32 __pn_mouse_y;
extern f32 __pn_mouse_sens;