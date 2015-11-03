#include "maraton.h"


#define PP_DEF(__type__,__name__) void __name__( __type__ value ) { __name__##_ = value; }; \
              __type__ __name__() { return __name__##_; }

#define EXECUTOR_TIMEOUT 5000000