#include "stdafx.h"
#include "header.h"

bool Uint2CharIP(uint8_t* uIP, char* cIP) {
	sprintf(cIP, "%hhu.%hhu.%hhu.%hhu", uIP[0], uIP[1], uIP[2], uIP[3]);
	return RETURN_SUCCESS;
}