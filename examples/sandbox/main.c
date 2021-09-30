#include "pn/pn.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[]){
	if(!pn_init()) return -1;	

	pn_window_t* window = pn_create_window("Protein", 640, 480);
	
	while(pn_should_run()){
		pn_start_frame();

		pn_end_frame();
	}

	pn_exit();

	return 0;
}