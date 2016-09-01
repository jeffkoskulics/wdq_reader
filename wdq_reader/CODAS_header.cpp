#include "CODAS_header.h"



CODAS_header::CODAS_header(std::istream& input)
{
	input >> Element1;
	input >> Element2;
	input >> Element3;
}


CODAS_header::~CODAS_header()
{
}
