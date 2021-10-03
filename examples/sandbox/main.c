#include "pn/pn.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, const char* argv[]){
	if(!pn_init()) return -1;	

	pn_window_t* window = pn_create_window("Protein", 800, 640);

	pn_vertex_t vertices[] = { 
		{{-1.0f,-1.0f,-1.0f, }},
		{{-1.0f,-1.0f, 1.0f,}},
		{{-1.0f, 1.0f, 1.0f,}},
		{{1.0f, 1.0f,-1.0f,}},
		{{-1.0f,-1.0f,-1.0f,}},
		{{-1.0f, 1.0f,-1.0f,}},
		{{1.0f,-1.0f, 1.0f,}},
		{{-1.0f,-1.0f,-1.0f,}},
		{{1.0f,-1.0f,-1.0f,}},
		{{1.0f, 1.0f,-1.0f,}},
		{{1.0f,-1.0f,-1.0f,}},
		{{-1.0f,-1.0f,-1.0f,}},
		{{-1.0f,-1.0f,-1.0f,}},
		{{-1.0f, 1.0f, 1.0f,}},
		{{-1.0f, 1.0f,-1.0f,}},
		{{1.0f,-1.0f, 1.0f,}},
		{{-1.0f,-1.0f, 1.0f,}},
		{{-1.0f,-1.0f,-1.0f,}},
		{{-1.0f, 1.0f, 1.0f,}},
		{{-1.0f,-1.0f, 1.0f,}},
		{{1.0f,-1.0f, 1.0f,}},
		{{1.0f, 1.0f, 1.0f,}},
		{{1.0f,-1.0f,-1.0f,}},
		{{1.0f, 1.0f,-1.0f,}},
		{{1.0f,-1.0f,-1.0f,}},
		{{1.0f, 1.0f, 1.0f,}},
		{{1.0f,-1.0f, 1.0f,}},
		{{1.0f, 1.0f, 1.0f,}},
		{{1.0f, 1.0f,-1.0f,}},
		{{-1.0f, 1.0f,-1.0f,}},
		{{1.0f, 1.0f, 1.0f,}},
		{{-1.0f, 1.0f,-1.0f,}},
		{{-1.0f, 1.0f, 1.0f,}},
		{{1.0f, 1.0f, 1.0f,}},
		{{-1.0f, 1.0f, 1.0f,}},
		{{1.0f,-1.0f, 1.0f}},
	};
	pn_render_object_t* object = pn_create_render_object(vertices, 12*3);

	__pn_cam_instance->m_pos[2] = -5;
	__pn_cam_instance->m_pos[1] = 2;
	__pn_cam_instance->m_forward[1] = -0.5f;

	float counter=0.0f;
	while(pn_should_run()){
		pn_start_frame();

		object->m_transform.m_rot[1] = counter * 2;

		pn_render_render_object(object, 0);

		pn_end_frame();
	
		counter += __pn_delta_time;
	}

	pn_free_render_object(object);
	pn_exit();

	return 0;
}