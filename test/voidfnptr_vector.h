#ifndef VOIDFNPTR_VECTOR_H_
#define VOIDFNPTR_VECTOR_H_

#define VALUE_TYPE_TYPEDEF(name) void (*name)()
#define VALUE_TYPE_NAME voidfnptr
#include <vector.template.h>

#endif
