#pragma once
#include "IFileReader.h"
#include "CODAS_header.h"
#include <iosfwd>

class CODAS_Reader 
{
public:
	CODAS_Reader(std::istream& input);
	virtual ~CODAS_Reader();
	int GetNumSamples() const;
	int16_t GetSample(int channel, int sample);
	float GetOutput(int channel, int sample);
	int GetNumChannels() const;

private:
	CODAS_header myHeader;
	std::istream& myStream;
};

