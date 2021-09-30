#pragma once

#include "pn_common.h"

#include "pn_vars.h"
#include "pn_camera.h"
#include "pn_color.h"
#include "pn_window.h"
#include "pn_render.h"
#include "pn_input.h"
#include "pn_init.h"
#include "pn_math.h"
#include "pn_log.h"

bool pn_should_run();
void pn_exit();

void pn_start_frame();
void pn_end_frame();