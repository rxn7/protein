#include "pn/pn.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, const char* argv[]){
	if(!pn_init()) return -1;	

	pn_window_t* window = pn_create_window("Protein", 800, 640);

	pn_texture_t* texture = pn_create_texture("./res/Rotthin_Avatar.png");
	pn_bind_texture(texture);

	pn_render_object_t* quad = pn_create_primitive(PN_QUAD);

	__pn_cam_instance->m_pos[2] = -2;

	float counter=0.0f;
	while(pn_should_run()){
		pn_start_frame();

		quad->m_transform.m_rot[2] = counter;		
		quad->m_transform.m_rot[0] = counter;		
		pn_render_render_object(quad, 0);

		pn_end_frame();
	
		counter += __pn_delta_time;
	}

	pn_free_render_object(quad);
	pn_exit();

	return 0;
}