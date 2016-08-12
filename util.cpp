#include "util.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <stdint.h>

// 	double xd = long2tilexd(40.347379, level) - x;
// 	double yd = lat2tileyd(56.116962, level) - y;
// 
// 	int xp = (int)std::round(xd * 256);
// 	int yp = (int)std::round(yd * 256);

int long2tilex(double lon, int z)
{
	return (int)(floor((lon + 180.0) / 360.0 * pow(2.0, z)));
}

int lat2tiley(double lat, int z)
{
	return (int)(floor((1.0 - log(tan(lat * M_PI / 180.0) + 1.0 / cos(lat * M_PI / 180.0)) / M_PI) / 2.0 * pow(2.0, z)));
}

int32_t long2tilexd(double lon, int z)
{
	double t = (lon + 180.0) / 360.0 * pow(2.0, z);
	return static_cast<int32_t>(std::round((t - static_cast<int32_t>(t)) * 256));
}

int32_t lat2tileyd(double lat, int z)
{
	double t = (1.0 - log(tan(lat * M_PI / 180.0) + 1.0 / cos(lat * M_PI / 180.0)) / M_PI) / 2.0 * pow(2.0, z);
	return static_cast<int32_t>(std::round((t - static_cast<int32_t>(t)) * 256));
}

double tilex2long(int x, int z)
{
	return x / pow(2.0, z) * 360.0 - 180;
}

double tiley2lat(int y, int z)
{
	double n = M_PI - 2.0 * M_PI * y / pow(2.0, z);
	return 180.0 / M_PI * atan(0.5 * (exp(n) - exp(-n)));
}
