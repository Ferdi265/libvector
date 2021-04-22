#include "vector.template.args.h"

#define PPCAT2_INTERNAL(A, B) A ## B
#define PPCAT2(A, B) PPCAT2_INTERNAL(A, B)
#define PPCAT3_INTERNAL(A, B, C) A ## B ## C
#define PPCAT3(A, B, C) PPCAT3_INTERNAL(A, B, C)

#define vector_type PPCAT2(VALUE_TYPE_NAME, _vector)
#define value_type PPCAT2(vector_type, _value_type)
#define vector_method(name) PPCAT3(vector_type, _, name)

#ifndef VALUE_TYPE_TYPEDEF
typedef VALUE_TYPE value_type;
#else
typedef VALUE_TYPE_TYPEDEF(value_type);
#endif

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    value_type * data;
    size_t size;
    size_t capacity;
} vector_type;

// functions that never fail

void vector_method(new_empty)(vector_type * this);
void vector_method(delete)(vector_type * this);
void vector_method(clear)(vector_type * this);
void vector_method(shrink_to_fit)(vector_type * this);

// failure-safe functions

bool vector_method(try_new_copy)(vector_type * this, const vector_type * copy_from);
bool vector_method(try_new_with_capacity)(vector_type * this, size_t capacity);
bool vector_method(try_new_with_size)(vector_type * this, size_t size);
bool vector_method(try_new_with_size_and_default)(vector_type * this, size_t capacity, value_type value);

bool vector_method(try_reserve)(vector_type * this, size_t new_capacity);
bool vector_method(try_resize)(vector_type * this, size_t new_size);
bool vector_method(try_resize_with_default)(vector_type * this, size_t new_size, value_type value);

bool vector_method(try_push_back)(vector_type * this, value_type value);
bool vector_method(try_pop_back)(vector_type * this, value_type * value_out);

// functions that abort on failure

void vector_method(new_copy)(vector_type * this, const vector_type * copy_from);
void vector_method(new_with_capacity)(vector_type * this, size_t capacity);
void vector_method(new_with_size)(vector_type * this, size_t size);
void vector_method(new_with_size_and_default)(vector_type * this, size_t capacity, value_type value);

void vector_method(reserve)(vector_type * this, size_t new_capacity);
void vector_method(resize)(vector_type * this, size_t new_size);
void vector_method(resize_with_default)(vector_type * this, size_t new_size, value_type value);

void vector_method(push_back)(vector_type * this, value_type value);
value_type vector_method(pop_back)(vector_type * this);

#ifndef VECTOR_IMPL
#undef vector_type
#undef value_type
#undef VALUE_TYPE
#undef VALUE_TYPE_NAME
#undef PPCAT2_INTERNAL
#undef PPCAT2
#undef PPCAT3_INTERNAL
#undef PPCAT3
#endif
