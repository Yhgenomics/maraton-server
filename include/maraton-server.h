#include "maraton.h"


#define PP_DEF(__type__,__name__) void __name__( __type__ value ) { __name__##_ = value; }; \
              __type__ __name__() { return __name__##_; }

enum ExecutorStatus
{
    UNKNOWN = 0,
	BOOT,
    BUSY,
    IDLE,
    PREPARE,
    WORK,
};