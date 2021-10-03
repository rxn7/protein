#include "pn_math.h"

f64 pn_deg2rad(f64 deg) {
	return deg * PN_PI / 180.0;
}

f64 pn_rad2deg(f64 rad){
	return rad * 180.0 / PN_PI;
}

void pn_gl_perspective(f64 fov, f64 aspect, f64 znear, f64 zfar) {
	f64 f = 1.0 / tan(fov * PN_PI / 360);
	f64 xform[16] = {
		f / aspect, 0, 0, 0,
		0,		    f, 0, 0,
		0,			0, (zfar + znear) / (znear - zfar), -1,
		0,			0, 2*zfar*znear/(znear - zfar), 0
	};
	glMultMatrixd(xform);
}