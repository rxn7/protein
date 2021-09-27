#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "pn_window.h"
#include "pn_common.h"

/*
	This function should be called at the beginning of the program to initialize the Protein library.
*/
bool pn_init();


/*
	This function should be used to check if the main loop should continue.
	Example:

	while(pn_should_run()){
		pn_start_frame();
		pn_end_frame();
	}
*/
bool pn_should_run();


/*
	Call this function when you want to exit the program.
*/
void pn_exit();

/*
	You should call this at the beginning of your main loop / before rendering. 
*/
void pn_start_frame();


/*
	You should call this at the end of your main loop.
*/
void pn_end_frame();

void pn_draw_rect(f32 x, f32 y, f32 w, f32 h);