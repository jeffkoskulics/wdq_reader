#include "WaveformChannelInfo.h"
#include "Serial.h"


WaveformChannelInfo::WaveformChannelInfo(std::istream& input)
{
	Serial::Primitive<float> ScalingSlope, ScalingIntercept;
	input >> ScalingSlope >> ScalingIntercept;
	myScalingSlope = ScalingSlope;
	myScalingIntercept = ScalingIntercept;

	Serial::Primitive<double> CalScalingFactor, CalInterceptFactor;
	input >> CalScalingFactor >> CalInterceptFactor;
	myCalibrationScalingFactor = CalScalingFactor;
	myCalibrationInterceptFactor = CalInterceptFactor;

	input.read(myEngineeringUnits,6);
}


WaveformChannelInfo::~WaveformChannelInfo()
{
}

