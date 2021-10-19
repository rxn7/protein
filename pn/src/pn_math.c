#include "pn_math.h"

void pn_v2_mult_each(v2 vec, float value) {
	vec[0] *= value;
	vec[1] *= value;
}

void pn_v3_mult_each(v3 vec, float value) {
	vec[0] *= value;
	vec[1] *= value;
	vec[2] *= value;
}

void pn_v2_div_each(v2 vec, float value) {
	vec[0] /= value;
	vec[1] /= value;
}

void pn_v3_div_each(v3 vec, float value) {
	vec[0] /= value;
	vec[1] /= value;
	vec[2] /= value;
}

void pn_v2_set(v2 vec, v2 value) {
	vec[0] = value[0];
	vec[1] = value[1];
}

void pn_v3_set(v3 vec, v3 value) {
	vec[0] = value[0];
	vec[1] = value[1];
	vec[2] = value[2];
}

void pn_v2_normalize(v2 vec) {
	f32 mag = pn_v2_get_magnitude(vec);

	if(mag != 0) {
		pn_v2_div_each(vec, mag);
	}else {
		pn_v2_set(vec, (v2){0,0});
	}
}

void pn_v3_normalize(v3 vec) {
	f32 mag = pn_v3_get_magnitude(vec);

	if(mag != 0) {
		pn_v3_div_each(vec, mag);
	}else {
		pn_v3_set(vec, (v3){0,0,0});
	}
}

f32 pn_v2_get_magnitude(v2 vec) {
	return sqrtf(vec[0] * vec[0] + vec[1] * vec[1]);
}

f32 pn_v3_get_magnitude(v3 vec) {
	return sqrtf(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}

void pn_v2_add(v2 a, v2 b, v2 dest) {
	dest[0] = a[0] + b[0];
	dest[1] = a[1] + b[1];
}

void pn_v2_sub(v2 a, v2 b, v2 dest) {
	dest[0] = a[0] - b[0];
	dest[1] = a[1] - b[1];
}

void pn_v3_add(v3 a, v3 b, v3 dest) {
	dest[0] = a[0] + b[0];
	dest[1] = a[1] + b[1];
	dest[2] = a[2] + b[2];
}

void pn_v3_sub(v3 a, v3 b, v3 dest) {
	dest[0] = a[0] - b[0];
	dest[1] = a[1] - b[1];
	dest[2] = a[2] - b[2];
}

void pn_v3_cross(v3 a, v3 b, v3 dest) {
    v3 result = {a[1]*b[2] - a[2]*b[1], a[0]*b[2] - a[2]*b[0], a[0]*b[1] - a[1]*b[0]};
    pn_v3_set(dest, result);
}

void pn_v3_normal(v3 a, v3 b, v3 c, v3 dest) {
    v3 x = {b[0]-a[0], b[1]-a[1], b[2]-a[2]};
    v3 y = {c[0]-a[0], c[1]-a[1], c[2]-a[2]};

    pn_v3_cross(x, y, dest);
    pn_v3_normalize(dest);
}
