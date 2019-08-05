#pragma once

#include "type.h"

#define RETURN_SUCCESS	false
#define RETURN_ERROR	true

// char_2_uint.cpp
bool Char2UintIP(char* cIP, uint8_t* uIP);

// uint_2_char.cpp
bool Uint2CharIP(uint8_t* uIP, char* cIP);

// pcap_l2.cpp
bool makeL2Ethernet(L2Ethernet* eth, uint8_t* dMac, uint8_t* sMac, uint16_t ethType);
bool parseL2Ethernet(L2Ethernet* eth, uint8_t* dMac, uint8_t* sMac, uint16_t ethType);

// pacp_l3.cpp
bool makeL3Arp(L3Arp* arp, uint16_t opCode, uint8_t* sMac, uint8_t* sIP, uint8_t* dMac, uint8_t* dIP);
bool parseL3Arp(L3Arp* arp, uint16_t opCode, uint8_t* sMac, uint8_t* sIP, uint8_t* dMac, uint8_t* dIP);

// pcap_recv.cpp
bool pacpRecv();

// pcap_send.cpp
bool pcapSend(uint8_t* packet);

// check.cpp

// getmac.cpp
bool GetMac(uint8_t* mac);
bool ArpGetMac(uint8_t *ip, uint8_t* mac);