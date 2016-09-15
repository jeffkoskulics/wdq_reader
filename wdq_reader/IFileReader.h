#pragma once
#include <cstdint>
#include <iostream>
#include <map>

class IFileReader
{
public:
	IFileReader() {}
	static IFileReader& createReader(const char* path);
	virtual ~IFileReader() {}
	virtual IFileReader& initialize(std::istream& input) = 0;
	virtual int GetNumSamples() const = 0;
	virtual int16_t GetSample(int channel, int sample) const = 0;
	virtual int GetNumChannels() const = 0;

protected:
	static std::map<const char*, IFileReader&(*)(std::istream&)> myFileTypes;
};

