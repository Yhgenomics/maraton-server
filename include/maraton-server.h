
/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       :
* Description:
* * * * * * * * * * * * * * * */
#ifndef MARATON_SERVER_H_
#define MARATON_SERVER_H_ 

#include "maraton.h"
#include <stdio.h>
#include <locale>
#include <codecvt>

#define PP_DEF(__type__,__name__) void __name__( __type__ value ) { __name__##_ = value; }; \
              __type__ __name__() { return __name__##_; }

#define EXECUTOR_TIMEOUT 5000000

inline std::wstring utf8_2_ws( const std::string& src )
{
    std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
    return conv.from_bytes( src );
}

#endif //!MARATON_SERVER_H_ 

