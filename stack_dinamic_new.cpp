#include "stack.h"

#include <stdlib.h>
#include <cassert>
#include <stdio.h>
#include <string.h>
#include <errno.h>


//Defaul capacity of stack_ptr
#define INITIAL_CAPACITY 10

//Coefficient of resize stack_ptr's capacity
#define RESIZE_FACTOR 2

//Canary's value
#define CANARY 0xFF

//Def function for check stack_ptr adequate
#define StackOK(stack_ptr, line, func, file) AssertFunctionStk(stack_ptr, line, func, file)

//Def function for check nullptr of stack_ptr
#define NotNULL(stack_ptr) StackExists(stack_ptr)


Stack* CreateStack(const char stack_name[])
{
    Stack* new_stack = (Stack*)calloc(1, sizeof(Stack));

    if (NotNULL(new_stack))
    {
        FileLogStk("Error command %s of the stack \"%s\"\n", __FUNCTION__, new_stack->name);
        ClearStk(new_stack);
        return nullptr;
    }

    new_stack->data = (Data_st*)calloc(1, sizeof(Data_st));

    if (NotNULL(new_stack->data))
    {
        FileLogStk("Error command %s of the stack \"%s\"\n", __FUNCTION__, new_stack->name);
        ClearStk(new_stack);
        return nullptr;
    }

    Data_st* data_ptr = new_stack->data;
    data_ptr->memory = (float*)calloc(INITIAL_CAPACITY + 2, sizeof(float));

    if (NotNULL(data_ptr->memory))
    {
        FileLogStk("Error command %s of the stack \"%s\"\n", __FUNCTION__, new_stack->name);
        ClearStk(new_stack);
        return nullptr;
    }

    data_ptr->capacity = INITIAL_CAPACITY;
    data_ptr->size = 0;

    new_stack->canary_right = CANARY;
    new_stack->canary_left = CANARY;
    data_ptr->canary_left = CANARY;
    data_ptr->canary_right = CANARY;

    DataInitializationStk(new_stack);
    NameInititializationStk(new_stack->name, stack_name);
    HashClearStk(new_stack);
    HashCalcStk(new_stack);

    if (StackOK(new_stack, __LINE__, __FUNCTION__, __FILE__))
    {
        FileLogStk("Error command %s of the stack \"%s\"\n", __FUNCTION__, new_stack->name);
        ClearStk(new_stack);
        return nullptr;
    }
    else
    {
        FileLogStk("Stack \"%s\"was created successfully\n", new_stack->name);
        return new_stack;
    }
}


int Push(Stack* stack_ptr, const float value)
{
    if (StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__))
    {
        FileLogStk("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
        return -1;
    }

    int cap = stack_ptr->data->capacity;
    int size = stack_ptr->data->size;

    if (size >= cap)
    {
        if (ResizeStk(stack_ptr))
        {
            FileLogStk("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
            return -1;
        }
    }
    
    PushAction(stack_ptr, value);
    HashClearStk(stack_ptr);
    HashCalcStk(stack_ptr);

    if (StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__))
    {
        FileLogStk("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
        return -1;
    }
    else
    {
        FileLogStk("Command %s of the stack \"%s\" was successful, value %f\n", __FUNCTION__, stack_ptr->name, value);
        return 0;
    }
}


int Pop(Stack* stack_ptr, float* dst)
{
    if (StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__))
    {
        FileLogStk("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
        return -1;
    }


    PopAction(stack_ptr, dst);
    HashClearStk(stack_ptr);
    HashCalcStk(stack_ptr);

    if (StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__))
    {
        FileLogStk("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
        return -1;
    }
    else
    {
        FileLogStk("Command %s of the stack \"%s\" was successful, value %f\n", __FUNCTION__, stack_ptr->name, *dst);
        return 0;
    }
}


int SizeStk(Stack* stack_ptr, int* dst)
{
    if (StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__))
    {
        FileLogStk("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
        return -1;
    }
    Data_st* data_ptr = stack_ptr->data;

    *dst = data_ptr->size;

    if (StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__))
    {
        FileLogStk("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
        return -1;
    }
    else
    {
        FileLogStk("Command %s of the stack \"%s\" was successful, value %d\n", __FUNCTION__, stack_ptr->name, *dst);
        return 0;
    }
}


int CapacityStk(Stack* stack_ptr, int* dst)
{
    if (StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__))
    {
        FileLogStk("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
        return -1;
    }
    Data_st* data_ptr = stack_ptr->data;

    *dst = data_ptr->capacity;

    if (StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__))
    {
        FileLogStk("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
        return -1;
    }
    else
    {
        FileLogStk("Command %s of the stack \"%s\" was successful, value %d\n", __FUNCTION__, stack_ptr->name, *dst);
        return 0;
    }
}


int ResizeStk(Stack* stack_ptr)
{
    if (StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__))
    {
        FileLogStk("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
        return -1;
    }
    Data_st* data_ptr = stack_ptr->data;

    data_ptr->capacity *= RESIZE_FACTOR;
    int cap = data_ptr->capacity;
    data_ptr->memory = (float*)realloc(data_ptr->memory, (cap + 2) * sizeof(float));

    if(NotNULL(stack_ptr))
    {
        FileLogStk("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
        return -1;
    }

    DataInitializationStk(stack_ptr);
    HashClearStk(stack_ptr);
    HashCalcStk(stack_ptr);

    if (StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__))
    {
        FileLogStk("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
        return -1;
    }
    else
    {
        FileLogStk("Command %s of the stack \"%s\" was successful\n", __FUNCTION__, stack_ptr->name);
        return 0;
    }
}


void NameInititializationStk(char target_name[], const char get_name[])
{
    strncpy(target_name, get_name, ST_S);
}


void DataInitializationStk(Stack* stack_ptr)
{
    Data_st* data_ptr = stack_ptr->data;

    int cap = data_ptr->capacity;
    data_ptr->data_canary_left = data_ptr->memory;
    data_ptr->data_canary_right = &data_ptr->memory[cap + 1];
    data_ptr->memory[0] = CANARY;
    data_ptr->memory[cap + 1] = CANARY;
    data_ptr->data = &data_ptr->memory[1];
}


void PushAction(Stack* stack_ptr, float value)
{
    Data_st* data_ptr = stack_ptr->data;

    data_ptr->data[data_ptr->size] = value;
    ++data_ptr->size;
}


void PopAction(Stack* stack_ptr, float* dst)
{
    Data_st* data_ptr = stack_ptr->data;

    *dst = data_ptr->data[data_ptr->size - 1];
    data_ptr->data[data_ptr->size - 1] = 0;
    --data_ptr->size;
}


int CleanDataStk(Stack* stack_ptr)
{
    if (StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__))
    {
        FileLogStk("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
        return -1;
    }

    Data_st* data_ptr = stack_ptr->data;
    for (int i = 0; i < data_ptr->size; i++)
    {
        data_ptr->data[i] = 0;
    }
    data_ptr->size = 0;

    HashClearStk(stack_ptr);
    HashCalcStk(stack_ptr);

    if (StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__))
    {
        FileLogStk("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name); 
        return -1;
    }
    else
    {
        FileLogStk("Command %s of the stack \"%s\" was successful\n", __FUNCTION__, stack_ptr->name);
        return 0;
    }
}


void ClearStk(Stack* stack_ptr)
{
    FileLogStk("Stack \"%s\" is deleting...\n", stack_ptr->name);
    free(stack_ptr->data->memory);
    free(stack_ptr->data);
    free(stack_ptr);
    FileLogStk("Deleting was successful\n");
}