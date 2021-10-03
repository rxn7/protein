#include "pn/pn.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, const char* argv[]){
	if(!pn_init()) return -1;	

	pn_window_t* window = pn_create_window("Protein", 800, 640);

	pn_vertex_t vertices[] = { 
		{ {-0.5f, -0.5f,  -0.5f} },
		{ {  0.0f, 0.5f,  -0.5f} },
		{ { 0.5f, -0.5f,  -0.5f} },
	 };
	pn_render_object_t* triangle = pn_create_render_object(vertices, 3);

	char* vert_src;
	char* frag_src;
	
	pn_read_file(&vert_src, "res/vert.glsl");
	pn_read_file(&frag_src, "res/frag.glsl");

	pn_shader_program_t* shader = pn_create_shader_program(vert_src, frag_src);
	
	free(vert_src);
	free(frag_src);

	float counter=0.0f;

	while(pn_should_run()){
		pn_start_frame();

		triangle->m_transform.m_pos[0] = cosf(counter) / 2.f;
		triangle->m_transform.m_pos[1] = sinf(counter) / 2.f;

		pn_render_render_object(triangle, shader);

		pn_end_frame();
	
		counter += 0.1f;
	}

	pn_free_shader_program(shader);
	pn_free_render_object(triangle);

	pn_exit();

	return 0;
}