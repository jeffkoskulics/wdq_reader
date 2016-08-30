#pragma once
class wdq_reader
{
public:
	wdq_reader(const char* file_name);
	virtual ~wdq_reader();

private:
	const char* myFilename;
};

