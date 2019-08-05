#include "stdafx.h"
#include "header.h"

bool MakeL2Ethernet(L2Ethernet* eth, const uint8_t* dMac, const uint8_t* sMac, const uint16_t ethType) {
	memcpy(eth->dMac, dMac, sizeof(uint8_t) * 6);
	memcpy(eth->sMac, sMac, sizeof(uint8_t) * 6);
	eth->ethType = htons(ethType);
	return RETURN_SUCCESS;
}

bool ParseL2Ethernet(const L2Ethernet* eth, uint8_t* dMac, uint8_t* sMac, uint16_t ethType) {
	memcpy(dMac, eth->dMac, sizeof(uint8_t) * 6);
	memcpy(sMac, eth->sMac, sizeof(uint8_t) * 6);
	ethType = ntohs(eth->ethType);
	return RETURN_SUCCESS;
}

bool ParseL2EthernetType(const L2Ethernet* eth, uint16_t* ethType) {
	*ethType = ntohs(eth->ethType);
	return RETURN_SUCCESS;
}