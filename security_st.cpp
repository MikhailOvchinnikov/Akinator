#include "stack.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <errno.h>
#include <stdarg.h>

//Hash coefficient
#define HASH 0.618033

//Canary's value
#define CANARY 0xFF


/// <summary>
/// Error codes
/// </summary>
enum ErrorCodes
{
    //stack_ptr pointer has a NULL pointer or not valid fields
    BADSTACK = 1,

    //canary data was corrupted
    CANARYDIED,

    //size of data has negative length or 0 length at the pop command
    BADSIZE,

    //different hash of something data
    BADHASH,

    //error memory allocation
    MEMORYERROR
};


void FileLogStk(const char* format, ...)
{
    static FILE* log_file = fopen("stack_log.txt", "w");
    va_list args;
    va_start(args, format);
    vfprintf(log_file, format, args);
    va_end(args);
}


int HashFuncStk(void* inf, int size)
{
    char* point = (char*)inf;
    int result = 0;
    for (int i = 0; i < size; i++)
    {
        result += (int)((size) * fmod(*(point++), HASH));
    }
    return result;
}


bool CheckHashStk(Stack* stack_ptr)
{
    Data_st* data_struct = stack_ptr->data;

    int prev_h_stack = stack_ptr->hash;
    int prev_h_dat = data_struct->hash;
    int prev_h_arr = data_struct->hash_data;

    stack_ptr->hash = 0;
    data_struct->hash = 0;
    data_struct->hash_data = 0;
    bool f_ret = HashFuncStk(data_struct, sizeof(*(data_struct))) == prev_h_dat;
    bool s_ret = HashFuncStk(stack_ptr, sizeof(*stack_ptr)) == prev_h_stack;
    bool t_ret = HashFuncStk(data_struct->data, data_struct->capacity * sizeof(data_struct->data[0])) == prev_h_arr;

    stack_ptr->hash = prev_h_stack;
    data_struct->hash = prev_h_dat;
    data_struct->hash_data = prev_h_arr;

    return f_ret && s_ret && t_ret;
}

void HashClearStk(Stack* stack_ptr)
{
    Data_st* data_struct = stack_ptr->data;

    data_struct->hash = 0;
    data_struct->hash_data = 0;
    stack_ptr->hash = 0;
}


void HashCalcStk(Stack* stack_ptr)
{
    Data_st* data_struct = stack_ptr->data;

    stack_ptr->hash = HashFuncStk(stack_ptr, sizeof(*stack_ptr));
    data_struct->hash = HashFuncStk(data_struct, sizeof(*data_struct));
    data_struct->hash_data = HashFuncStk(data_struct->data, data_struct->capacity * sizeof(data_struct->data[0]));
}


bool CheckCanariesStk(Stack* stack_ptr)
{
    Data_st* data_struct = stack_ptr->data;

    bool f_ret = stack_ptr->canary_left == CANARY && stack_ptr->canary_right == CANARY;
    bool s_ret = data_struct->canary_left == CANARY && data_struct->canary_right == CANARY;
    bool t_ret = *data_struct->data_canary_left == CANARY && *data_struct->data_canary_right == CANARY;
    return f_ret && s_ret && t_ret;
}

bool CheckSizesStk(Stack* stack_ptr)
{
    Data_st* data_struct = stack_ptr->data;

    bool f_ret = data_struct->size <= data_struct->capacity;
    bool s_ret = data_struct->size >= 0;
    bool t_ret = data_struct->capacity >= 0;

    return f_ret && s_ret && t_ret;
}


void DumpStk(const Stack* stack_ptr, int line, const char* func, const char* file)
{
    if (stack_ptr == NULL)
    {
        return;
    } 

    Data_st* data_struct = stack_ptr->data;

    int cap = data_struct->capacity;
    int size = data_struct->size;

    FileLogStk("Stack<>[%p] \"%s\" in the \"%d\" line of the function \"%s\" in programm at \"%s\"\n", stack_ptr, stack_ptr->name, line, func, file);
    FileLogStk("Size = %d\nCapacity = %d\n", size, cap);
    FileLogStk("data[%p]\n\t{\n", &data_struct->data);

    for (int i = 0; i < cap; i++)
    {
        if (i < size)
        {
            FileLogStk("\t\t[%d] %f\n", i, data_struct->data[i]);
        }
        else
        {
            FileLogStk("\t\t[%d] (undefined value)\n", i);
        }
    }
    FileLogStk("\t}\n");
}


int StackExists(void* ptr)
{
    if (!ptr)
    {
        printf("code %d\n", ErrorCodes::BADSTACK);
        errno = ErrorCodes::BADSTACK;
        return -1;
    }
    return 0;
}


int AssertFunctionStk(Stack* stack_ptr, int line,const char* func,const char* file)
{
    StackExists(stack_ptr);
    if(!errno)
    {
        if (!CheckCanariesStk(stack_ptr)) {
            FileLogStk("\n\n\t\tCANARY DIED\n\n\n");
            DumpStk(stack_ptr, line, func, file);
            errno = ErrorCodes::CANARYDIED;
        }
        else if (!CheckSizesStk(stack_ptr)) {
            FileLogStk("\n\n\t\tBAD SIZE\n\n\n");
            DumpStk(stack_ptr, line, func, file);
            errno = ErrorCodes::BADSIZE;
        }
        else if (!CheckHashStk(stack_ptr))
        {
            FileLogStk("\n\n\t\tHASH ERROR\n\n\n");
            DumpStk(stack_ptr, line, func, file);
            errno = ErrorCodes::BADHASH;
        }
    }
    if (errno)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
