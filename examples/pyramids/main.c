#include "pn/pn.h"
#include "pn/pn_sys.h"
#include <stdlib.h>
#include <math.h>

int main(int argc, const char* argv[]){
	if(!pn_init()) return -1;
	pn_create_window("Protein", 800, 640);

	pn_render_object_t* obj = pn_create_primitive(PN_PYRAMID);

	pn_set_clear_color((pn_color_t){ 80, 80, 80, 255});
	
	pn_lock_mouse();
	pn_enable_mouse_camera_movement();

	__pn_cam_instance->m_pos[2] = -100;

	float counter=0.0f;
	while(pn_should_run()){
		pn_start_frame();

		v3 move_dir = {0, 0, 0};
		if(pn_is_key_pressed(PN_KEY_W)) glm_vec3_add(move_dir, __pn_cam_instance->m_forward, move_dir);
		if(pn_is_key_pressed(PN_KEY_S)) glm_vec3_sub(move_dir, __pn_cam_instance->m_forward, move_dir);
		if(pn_is_key_pressed(PN_KEY_A)) glm_vec3_sub(move_dir, __pn_cam_instance->m_right, move_dir);
		if(pn_is_key_pressed(PN_KEY_D)) glm_vec3_add(move_dir, __pn_cam_instance->m_right, move_dir);

		// glm_vec3_normalize(move_dir); 
		pn_v3_normalize(move_dir);
		pn_v3_mult_each(move_dir, __pn_delta_time * 10);

		pn_move_camera(move_dir);

 		obj->m_transform.m_rot[1] = counter;

		f32 scale = cosf(counter * 10) / 2 + 1;
		pn_v3_set(obj->m_transform.m_scale, (v3){scale, scale, scale});

		const static int MAX = 10;
		const static int HALF = MAX/2;

		for(int x=-HALF; x<HALF; x++){
			for(int y=-HALF; y<HALF; y++){
				for(int z=-HALF; z<HALF; z++){
					f32 red = (f32)(x + HALF) / MAX * 255;
					f32 green = (f32)(y + HALF) / MAX * 255;
					f32 blue = (f32)(z + HALF) / MAX * 255;
					obj->m_color = (pn_color_t) {red, green, blue, 255};

					pn_v3_set(obj->m_transform.m_pos, (v3){x,y,z});
					// glm_vec3_copy((vec3) {x,y,z}, obj->m_transform.m_pos);
					pn_v3_mult_each(obj->m_transform.m_pos, 4);

					// Render the render object.
					pn_render_render_object(obj, 0, 0);
				}
			}
		}

		pn_end_frame();

		counter += __pn_delta_time;
	}

	pn_free_render_object(obj);
	pn_exit();

	return 0;
}