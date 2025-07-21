#include "dispatcher.h"
#include "stdlib.h"

#include <stdio.h>

#define DISPATCHER_NULL (void*)0

void dispatcher_init(dispatcher* dispatcher) {
    dispatcher->function_array_size = 0;
    dispatcher->first_layer = DISPATCHER_NULL;
}

void dispatcher_set_function_array_size(dispatcher* dispatcher, dispatcher_size size) {
    dispatcher->function_array_size = size;
}

void dispatcher_create_layer(dispatcher* dispatcher, dispatcher_init_func init_func, void* userData) {
    if (dispatcher->first_layer == DISPATCHER_NULL) {
        dispatcher->first_layer = malloc(sizeof(dispatcher_layer));
        dispatcher->first_layer->userData = userData;
        dispatcher->first_layer->function_array = calloc(1, sizeof(dispatcher->function_array_size));
        dispatcher->first_layer->next_layer = DISPATCHER_NULL;
        init_func(dispatcher->first_layer);
        return;
    }
    dispatcher_layer* current_layer = dispatcher->first_layer;
    while (current_layer->next_layer != DISPATCHER_NULL) {
        current_layer = current_layer->next_layer;
    }

    current_layer->next_layer = malloc(sizeof(dispatcher_layer));
    current_layer->next_layer->userData = userData;
    current_layer->next_layer->function_array = calloc(1, sizeof(dispatcher->function_array_size));
    current_layer->next_layer->next_layer = DISPATCHER_NULL;
    init_func(current_layer->next_layer);
}

void dispatcher_destroy(dispatcher* dispatcher) {
    if (dispatcher->first_layer == NULL) { return; }

    dispatcher_layer* current_layer = dispatcher->first_layer, *lastLayer = DISPATCHER_NULL;
    while (current_layer->next_layer != DISPATCHER_NULL) {
        lastLayer = current_layer;
        current_layer = current_layer->next_layer;
    }

    current_layer->userData = DISPATCHER_NULL;
    free(current_layer->function_array);
    if (lastLayer != NULL) free(lastLayer->next_layer);
    lastLayer->next_layer = NULL;
    dispatcher_destroy(dispatcher);
}
