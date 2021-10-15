#include "pn/pn.h"

#define MOVE_SPEED 10

int main(int argc, const char* argv[]){
	if(!pn_init("Protein", 800, 640)) return -1;

	// Set the clear color to light gray.
	pn_set_clear_color((pn_color_t){ 80, 80, 80, 255});
	
    pn_enable_mouse_camera_movement();
	pn_lock_mouse();
	
    pn_render_object_t* obj = pn_create_primitive_render_object(PN_TRIANGLE);
	obj->m_color = (pn_color_t){100, 100, 100, 255};

	pn_render_object_t* light = pn_create_primitive_render_object(PN_TRIANGLE);
	light->m_color = (pn_color_t){0, 255, 0, 255};
	light->m_use_light = false;


	f32 counter=0.0f;
	f32* move_dir;
	f32* forward;
	f32* right;

	// Game loop
	while(pn_should_run()){
		// You need to call this at the start of every frame.
		// This function clears the buffers, calculates the time delta between frames and poll the events. 
		pn_start_frame();

		forward = (v3){ __pn_cam_instance->m_forward[0], 0, __pn_cam_instance->m_forward[2] };
		right = (v3){ __pn_cam_instance->m_right[0], 0, __pn_cam_instance->m_right[2] };
		move_dir = (v3) {0,0,0};

		// Front, left, right, back movement.
		if(pn_is_key_pressed(PN_KEY_W)) pn_v3_add(move_dir, forward, move_dir);
		if(pn_is_key_pressed(PN_KEY_S)) pn_v3_sub(move_dir, forward, move_dir);
		if(pn_is_key_pressed(PN_KEY_A)) pn_v3_sub(move_dir, right, move_dir);
		if(pn_is_key_pressed(PN_KEY_D)) pn_v3_add(move_dir, right, move_dir);

		// Up, down movement.
		if(pn_is_key_pressed(PN_KEY_SPACE)) pn_v3_add(move_dir, (v3){0,1,0}, move_dir);
		if(pn_is_key_pressed(PN_KEY_LEFT_SHIFT)) pn_v3_add(move_dir, (v3){0,-1,0}, move_dir);

		pn_v3_normalize(move_dir);

		// We multiply each element of move_dir by delta time to make the movement speed framerate-independent.
		pn_v3_mult_each(move_dir, __pn_delta_time * MOVE_SPEED);
		pn_move_camera(move_dir);

		const static int MAX = 20;
		const static int HALF = MAX/2;

		obj->m_transform.m_rot[1] = counter;

		light->m_transform.m_pos[0] = sinf(counter * 20) * 5;
		light->m_transform.m_pos[1] = cosf(counter * 20) * 5;
		light->m_transform.m_pos[2] = cosf(counter * 20) * 5;

		pn_set_light_pos(light->m_transform.m_pos);

		// Render the object multiple times in each direction.
		for(int x=-HALF; x<HALF; x++){
			for(int y=-HALF; y<HALF; y++){
				for(int z=-HALF; z<HALF; z++){
					// Set the obj's position.
					pn_v3_set(obj->m_transform.m_pos, (v3){x,y,z});
					pn_v3_mult_each(obj->m_transform.m_pos, 3.5);

					// Render the render object.
					pn_render_render_object(obj, 0, 0);
				}
			}
		}

		pn_render_render_object(light, 0, 0);

		// You need to call this at the end of every frame.
		// This function swaps the screen buffer.
		pn_end_frame();

		counter += __pn_delta_time / 10;
	}

	// You need to free each object created with pn_create_render_object or pn_create_primitive_render_object.
	pn_free_render_object(obj);
	pn_free_render_object(light);

	// This function closes the window and cleans up the memory allocated by protein.
	pn_exit();

	return 0;
}
