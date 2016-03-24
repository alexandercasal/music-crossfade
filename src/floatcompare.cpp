#include "floatcompare.h"

/*-------------------------------------------------------
* FUNCTION    : floatCompare
* DESCRIPTION : Compares aproximate equality of two floats
* http://realtimecollisiondetection.net/blog/?p=89
*--------------------------------------------------------*/
bool floatCompare(const float first, const float second)
{
	return (std::fabs(first - second) <= (FLT_EPSILON * (std::fmax(first, second))));
}