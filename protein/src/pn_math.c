#include "pn_math.h"

f64 pn_deg2rad(f64 deg) {
	return deg * PN_PI / 180.0;
}

f64 pn_rad2deg(f64 rad){
	return rad * 180.0 / PN_PI;
}