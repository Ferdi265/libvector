#include "vector.template.args.h"

#define VECTOR_IMPL
#include "vector.template.h"

#include <stdlib.h>
#include <stdio.h>

// functions that never fail

void vector_method(new_empty)(vector_type * this) {
    this->data = NULL;
    this->size = 0;
    this->capacity = 0;
}

void vector_method(delete)(vector_type * this) {
    free(this->data);
    vector_method(new_empty)(this);
}

void vector_method(clear)(vector_type * this) {
    // this will never fail
    vector_method(try_resize)(this, 0);
}

void vector_method(shrink_to_fit)(vector_type * this) {
    // check if the vector is empty
    if (this->size == 0) {
        // delete the whole vector instead
        vector_method(delete)(this);
        return;
    }

    // try to reallocate to be just large enough for size
    value_type * new_data = realloc(this->data, this->size * sizeof (value_type));
    if (new_data == NULL) {
        // if we failed to shrink then just don't do anything
        return;
    }

    // update members
    this->data = new_data;
    this->capacity = this->size;
}

// failure-safe functions

bool vector_method(try_new_copy)(vector_type * this, const vector_type * copy_from) {
    vector_method(new_empty)(this);

    // reserve space
    if (!vector_method(try_reserve)(this, copy_from->size)) {
        return false;
    }

    // copy over data
    for (size_t i = 0; i < copy_from->size; i++) {
        this->data[i] = copy_from->data[i];
    }

    return true;
}

bool vector_method(try_new_with_capacity)(vector_type * this, size_t capacity) {
    vector_method(new_empty)(this);
    return vector_method(try_reserve)(this, capacity);
}

bool vector_method(try_new_with_size)(vector_type * this, size_t size) {
    vector_method(new_empty)(this);
    return vector_method(try_resize)(this, size);
}

bool vector_method(try_new_with_size_and_default)(vector_type * this, size_t size, value_type value) {
    vector_method(new_empty)(this);
    return vector_method(try_resize_with_default)(this, size, value);
}

bool vector_method(try_reserve)(vector_type * this, size_t new_capacity) {
    // check if capacity already big enough
    if (this->capacity >= new_capacity) {
        return true;
    }

    // try to reallocate
    value_type * new_data = realloc(this->data, new_capacity * sizeof (value_type));
    if (new_data == NULL) {
        return false;
    }

    // update members
    this->data = new_data;
    this->capacity = new_capacity;
    return true;
}

bool vector_method(try_resize)(vector_type * this, size_t new_size) {
    return vector_method(try_resize_with_default)(this, new_size, 0);
}

bool vector_method(try_resize_with_default)(vector_type * this, size_t new_size, value_type value) {
    // check if we are shrinking
    if (new_size <= this->size) {
        this->size = new_size;
        return true;
    }

    // reserve space
    if (!vector_method(try_reserve)(this, new_size)) {
        return false;
    }

    // initialize new values with default
    for (size_t i = this->size; i < new_size; i++) {
        this->data[i] = value;
    }

    // update members
    this->size = new_size;
    return true;
}

bool vector_method(try_push_back)(vector_type *this, value_type value) {
    return vector_method(try_resize_with_default)(this, this->size + 1, value);
}

bool vector_method(try_pop_back)(vector_type * this, value_type * value_out) {
    // check if vector not empty
    if (this->size == 0) {
        return false;
    }

    // get the last element
    *value_out = this->data[this->size - 1];

    // shrink vector, this will never fail
    vector_method(try_resize)(this, this->size - 1);

    return true;
}

// functions that abort on failure

static void vector_method(assert)(bool condition, const char * function) {
    if (!condition) {
        fprintf(stderr, "%s: allocation failure\n", function);
        abort();
    }
}

void vector_method(new_copy)(vector_type * this, const vector_type * copy_from) {
    vector_method(assert)(vector_method(try_new_copy)(this, copy_from), __FUNCTION__);
}

void vector_method(new_with_capacity)(vector_type * this, size_t capacity) {
    vector_method(assert)(vector_method(try_new_with_capacity)(this, capacity), __FUNCTION__);
}

void vector_method(new_with_size)(vector_type * this, size_t size) {
    vector_method(assert)(vector_method(try_new_with_size)(this, size), __FUNCTION__);
}

void vector_method(new_with_size_and_default)(vector_type * this, size_t size, value_type value) {
    vector_method(assert)(vector_method(try_new_with_size_and_default)(this, size, value), __FUNCTION__);
}

void vector_method(reserve)(vector_type * this, size_t new_capacity) {
    vector_method(assert)(vector_method(try_reserve)(this, new_capacity), __FUNCTION__);
}

void vector_method(resize)(vector_type * this, size_t new_size) {
    vector_method(assert)(vector_method(try_resize)(this, new_size), __FUNCTION__);
}

void vector_method(resize_with_default)(vector_type * this, size_t new_size, value_type value) {
    vector_method(assert)(vector_method(try_resize_with_default)(this, new_size, value), __FUNCTION__);
}

void vector_method(push_back)(vector_type * this, value_type value) {
    vector_method(assert)(vector_method(try_push_back)(this, value), __FUNCTION__);
}

value_type vector_method(pop_back)(vector_type * this) {
    value_type value;
    if (!vector_method(try_pop_back)(this, &value)) {
        fprintf(stderr, "%s: empty vector\n", __FUNCTION__);
        abort();
    }

    return value;
}
