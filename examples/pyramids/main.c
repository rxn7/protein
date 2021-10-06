#include "pn/pn.h"
#include "pn/pn_sys.h"
#include <stdlib.h>
#include <math.h>

int main(int argc, const char* argv[]){
	if(!pn_init()) return -1;	

	pn_window_t* window = pn_create_window("Protein", 800, 640);
	pn_texture_t* texture = pn_create_texture("./res/bricks.jpeg");
	pn_render_object_t* obj = pn_create_primitive(PN_PYRAMID);

	pn_lock_mouse();

	float counter=0.0f;
	while(pn_should_run()){
		pn_start_frame();

		// __pn_cam_instance->m_pos[2] = cosf(counter * 2) * 40 - 50;
		vec3 move_dir = {0, 0, 0};
		if(pn_is_key_pressed(PN_KEY_W)) move_dir[2] += __pn_cam_instance->m_forward[2];
		if(pn_is_key_pressed(PN_KEY_S)) move_dir[2] -= __pn_cam_instance->m_forward[2];
		if(pn_is_key_pressed(PN_KEY_A)) move_dir[0] -= __pn_cam_instance->m_right[0];
		if(pn_is_key_pressed(PN_KEY_D)) move_dir[0] += __pn_cam_instance->m_right[0];
		move_dir[0] *= __pn_delta_time * 2;
		move_dir[2] *= __pn_delta_time * 2;

		pn_move_camera(move_dir, true);

 		obj->m_transform.m_rot[1] = counter;

		glm_vec3_copy((vec3) { cosf(counter * 5) / 2 + 1, sinf(counter * 5) / 2 + 1, cosf(counter * 5) / 2 + 1 }, obj->m_transform.m_scale);

		int rows = 10;
		int cols = 10;

		int half_rows = rows/2;
		int half_cols = cols/2;		

		for(int x=-half_rows; x<half_rows; x++){
			for(int y=-half_cols; y<half_cols; y++){
				f32 red = (f32)(x + half_rows) / rows * 255;
				f32 green = (f32)(y + half_cols) / cols * 255;
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