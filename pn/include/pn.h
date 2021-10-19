#pragma once

#include "pn_texture.h"
#include "pn_transform.h"
#include "pn_common.h"
#include "pn_color.h"
#include "pn_window.h"
#include "pn_render.h"
#include "pn_shader.h"
#include "pn_input.h"
#include "pn_init.h"
#include "pn_math.h"
#include "pn_util.h"
#include "pn_log.h"
#include "pn_vars.h"

bool pn_should_run(void);
void pn_exit(void);

void pn_start_frame(void);
void pn_end_frame(void);