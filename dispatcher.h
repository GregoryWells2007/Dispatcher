#pragma once
#include "dispatcher_layer.h"

typedef int dispatcher_bool;
#define dispatcher_false 0
#define dispatcher_true 1

typedef struct dispatcher {
    dispatcher_size function_array_size;
    dispatcher_layer* first_layer;
} dispatcher;

typedef dispatcher_bool (*dispatcher_init_func)(dispatcher_layer* layer);

void dispatcher_init(dispatcher* dispatcher);
void dispatcher_set_function_array_size(dispatcher* dispatcher, dispatcher_size size);
void dispatcher_create_layer(dispatcher* dispatcher, dispatcher_init_func init_func, void* userData);
void dispatcher_destroy(dispatcher* dispatcher);
