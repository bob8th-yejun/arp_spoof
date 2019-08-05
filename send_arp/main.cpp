#include "stdafx.h"
#include "header.h"

#define DEV

int main(int argc, char* argv[]) {
#ifdef DEV
	char adapter[]	= "wlan0";
	char cSenderIP[] = "192.168.0.254";
	char cTargetIP[] = "192.168.3.63";
#else
	if (argc != 4) {
		puts("인자가 올바르게 입력되지 않았습니다!");
		puts("아래와 같이 입력 후 다시 실행해주세요!");
		puts("send_arp.exe <interface명> <sender ip> <target ip>");
		puts("(ex) send_arp.exe wlan0 192.168.0.1 192.168.0.100");
		return -1;
	} else {
		char* adapter = argv[2];
		char* cSenderIP = argv[3];
		char* cTargetIP = argv[4];
	}
#endif
	uint8_t sendeIP[4], targetIP[4];
	if (Char2UintIP(cSenderIP, sendeIP));
	if (Char2UintIP(cTargetIP, targetIP));
	GetMac(nullptr);
}