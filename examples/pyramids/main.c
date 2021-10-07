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

		vec3 move_dir = {0, 0, 0};
		if(pn_is_key_pressed(PN_KEY_W)) glm_vec3_add(move_dir, __pn_cam_instance->m_forward, move_dir);
		if(pn_is_key_pressed(PN_KEY_S)) glm_vec3_sub(move_dir, __pn_cam_instance->m_forward, move_dir);
		if(pn_is_key_pressed(PN_KEY_A)) glm_vec3_sub(move_dir, __pn_cam_instance->m_right, move_dir);
		if(pn_is_key_pressed(PN_KEY_D)) glm_vec3_add(move_dir, __pn_cam_instance->m_right, move_dir);
		glm_vec3_normalize(move_dir); 
		pn_vec3_mult_each(move_dir, __pn_delta_time * 10);
		pn_move_camera(move_dir);

		f32 rotate_speed = __pn_delta_time * 200;
		if(pn_is_key_pressed(PN_KEY_LEFT)) pn_rotate_camera(-rotate_speed, 0);	
		if(pn_is_key_pressed(PN_KEY_RIGHT)) pn_rotate_camera(rotate_speed, 0);	
		if(pn_is_key_pressed(PN_KEY_UP)) pn_rotate_camera(0, rotate_speed);	
		if(pn_is_key_pressed(PN_KEY_DOWN)) pn_rotate_camera(0, -rotate_speed);	

 		obj->m_transform.m_rot[1] = counter;

		glm_vec3_copy((vec3) { cosf(counter * 5) / 2 + 1, sinf(counter * 5) / 2 + 1, cosf(counter * 5) / 2 + 1 }, obj->m_transform.m_scale);

		int max_x = 10;
		int max_y = 10;
		int max_z = 10;

		int half_x = max_x/2;
		int half_y = max_y/2;		
		int half_z = max_z/2;

		for(int x=-half_x; x<half_x; x++){
			for(int y=-half_y; y<half_y; y++){
				for(int z=-half_z; z<half_z; z++){
					f32 red = (f32)(x + half_x) / max_x * 255;
					f32 green = (f32)(y + half_y) / max_y * 255;
					f32 blue = (f32)(z + half_z) / max_z * 255;
					obj->m_color = (pn_color_t) {red, green, blue, 255};
					
					obj->m_transform.m_pos[0] = x * 4;
					obj->m_transform.m_pos[1] = y * 4;
					obj->m_transform.m_pos[2] = z * 4;
					pn_render_render_object(obj, 0, texture);
				}
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