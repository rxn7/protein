#pragma once

#include "pn_window.h"
#include "pn_camera.h"
#include <stdbool.h> 

extern pn_camera_t* __pn_cam_instance;
extern pn_window_t* __pn_window_instance;
extern bool __pn_pre_inited;
extern bool __pn_post_inited;
extern bool __pn_should_run;