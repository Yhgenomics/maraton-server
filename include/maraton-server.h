
#define PROPERTY_DEF(__type__,__name__,__valiable__) void __name__( __type__ value ) { __valiable__ = value; }; __type__ __name__() { return __valiable__; };

enum EXECUTORSTATUS
{
    BUSY = 1,
    IDLE,
    PREPARE,
    WORK,

    UNKNOWN = 0xFFFF
};