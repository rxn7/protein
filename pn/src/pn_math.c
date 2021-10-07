#include "pn_math.h"

void pn_vec3_mult_each(vec3 vec, float value) {
	for(u8 i=0; i<3; i++) vec[i] *= value;
}