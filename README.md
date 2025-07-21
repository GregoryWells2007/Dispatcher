
# Dispatcher
a tool to create validation layers for functions

# Use Case
This is intended to be used in my main project Gryphn to allow for functions to attach validation layers to them, every object that contains platform specific functions must have a dispatcher attached to it which is just a thin wrapper for the layered functions and allows them to be called

# Dumb assumptions I made
1. the dispatcher always assumes you call `dispatcher_set_function_array_size` before adding layers, if you don't then the function array pointer will be a zero sized array.
2. the dispatcher does not do any error checking for its functions, i plan to add in some defines to help with this but at the same time this is a minimal project that adds as little overhead and memory use as possible <br />

# Usage
To create a debugger an initialize its objects you call this
```C
dispatcher caller;
dispatcher_init(&caller);
dispatcher_set_function_array_size(&caller, {your array size});
```
for every layer you create you need an init function which takes in a `dispatcher_layer*` and loads all its functions, this also returns a `dispatcher_bool` for if it succeeded *note this is not checked*
```C
dispatcher_bool {layer}_layer_init(dispather_layer* layer) {
// set functions here
return dispatcher_true;
}
```

then you can call `dispatcher_create_layer` which takes in a user data parameter this is used in initialization *the user data pointer is stored in `layer->userData`*
```C
// no user data needed for this function
dispatcher_create_layer(&caller, {layer}_layer_init, NULL);
```
then call dispatcher_destroy which will free all the memory that has been allocated by the dispatcher
```C
dispatcher_destroy(&caller);
```
