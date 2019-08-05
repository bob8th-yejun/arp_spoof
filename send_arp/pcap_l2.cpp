#include "stdafx.h"
#include "header.h"

bool makeL2Ethernet(L2Ethernet* eth, uint8_t* dMac, uint8_t* sMac, uint16_t ethType) {
	memcpy(eth->dMac, dMac, sizeof(uint8_t) * 6);
	memcpy(eth->sMac, sMac, sizeof(uint8_t) * 6);
	eth->ethType = ethType;
	return RETURN_SUCCESS;
}

bool parseL2Ethernet(L2Ethernet* eth, uint8_t* dMac, uint8_t* sMac, uint16_t ethType) {
	memcpy(dMac, eth->dMac, sizeof(uint8_t) * 6);
	memcpy(sMac, eth->sMac, sizeof(uint8_t) * 6);
	ethType = eth->ethType;
	return RETURN_SUCCESS;
}