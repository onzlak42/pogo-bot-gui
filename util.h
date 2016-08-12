#pragma once

#include <stdint.h>

int long2tilex(double lon, int z);

int lat2tiley(double lat, int z);

int32_t long2tilexd(double lon, int z);

int32_t lat2tileyd(double lat, int z);

double tilex2long(int x, int z);

double tiley2lat(int y, int z);
