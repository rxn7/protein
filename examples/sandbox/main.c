#include "pn/pn.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, const char* argv[]){
	if(!pn_init()) return -1;	

	pn_window_t* window = pn_create_window("Protein", 800, 640);

	pn_render_object_t* triangle = pn_create_triangle();

	pn_render_object_t* quad = pn_create_quad();
	quad->m_color = (pn_color_t){255, 0, 0, 255};
	quad->m_transform.m_pos[1] = 2;

	__pn_cam_instance->m_pos[2] = -5;
	__pn_cam_instance->m_pos[1] = 2;
	__pn_cam_instance->m_forward[1] = -0.5f;

	float counter=0.0f;
	while(pn_should_run()){
		pn_start_frame();

		triangle->m_transform.m_rot[1] = counter * 2;
		quad->m_transform.m_rot[2] = counter * 2;
		pn_render_render_object(quad, 0);

		pn_render_render_object(triangle, 0);

		pn_end_frame();
	
		counter += __pn_delta_time;
	}

	pn_free_render_object(triangle);
	pn_free_render_object(quad);
	pn_exit();

	return 0;
}