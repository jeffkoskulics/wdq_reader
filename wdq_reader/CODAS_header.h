#pragma once
#include "Serial.h"
#include "WaveformChannelInfo.h"
#include <vector>
#include <array>
#include <map>
#include <iosfwd>




class CODAS_header
{
public:
	CODAS_header(std::istream& input);
	CODAS_header(CODAS_header&&) noexcept = default;
	~CODAS_header();
	int get_num_channels() const { return myNumChannels; }
	unsigned long int get_num_samples() const { return myNumSamples; }
	double get_sample_rate () const { return mySampleRate; }
	int get_data_start() const { return myDataStart; }
	WaveformChannelInfo getWaveformChannelInfo(int channel) const { return myWaveformChannelInfos.at(channel - 1); }

private:
	int myNumChannels;
	unsigned long int myNumSamples;
	double mySampleRate;
	int myDataStart;
	std::vector<WaveformChannelInfo> myWaveformChannelInfos;
	WaveformChannelInfo readWaveformChannelInfo(std::istream&, int channel);
	int setStartingByteForElement(int index) const { return LastByteOfElement[index - 1] + 1; }

	std::array<int, 36> LastByteOfElement{ -1, 1, 3, 4, 5, 7, 11,
		15, 17, 19, 21, 23, 27, 35, 39, 43, 47, 51, 55, 59, 61, 63, 64, 65,
		66, 67, 99, 101, 102, 104, 105, 106, 108, 109, -1, -1 };
};


