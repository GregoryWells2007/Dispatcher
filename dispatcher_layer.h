#pragma once
typedef unsigned long dispatcher_size;

typedef struct dispatcher_layer {
    void* function_array;
    void* userData;
    struct dispatcher_layer* next_layer;
} dispatcher_layer;
