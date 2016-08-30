#include "wdq_reader.h"
#include <exception>
#include <cstring>

wdq_reader::wdq_reader(const char* file_name):
	myFilename(file_name)
{

}


wdq_reader::~wdq_reader()
{
}


void wdq_reader::initiallize()
{
	//Attempt to open file
	myFILE = fopen(myFilename, "r");

	//Determine file size
	fseek(myFILE, 0, SEEK_END);
	myFileSizeInBytes = ftell(myFILE);

	//Determine Endian-ness of the platform
	int i = 1;
	LittleEndian = *(char *)&i == 1;

	//Begin setting header elements
	setHeaderElement1();
}


void wdq_reader::setHeaderElement1()
{
	const char NumElementBytes = 2;
	char Bytes[NumElementBytes];
	if (fread(&Bytes, 1, NumElementBytes, myFILE) != NumElementBytes) 
		throw std::runtime_error("Couldn't read Header Element 1");
	myNumChannels = Bytes[0] & 0b00011111;

	union TwoBytes {
		char Bytes[2];
		unsigned short BiggerNumber;
	} TB;

	TB.Bytes[0] = Bytes[0];
	TB.Bytes[1] = Bytes[1];

	mySampleDenominator = TB.BiggerNumber;
	mySampleDenominator = mySampleDenominator & 0x7F80 >> 5;
}
