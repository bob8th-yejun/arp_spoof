#include "stdafx.h"
#include "header.h"

bool Char2UintIP(char* cIP, uint8_t* uIP) {
	sscanf(cIP, "%hhu.%hhu.%hhu.%hhu", &uIP[0], &uIP[1], &uIP[2], &uIP[3]);
	return RETURN_SUCCESS;
}