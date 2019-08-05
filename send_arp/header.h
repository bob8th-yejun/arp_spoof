#pragma once

#include "type.h"

#define RETURN_SUCCESS			false
#define RETURN_ERROR			true

#define SIZE_ETHERNET_HEADER	14
#define SIZE_ARP_HEADER			28

#define ETH_TYPE_ARP			0x0806

#define ARP_OPCODE_REQUEST		1
#define ARP_OPCODE_REPLY		2

// char_2_uint.cpp
bool Char2UintIP(char* cIP, uint8_t* uIP);

// uint_2_char.cpp
bool Uint2CharIP(uint8_t* uIP, char* cIP);

// pcap_l2.cpp
bool MakeL2Ethernet(L2Ethernet* eth, const uint8_t* dMac, const uint8_t* sMac, const uint16_t ethType);
bool ParseL2Ethernet(const L2Ethernet* eth, uint8_t* dMac, uint8_t* sMac, uint16_t ethType);
bool ParseL2EthernetType(const L2Ethernet* eth, uint16_t* ethType);

// pacp_l3.cpp
bool MakeL3Arp(L3Arp* arp, const uint16_t opCode, const uint8_t* sMac, const uint8_t* sIP, const uint8_t* dMac, const uint8_t* dIP);
bool ParseL3Arp(const L3Arp* arp, uint16_t opCode, uint8_t* sMac, uint8_t* sIP, uint8_t* dMac, uint8_t* dIP);
bool ParseL3ArpReply(const L3Arp* arp, uint16_t* opCode, uint8_t* sIP, uint8_t* sMac);

// pcap_init.cpp
pcap_t* PcapInit(char* adapter);
bool PcapAdapterListPrint();

// pcap_recv.cpp
bool PcapRecv(pcap_t* handle);
bool PcapRecvArpReply(pcap_t* handle, const uint8_t* ip, uint8_t* mac);


// pcap_send.cpp
bool PcapSend(pcap_t* handle, uint8_t* packet, int len);

// check.cpp

// get_ip.cpp
int GetIP(char* adapter, uint8_t* ip);

// get_mac.cpp
bool GetMac(char* adapter, uint8_t* mac);
bool ArpGetMac(pcap_t* handle, const uint8_t* myMac, const uint8_t* myIP, const uint8_t* ip, uint8_t* mac);
int get_mac_address(pcap_if_t *d, u_char mac_addr[6]);
int compare_guid(wchar_t *, wchar_t *);