/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       :
* Description:
* * * * * * * * * * * * * * * */
#ifndef MARATON_MATH_H_
#define MARATON_MATH_H_ 

#include <math.h>

inline double maraton_round( double val )
{
    return ( val> 0.0 ) ? floor( val + 0.5 ) : ceil( val - 0.5 );
}

#endif //!MARATON_MATH_H_ 