#include "CODAS_header.h"
#include <cstdint>



CODAS_header::CODAS_header(std::istream& input)
{
	input.seekg(setStartingByteForElement(1));
	Serial::Primitive<uint16_t> Element1;
	input >> Element1;
	num_channels = Element1 & 0b11111;
	int sample_rate_divisor = (Element1 & 0b0111111111100000) >> 5;
	
	Serial::Primitive<uint32_t> Element6;
	input.seekg(setStartingByteForElement(6));
	input >> Element6;

	Serial::Primitive<double> Element13;
	input.seekg(setStartingByteForElement(13));
	input >> Element13;
	
	sample_rate = 1 / Element13 ;
	num_samples = 1 + (((Element6 / (2 * num_channels)) - 1) / sample_rate_divisor);

	myWaveformChannelInfos.reserve(num_channels);
	for (int i = 0; i < num_channels; ++i)
	{
		myWaveformChannelInfos.push_back(readWaveformChannelInfo(input, i+1));
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