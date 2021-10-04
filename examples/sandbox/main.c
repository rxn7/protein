#include "pn/pn.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, const char* argv[]){
	if(!pn_init()) return -1;	

	pn_window_t* window = pn_create_window("Protein", 800, 640);

	__pn_cam_instance->m_pos[2] = -5;

	pn_render_object_t* triangle = pn_create_primitive(PN_TRIANGLE);
	triangle->m_color = (pn_color_t){255, 0, 0, 70};
	triangle->m_transform.m_scale[0] = 2;
	triangle->m_transform.m_scale[1] = 2;

	pn_render_object_t* quad = pn_create_primitive(PN_QUAD);
	quad->m_color = (pn_color_t){0, 255, 0, 255};

	float counter=0.0f;
	while(pn_should_run()){
		pn_start_frame();
		
		triangle->m_transform.m_pos[2] = cosf(counter * 5);
		pn_render_render_object(quad, 0);
		pn_render_render_object(triangle, 0);

		pn_end_frame();
	
		counter += __pn_delta_time;
	}

	pn_free_render_object(quad);
	pn_free_render_object(triangle);
	pn_exit();

	return 0;
}