#include "pn/pn.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, const char* argv[]){
	if(!pn_init()) return -1;	

	pn_window_t* window = pn_create_window("Protein", 800, 640);
	pn_texture_t* texture = pn_create_texture("./res/bricks.jpeg");
	pn_render_object_t* obj = pn_create_primitive(PN_PYRAMID);

	float counter=0.0f;
	while(pn_should_run()){
		pn_start_frame();

		__pn_cam_instance->m_pos[2] = cosf(counter * 2) * 40 - 50;
		
 		obj->m_transform.m_rot[1] = counter;		
        obj->m_transform.m_scale[0] = cosf(counter * 5) / 2 + 1;
        obj->m_transform.m_scale[1] = sinf(counter * 5) / 2 + 1;
        obj->m_transform.m_scale[2] = cosf(counter * 5) / 2 + 1;

		for(int x=-30; x<30; x++){
			for(int y=-30; y<30; y++){
				f32 red = (f32)(x + 30) / 60 * 255;
				f32 green = (f32)(y + 30) / 60 * 255;
				obj->m_color = (pn_color_t) {red, green, 255, 255};
				
				obj->m_transform.m_pos[0] = x * 4;
				obj->m_transform.m_pos[1] = y * 4;
				pn_render_render_object(obj, 0, texture);
			}
		}

		pn_end_frame();
	
		counter += __pn_delta_time;
	}

	pn_free_render_object(obj);
	pn_free_texture(texture);
	pn_exit();

	return 0;
}
