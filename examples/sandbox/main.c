#include "pn/pn.h"
#include "pn/pn_sys.h"
#include "pn/pn_sys.h"

#define MOVE_SPEED 10

int main(int argc, const char* argv[]){
	if(!pn_init("Protein", 800, 640)) return -1;

	// Set the clear color to light gray.
	pn_set_clear_color((pn_color_t){ 80, 80, 80, 255});
	
    pn_camera_movement_enable();
	pn_mouse_lock();
	
    pn_render_object_t* floor = pn_primitive_render_object_create(PN_QUAD_ONE_FACE);
	floor->m_transform.m_scale[0] = 10;
	floor->m_transform.m_scale[1] = 10;
    floor->m_transform.m_pos[1] = -3;
    floor->m_transform.m_rot[0] = PN_DEG_TO_RAD(90);
    floor->m_color = (pn_color_t){100, 100, 100, 255};

	pn_render_object_t* light = pn_primitive_render_object_create(PN_QUAD);
	light->m_color = (pn_color_t){0, 255, 0, 255};
	light->m_use_light = false;

	f32 counter=0.0f;
	f32* move_dir;
	f32* forward;
	f32* right;

	// Game loop
	while(pn_should_run()){
		pn_start_frame();

		forward = (v3){ __pn_cam_instance->m_forward[0], 0, __pn_cam_instance->m_forward[2] };
		right = (v3){ __pn_cam_instance->m_right[0], 0, __pn_cam_instance->m_right[2] };
		move_dir = (v3) {0,0,0};

		if(pn_is_key_pressed(PN_KEY_W)) pn_v3_add(move_dir, forward, move_dir);
		if(pn_is_key_pressed(PN_KEY_S)) pn_v3_sub(move_dir, forward, move_dir);
		if(pn_is_key_pressed(PN_KEY_A)) pn_v3_sub(move_dir, right, move_dir);
		if(pn_is_key_pressed(PN_KEY_D)) pn_v3_add(move_dir, right, move_dir);
		if(pn_is_key_pressed(PN_KEY_SPACE)) 	 pn_v3_add(move_dir, PN_V3_UP, move_dir);
		if(pn_is_key_pressed(PN_KEY_LEFT_SHIFT)) pn_v3_add(move_dir, PN_V3_DOWN, move_dir);

		pn_v3_normalize(move_dir);

		// We multiply each element of move_dir by delta time to make the movement speed framerate-independent.
		pn_v3_mult_each(move_dir, __pn_delta_time * MOVE_SPEED);
		pn_camera_move(move_dir);

		const static int MAX = 20;
		const static int HALF = MAX/2;

		light->m_transform.m_pos[0] = sinf(counter * 20) * 5;
		light->m_transform.m_pos[2] = cosf(counter * 20) * 5;

		pn_light_set_pos(light->m_transform.m_pos);

		pn_render_object_draw(floor, 0, 0);
		pn_render_object_draw(light, 0, 0);

		pn_end_frame();

		counter += __pn_delta_time / 10;
	}

	pn_render_object_free(floor);
	pn_render_object_free(light);

	pn_exit();

	return 0;
}
