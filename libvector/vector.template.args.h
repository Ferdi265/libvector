#ifdef VALUE_TYPE_TYPEDEF
#define VALUE_TYPE _unused
#ifndef VALUE_TYPE_NAME
#error "VALUE_TYPE_NAME not defined"
#endif
#endif

#ifndef VALUE_TYPE
#error "VALUE_TYPE not defined"
#endif

#ifndef VALUE_TYPE_NAME
#define VALUE_TYPE_NAME VALUE_TYPE
#endif
