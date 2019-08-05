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
		puts("���ڰ� �ùٸ��� �Էµ��� �ʾҽ��ϴ�!");
		puts("�Ʒ��� ���� �Է� �� �ٽ� �������ּ���!");
		puts("send_arp.exe <interface��> <sender ip> <target ip>");
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