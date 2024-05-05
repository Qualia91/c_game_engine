#include "darray.h"

#include "core/kmemory.h"
#include "core/logger.h"

void* _darray_create(u64 length, u64 stride) {
    u64 header_size = DARRAY_FIELD_LENGTH * sizeof(u64);
    u64 array_size = length * stride;
    u64* new_array = kallocate(array_size + header_size, MEMORY_TAG_DARRAY);
    new_array[DARRAY_CAPACITY] = length;
    new_array[DARRAY_LENGTH] = 0;
    new_array[DARRAY_STRIDE] = stride;
    return (void*)(new_array + DARRAY_FIELD_LENGTH);
}

void _darray_destroy(void* array) {
    u64* header = (u64*)array - DARRAY_FIELD_LENGTH;
    u64 header_size = DARRAY_FIELD_LENGTH * sizeof(u64);
    u64 array_size = header[DARRAY_CAPACITY] * header[DARRAY_STRIDE];
    kfree(header, header_size + array_size, MEMORY_TAG_DARRAY);
}

u64 _darray_field_get(void* array, u64 field) {
    u64* header = (u64*)array - DARRAY_FIELD_LENGTH;
    return header[field];
}

void _darray_field_set(void* array, u64 field, u64 value) {
    u64* header = (u64*)array - DARRAY_FIELD_LENGTH;
    header[field] = value;
}

void* _darray_resize(void* array) {
    u64 length = darray_length(array);
    u64 stride = darray_stride(array);
    u64* new_array = _darray_create(
        (DARRAY_RESIZE_FACTOR * length),
        stride
    );
    kcopy_memory(new_array, array, length * stride);
    _darray_field_set(array, DARRAY_LENGTH, length);
    _darray_destroy(array);
    return new_array;
}

void* _darray_push(void* array, const void* value_ptr) {
    u64 length = darray_length(array);
    u64 capacity = darray_capacity(array);
    u64 stride = darray_stride(array);
    if (length >= capacity - 1) {
        array = _darray_resize(array);
    }
    u64 addr = (u64)array;
    addr += (length * stride);
    kcopy_memory((void*)addr, value_ptr, stride);
    _darray_field_set(array, DARRAY_LENGTH, length + 1);
    return array;
}

void _darray_pop(void* array, void* dest) {
    u64 length = darray_length(array);
    u64 stride = darray_stride(array);
    u64 addr = (u64)array;
    addr += ((length - 1) * stride);
    kcopy_memory(dest, (void*)addr, stride);
    _darray_field_set(array, DARRAY_LENGTH, length - 1);
}

void* _darray_pop_at(void* array, u64 index, void* dest) {
    u64 length = darray_length(array);

    if (index >= length) {
        KERROR("Index %d is larger than length of array (%d)", index, length);
        return array;
    }

    u64 stride = darray_stride(array);
    u64 index_addr = (u64)array;
    index_addr += (index * stride);

    kcopy_memory(dest, (void*)index_addr, stride);

    if (index != length - 1) {
        
        u64 start_addr = index_addr + (index * stride);
        u64 end_addr = index_addr + ((length - 1) * stride);

        kcopy_memory(
            (void*)start_addr,
            (void*)end_addr,
            stride * (length - index)
        );
    }

    _darray_field_set(array, DARRAY_LENGTH, length - 1);
    return array;
}

void* _darray_insert_at(void* array, u64 index, const void* value_ptr) {
    u64 length = darray_length(array);
    u64 stride = darray_stride(array);

    if (index > length) {
        KERROR("Index %d is larger than length of array (%d)", index, length);
        return array;
    }

    if (length >= darray_capacity(array)) {
        array = _darray_resize(array);
    }

    u64 index_addr = (u64)array;
    index_addr += (index * stride);

    if (index != length - 1) {
        
        u64 data_stride = (length - index) * stride;
        u64 new_start_addr = index_addr + (index * stride);

        kcopy_memory(
            (void*)new_start_addr,
            (void*)index_addr,
            data_stride
        );
    }

    kcopy_memory((void*)index_addr, value_ptr, stride);

    _darray_field_set(array, DARRAY_LENGTH, length + 1);
    return array;
}