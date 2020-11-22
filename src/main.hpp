#pragma once
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <windows.h>
typedef unsigned char *(WINAPI *LPFNAquesTalk_Synthe)(const char *,int,int*);
typedef void(WINAPI *LPFNAquesTalk_FreeWave)(unsigned char*);
void usage();
int main(int argc,char* argv[]);