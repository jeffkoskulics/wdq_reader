#pragma once
#include "EndianHelper.h"
#include <vector>
#include <array>

class ChannelInfo;

class CODAS_header
{
public:
	CODAS_header(std::istream& input);
	~CODAS_header();
private:
	Serial::Word Element1;
	Serial::Word Element2;
	Serial::Byte Element3;
	Serial::Byte Element4;
	Serial::Word Element5;
	Serial::DoubleWord Element6;
	Serial::DoubleWord Element7;
	Serial::Word Element8;
	Serial::Word Element9;
	Serial::Word Element10;
	Serial::Word Element11;
	Serial::DoubleWord Element12;
	Serial::DoubleWord Element13;
	Serial::DoubleWord Element14;
	Serial::DoubleWord Element15;
	Serial::DoubleWord Element16;
	Serial::DoubleWord Element17;
	Serial::DoubleWord Element18;
	Serial::DoubleWord Element19;
	Serial::Word Element20;
	Serial::Word Element21;
	Serial::Byte Element22;
	Serial::Byte Element23;
	Serial::Byte Element24;
	Serial::Byte Element25;
	std::array<Serial::Byte, 32> Element26;
	Serial::Word Element27;
	Serial::Word Element28;
	Serial::Byte Element29;
	Serial::Byte Element30;
	Serial::Word Element31;
	Serial::Byte Element32;
	Serial::Byte Element33;
	std::vector<ChannelInfo> Element34;
	Serial::Word Element35;
};

class ChannelInfo {
private:
	Serial::DoubleWord Item1;
	Serial::DoubleWord Item2;
	Serial::QuadWord Item3;
	Serial::QuadWord Item4;
	std::array<Serial::Byte, 6> Item5;
	Serial::Byte Item6;
	Serial::Byte Item7;
	Serial::Byte Item8;
	Serial::Byte Item9;
	Serial::Word Item10;

	friend class CODAS_header;
};
