#include "pn_vars.h"

pn_camera_t* __pn_camera_instance = 0;
pn_window_t* __pn_window_instance = 0;
bool __pn_pre_inited = false;
bool __pn_post_inited = false;
bool __pn_should_run = false;