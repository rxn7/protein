#include "pn_vars.h"

pn_shader_program_t* __pn_default_shader_program;
pn_camera_t* __pn_cam_instance = 0;
pn_window_t* __pn_window_instance = 0;
bool __pn_pre_inited = false;
bool __pn_post_inited = false;
bool __pn_should_run = false;
bool __pn_camera_update_queued = false;
f32 __pn_last_frame = 0.0f;
f32 __pn_delta_time = 0.0f;