#include <cstdio>
#pragma once
#include "EndianHelper.h"

class wdq_reader
{
public:
	wdq_reader(const char* file_name);
	virtual ~wdq_reader();


private:
	const char* myFilename;
	FILE* myFILE;
	int myFileSizeInBytes;
	int mySampleDenominator;
	char myNumChannels;
	bool LittleEndian;
protected:
	void initiallize();
private:
	void setHeaderElement1();
};

 