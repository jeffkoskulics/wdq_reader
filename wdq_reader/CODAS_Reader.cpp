#include "CODAS_Reader.h"



CODAS_Reader::CODAS_Reader(std::istream& input) :
	myHeader(input), myStream(input)
{
}


CODAS_Reader::~CODAS_Reader()
{
}

int CODAS_Reader::GetNumSamples() const  {
	return myHeader.get_num_samples();
}

int16_t CODAS_Reader::GetSample(int channel, int index)  
{
	int channel_offset = 2 * ( channel - 1 );
	int sample_offset = myHeader.get_num_channels() * 2 * index;
	int data_start = myHeader.get_data_start();
	int read_point = data_start + sample_offset + channel_offset;
	myStream.seekg(read_point);
	Serial::Primitive<int16_t> sample;
	myStream >> sample;
	sample = sample >> 2;
	return sample;
}

float CODAS_Reader::GetOutput(int channel, int index)
{
	int sample = this->GetSample(channel, index);
	double offset = this->myHeader.getWaveformChannelInfo(channel).getCalibrationInterciptFactor();
	double slope = this->myHeader.getWaveformChannelInfo(channel).getCalibrationScalingFactor();
	return (sample * slope) + offset;
}

int CODAS_Reader::GetNumChannels() const 
{
	return myHeader.get_num_channels();
}