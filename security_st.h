#pragma once


void FileLogStk(const char* format, ...);

/// <summary>
/// Count hash of data
/// </summary>
/// <param name="inf">Pointer to data</param>
/// <param name="size">Size of one data element</param>
/// <returns>Unsigned int value of hash</returns>
int HashFuncStk(void* inf, int size);


/// <summary>
/// Nullify hash of data
/// </summary>
/// <param name="stack_ptr">Pointer on Stack data</param>
void HashClearStk(Stack* stack_ptr);


/// <summary>
/// Calculate hasg for all data of Stack
/// </summary>
/// <param name="stack_ptr">Pointer on Stack data</param>
void HashCalcStk(Stack* stack_ptr);


/// <summary>
/// Check correct hash value of stack_ptr and array
/// </summary>
/// <param name="stack_ptr">Pointer on Stack data</param>
/// <returns>1 if hash value is correct, else 0</returns>
bool CheckHashStk(Stack* stack_ptr);


/// <summary>
/// Check canaries' values
/// </summary>
/// <param name="stack_ptr">Transmitted stack_ptr</param>
/// <returns>1 if nothing has been changed, else 0</returns>
bool CheckCanariesStk(Stack* stack_ptr);


/// <summary>
/// Check stack_ptr sizes corectness
/// </summary>
/// <param name="stack_ptr">Transmitted stack_ptr</param>
/// <returns>1 if all sizes are right, else 0</returns>
bool CheckSizesStk(Stack* stack_ptr);


/// <summary>
/// Print information about stack_ptr: size, capacity, element and errors, if they exist
/// </summary>
/// <param name="stack_ptr">Trnsmitted stack_ptr</param>
/// <param name="errtxt">Description of error</param>
/// <param name="line">Error occurence line</param>
/// <param name="func">Error occurence function</param>
/// <param name="file">Error occurence file</param>
void DumpStk(const Stack* stack_ptr, int line = 0, const char* func = nullptr, const char* file = nullptr);


/// <summary>
/// Detect valid or not pointer to the stack
/// </summary>
/// <param name="stack_ptr">Pointer to the stack</param>
int StackExists(void* stack_ptr);


/// <summary>
/// Find errors on transmitted stack and write error code to the errno
/// </summary>
/// <param name="stack_ptr">Transmitted stack_ptr</param>
/// <param name="line">Error occurence line</param>
/// <param name="func">Error occurence function</param>
/// <param name="file">Error occurence file</param>
int AssertFunctionStk(Stack* stack_ptr, int line, const char* func, const char* file);
