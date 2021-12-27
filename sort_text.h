#pragma once
#include <stdio.h>


int Comp(void* o, void* t);


/// <summary>
/// Exchange value of two elements
/// </summary>
/// <param name="first">first element</param>
/// <param name="second">second element</param>
void SwapValues(void* first, void* second, int size);


/// <summary>
/// Miss symbol that is not letter
/// </summary>
/// <param name="sym">Transmitted symbol</param>
/// <returns>1 if sym is letter, else 0</returns>
inline int MissNotSymbols(char sym);


/// <summary>
/// Compare two strings based on transmit comparator
/// </summary>
/// <param name="first">First transmit string</param>
/// <param name="second">Second transmit string</param>
/// <param name="compare">Comparator</param>
/// <returns>1 if first string is larger than second, 
/// 2 if second string is larger than second, 0 if they are equal</returns>
int CompareStr(void* first, void* second);


/// <summary>
/// Compare two strings from the end based on transmit comparator
/// </summary>
/// <param name="first">First transmit string</param>
/// <param name="second">Second transmit string</param>
/// <param name="compare">Comparator</param>
/// <returns>1 if first string is larger than second, 
/// 2 if second string is larger than second, 0 if they are equal</returns>
int CompareStrReverse(void* first, void* second);


/// <summary>
/// Sort strings from the end of text based on transmit comparator
/// </summary>
/// <param name="array">Transmit text</param>
/// <param name="low">Beginning number of symbol</param>
/// <param name="high">End number of symbol</param>
/// <param name="compare">Comaparator</param>
void StringsSort(void* array, int low, int high, int size, int (*compare) (void*, void*));


/// <summary>
/// Count lines quantity from transmit file
/// </summary>
/// <param name="file">Transmit file</param>
/// <param name="text">Array for write file's text</param>
/// <param name="lines">Number of lines</param>
int GetParametersFile(FILE* file, char* text, int syms);


/// <summary>
/// Separation text on lines with remove tabs symbol of next line
/// </summary>
/// <param name="text">Transmit text</param>
/// <param name="p">Set of transmit lines for writing</param>
void SeparateTextToLines(char* text, char** p);


/// <summary>
/// Count number of symbols in transmitted file
/// </summary>
/// <param name="file">Transmitted file</param>
/// <return>Number of symbols</returns>
int CountSymbols(FILE* file);