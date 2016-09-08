#pragma once
#include <iosfwd>

class WaveformChannelInfo
{
public:
	WaveformChannelInfo(std::istream& input);
	~WaveformChannelInfo();
	float getScalingSlope() { return myScalingSlope; }
	float getScalingIntercept() { return myScalingIntercept; }
	double getCalibrationScalingFactor() { return myCalibrationScalingFactor; }
	double getCalibrationInterciptFactor() { return myCalibrationInterceptFactor; }
	const char* getEngineeringUnits() { return myEngineeringUnits; }

private:
	float myScalingSlope;
	float myScalingIntercept;
	double myCalibrationScalingFactor;
	double myCalibrationInterceptFactor;
	char myEngineeringUnits[7];
};

