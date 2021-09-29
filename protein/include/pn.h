#pragma once

#include "pn_color.h"
#include "pn_window.h"
#include "pn_common.h"
#include "pn_input.h"

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


void pn_set_clear_color(pn_color_t color);