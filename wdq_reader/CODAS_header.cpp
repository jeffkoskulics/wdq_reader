#include "CODAS_header.h"
#include <cstdint>
#include <string>
#include <exception>


CODAS_header::CODAS_header(std::istream& input)
{
	input.seekg(setStartingByteForElement(1));
	Serial::Primitive<uint16_t> Element1;
	input >> Element1;
	myNumChannels = Element1 & 0b11111;
	int sample_rate_divisor = (Element1 & 0b0111111111100000) >> 5;
	
	Serial::Primitive<uint32_t> Element6;
	input.seekg(setStartingByteForElement(6));
	input >> Element6;

	Serial::Primitive<double> Element13;
	input.seekg(setStartingByteForElement(13));
	input >> Element13;
	
	mySampleRate = 1 / Element13 ;
	myNumSamples = 1 + (((Element6 / (2 * myNumChannels)) - 1) / sample_rate_divisor);

	myWaveformChannelInfos.reserve(myNumChannels);
	for (int i = 0; i < myNumChannels; ++i)
	{
		myWaveformChannelInfos.push_back(readWaveformChannelInfo(input, i+1));
	}

	Serial::Primitive<uint16_t> Element5;
	input.seekg(setStartingByteForElement(5));
	input >> Element5;

	LastByteOfElement[34] = Element5 - 3;
	LastByteOfElement[35] = Element5 - 2;

	Serial::Primitive<uint16_t> Element35;
	input.seekg(setStartingByteForElement(35));
	input >> Element35;


	if (Element35 != 0x8001)
	{
		std::string error{ "Bad file - invalid element 35. Expected 0x8001 but read " };
		error += std::to_string(Element35);
		error += ".\n";
		throw std::runtime_error(error.c_str());
	}

	myDataStart = input.tellg();

	//Check that the file is at least as large as expected
	input.seekg(0, input.end);
	int fileLength = input.tellg();
	int expectedMinFileSize = myNumSamples * myNumChannels * 2 + myDataStart;
	if (fileLength < expectedMinFileSize) {
		std::string error{ "Error - the file is smaller than expected.\nThe file size is: " };
		error += std::to_string(fileLength);
		error += "\nThe expected minimum file size is: ";
		error += std::to_string(expectedMinFileSize);
		error += "\n";
		throw std::runtime_error(error);
	}
	
}


CODAS_header::~CODAS_header()
{
}


WaveformChannelInfo CODAS_header::readWaveformChannelInfo(std::istream& input, int channel)
{
	int offset = channel - 1; 
	offset *= 36;
	offset += 110;
	input.seekg(offset);
	return WaveformChannelInfo(input);
}