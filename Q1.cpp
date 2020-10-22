#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

void cpuid(int CPUInfo[4], int InfoType, int SubInfo)
{
	__asm__ __volatile__(
		"cpuid":
	    "=a" (CPUInfo[0]),
		"=b" (CPUInfo[1]),
		"=c" (CPUInfo[2]),
		"=d" (CPUInfo[3]) :
		"a" (InfoType),
		"c" (SubInfo)
		);
}

int main(void)
{
	int info[4];
	bool MMX   = false;
	bool SSE   = false;
	bool SSE2  = false;
	bool SSE3  = false;
	bool AES   = false;
	bool SSE41 = false;
	bool SSE42 = false;
	bool AVX   = false;
	bool AVX2  = false;
	bool SHA   = false;
	string vendor;
	string model;
	int smt;
	int cores;
	int logicalCores;

	cpuid(info, 0x00000000, 0x00000000);
    uint32_t HFS = info[0];
    vendor += string((const char *)&info[1], 4);
    vendor += string((const char *)&info[3], 4);
    vendor += string((const char *)&info[2], 4);

    for(int i=0x80000002; i<0x80000005; ++i)
    {
        cpuid(info, i, 0x00000000);
        model += string((const char*)&info[0], 4);
        model += string((const char*)&info[1], 4);
        model += string((const char*)&info[2], 4);
        model += string((const char*)&info[3], 4);
    }

    for (int lvl=0; lvl<4; ++lvl)
    {
    	cpuid(info, 0x0B, lvl);
        uint32_t currLevel = (0x0000FF00 & info[2])>>8;
        switch(currLevel)
        {
            case 0x01: smt     = 0x0000FFFF & info[1]; break;
            case 0x02: logicalCores = 0x0000FFFF & info[1]; break;
            default: break;
        }
    }
    cores = logicalCores/smt;

	cpuid(info, 0x00000001, 0x00000000);

	MMX   = (info[3] & ((int)1 << 23)) != 0;

	SSE   = (info[3] & ((int)1 << 25)) != 0;
	SSE2  = (info[3] & ((int)1 << 26)) != 0;
	SSE3  = (info[2] & ((int)1 << 0))  != 0;
	AES   = (info[2] & ((int)1 << 25)) != 0;
	SSE41 = (info[2] & ((int)1 << 19)) != 0;
	SSE42 = (info[2] & ((int)1 << 20)) != 0;

	AVX   = (info[2] & ((int)1 << 28)) != 0;

	cpuid(info, 0x80000000,  0x00000000);
	if (info[0] >= 0x00000007){
		cpuid(info, 0x00000007 , 0x00000000);
		AVX2   = (info[1] & ((int)1 <<  5)) != 0;
		SHA    = (info[1] & ((int)1 << 29)) != 0;
	}
	cout << "810196512 - 810196469" << endl;
	cout << "CPU vendor = " << vendor << endl;
    cout << "CPU Brand = " << model << endl;
    cout << "Number of cores = " << cores << endl;
    cout << "Number of logical cores = " << logicalCores << endl;
	printf("%s\n", MMX   ? "MMX   Supported" : "MMX   NOT Supported");
	printf("%s\n", SSE   ? "SSE   Supported" : "SSE   NOT Supported");
	printf("%s\n", SSE2  ? "SSE2  Supported" : "SSE2  NOT Supported");
	printf("%s\n", SSE3  ? "SSE3  Supported" : "SSE3  NOT Supported");
	printf("%s\n", SSE41 ? "SSE41 Supported" : "SSE41 NOT Supported");
	printf("%s\n", SSE42 ? "SSE42 Supported" : "SSE42 NOT Supported");
	printf("%s\n", AES   ? "AES   Supported" : "AES   NOT Supported");
	printf("%s\n", SHA   ? "SHA   Supported" : "SHA   NOT Supported");
	printf("%s\n", AVX   ? "AVX   Supported" : "AVX   NOT Supported");
	printf("%s\n", AVX2  ? "AVX2  Supported" : "AVX2  NOT Supported");

	return 0;
}
