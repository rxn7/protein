#include "pn_util.h"
#include "pn_log.h"

#include <stdlib.h>
#include <stdio.h>

void pn_read_file(char** buff, const char* path) {
	long length;
	FILE* file = fopen(path, "r");

	if(!file){
		pn_log("Failed to read file %s!", path);
		return;
	}

	fseek(file, 0L, SEEK_END);
	length = ftell(file);
	rewind(file);

	*buff = calloc(1, length+1);
	if(!*buff) {
		fclose(file);
		pn_log("Failed to allocate buffer for file %s!", path);
		return;
	}

	if(fread(*buff, length, 1, file) != 1) {
		fclose(file);
		free(*buff);
		pn_log("Failed to read file %s!", path);
		return;
	}

	fclose(file);
}