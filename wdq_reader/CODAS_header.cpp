#include "CODAS_header.h"
#include <cstdint>



CODAS_header::CODAS_header(std::istream& input)
{
	Serial::Primitive<uint16_t> Element1;
	input >> Element1;
	num_channels = Element1 & 0b11111;
	int sample_rate_divisor = (Element1 & 0b0111111111100000) >> 5;
	
	Serial::Primitive<uint32_t> Element6;
	input.seekg(8);
	input >> Element6;

	Serial::Primitive<double> Element13;
	input.seekg(28);
	input >> Element13;
	
	sample_rate = 1 / Element13 ;
	num_samples = 1 + (((Element6 / (2 * num_channels)) - 1) / sample_rate_divisor);
}


CODAS_header::~CODAS_header()
{
}


