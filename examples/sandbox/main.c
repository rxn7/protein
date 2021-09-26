#include "pn/pn.h"
#include <stdio.h>

int main(int argc, const char* argv[]){
	if(!pn_init()){
		printf("we completely fucked completely fucked");
		return -1;	
	}

	pn_window_t* window = pn_create_window("Protein", 640, 480);
	while(1){}

	return 0;
}