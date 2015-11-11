
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

#define PP_DEF(__type__,__name__) void __name__( __type__ value ) { __name__##_ = value; }; \
              __type__ __name__() { return __name__##_; }

#define EXECUTOR_TIMEOUT 5000
 
#endif //!MARATON_SERVER_H_ 

