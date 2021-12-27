#pragma once


/// <summary>
/// Create and initializate new stack
/// </summary>
/// <param name="stack_name">Transmitted name of stack</param>
/// <returns>Pointer to the initialized stack</returns>
Stack* CreateStack(const char stack_name[]);

/// <summary>
/// Push transmitted element on top of transmitted stack
/// </summary>
/// <param name="stack">Transmitted stack</param>
/// <param name="value">The value to put on the stack</param>
/// <returns>Return 0, if all actions were succesfull, else return error code</returns>
int Push(Stack* stack, const float value);

/// <summary>
/// Reduce the stack size by decrementation of element's size
/// </summary>
/// <param name="stack">Transmitted stack</param>
/// <param name="dst">Transmitted pointer to the variable</param>
/// <returns>Return 0, if all actions were succesfull, else return error code</returns>
int Pop(Stack* stack, float* dst);

/// <summary>
/// Return size of stack
/// </summary>
/// <param name="stack">Transmitted stack</param>
/// <param name="dst">Transmitted pointer to the variable</param>
/// <returns>Return 0, if all actions were succesfull, else return error code</returns>
int SizeStk(Stack* stack, int* dst);

/// <summary>
/// Return capacity of stack
/// </summary>
/// <param name="stack">Transmitted stack</param>
/// <param name="dst">Transmitted pointer to the variable</param>
/// <returns>Return 0, if all actions were succesfull, else return error code</returns>
int CapacityStk(Stack* stack, int* dst);

/// <summary>
/// Increase stack capacity of stack or do nothing, if stack is empty
/// </summary>
/// <param name="stack">Transmitted stack</param>
/// <returns>Return 0, if all actions were succesfull, else return error code</returns>
int ResizeStk(Stack* stack);

/// <summary>
/// Initialization stack's name by transmitted name
/// </summary>
/// <param name="target_name">Char array get transmitted name of Stack</param>
/// <param name="get_name">Transmitted name</param>
void NameInititializationStk(char target_name[], const char get_name[]);

/// <summary>
/// Initial pointers to data array, canaries and sizes 
/// </summary>
/// <param name="stack_ptr">Transmitted stack</param>
void DataInitializationStk(Stack* stack_ptr);

/// <summary>
/// Increase value of stack size and add new value
/// </summary>
/// <param name="stack_ptr">Transmitted stack</param>
/// <param name="value">Added value</param>
void PushAction(Stack* stack_ptr, float value);

/// <summary>
/// Decrease value of stack size, remove last element and set 0 value
/// </summary>
/// <param name="stack_ptr">Transmitted stack</param>
/// <param name="dst">Pointers for remove value</param>
void PopAction(Stack* stack_ptr, float* dst);


/// <summary>
/// Replace all elements to 0 and resize Stack to 0
/// </summary>
/// <param name="stack">Transmitted Stack</param>
int CleanDataStk(Stack* stack);


/// <summary>
/// Delete stack by free memory
/// </summary>
/// <param name="stack">Transmitted stack</param>
void ClearStk(Stack* stack);