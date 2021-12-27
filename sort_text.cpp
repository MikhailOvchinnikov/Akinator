#include "sort_text.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int Comp(void* o, void* t)
{
	return *(int*)o < *(int*)t;
}

void SwapValues(void* first, void* second, int size)
{
	char t;
	char* a = (char*)first;
	char* b = (char*)second;

	do
	{
		t = *a;
		*a++ = *b;
		*b++ = t;
	} while (--size);
}


inline int MissNotSymbols(char sym)
{
	return !('a' <= sym && sym <= 'z' || 'A' <= sym && sym <= 'Z');
}


int CountSymbols(FILE* file)
{
	fseek(file, 0, SEEK_END);
	int syms = ftell(file);
	rewind(file);
	return syms;
}


int CompareStr(void* first, void* second)
{
	char* n_first = (char*)first;
	char* n_second = (char*)second;
	int f_len = strlen(n_first);
	int s_len = strlen(n_second);
	for (int i = 0, k = 0; (i < f_len + 1) && (k < s_len + 1); i++, k++)
	{
		while (MissNotSymbols(n_first[i]) && i < f_len)
		{
			i++;
		}
		while (MissNotSymbols(n_second[k]) && k < s_len)
		{
			k++;
		}
		char current_s_f = (char)tolower(n_first[i]);
		char current_s_s = (char)tolower(n_second[k]);
		if (current_s_f - current_s_s > 0)
		{
			return 1;
		}
		else if (current_s_f - current_s_s < 0)
		{
			return -1;
		}
	}
	return 0;
}


int CompareStrReverse(void* first, void* second)
{
	char* n_first = (char*)first;
	char* n_second = (char*)second;
	int f_len = strlen(n_first);
	int s_len = strlen(n_second);
	for (int i = 0, k = 0; i < (f_len + 1) && k < (s_len + 1); i++, k++)
	{
		while (MissNotSymbols(n_first[f_len - i]) && i < f_len)
		{
			i++;
		}
		while (MissNotSymbols(n_second[s_len - k]) && k < s_len)
		{
			k++;
		}
		char current_s_f = (char)tolower(n_first[f_len - i]);
		char current_s_s = (char)tolower(n_second[s_len - k]);
		
		if (current_s_f - current_s_s > 0)
		{
			return 1;
		}
		else if (current_s_f - current_s_s < 0)
		{
			return -1;
		}
	}
	return 0;
}


void StringsSort(void* array, int low, int high, int size, int (*compare) (void*, void*))
{
	int i = low;
	int j = high;
	char* pivot = (char*)array + size*(low + (high - low) / 2);
	do
	{
		while (compare((char*)array + size*i, pivot) < 0)
		{
			i++;
		}
		while (compare((char*)array + size*j, pivot) > 0)
		{
			j--;
		}
		if (i <= j)
		{
			if (compare((char*)array + size*i, (char*)array + size*j) > 0)
			{
				SwapValues((char*)array + size*i, (char*)array + size*j, size);
			}
			if (j > 0)
			{
				j--;
			}
			i++;
		}
	} while (i <= j);
	if (i < high)
	{
		StringsSort(array, i, high, size, compare);
	}
	if (j > low)
	{
		StringsSort(array, low, j, size, compare);
	}
}


int GetParametersFile(FILE* file, char* text, int syms)
{
	if (text == NULL)
	{
		fputs("Error memory allocation for *text\n", stderr);
		exit(2);
	}
	if (fread(text, 1, syms, file) != syms)
	{
		fputs("Error reading", stderr);
		exit(3);
	}
	int lines = 0;
	for (int i = 0; i < syms; i++)
	{
			lines += text[i] == '\n';
	}
	lines++;
	return lines;
}


void SeparateTextToLines(char* text, char** p)
{
	int sum = 0;
	int k = 0;
	for (int i = 0; text[sum] != '\0'; i++)
	{
		for (k = 0; text[sum] != '\0'; k++)
		{
			if (text[sum] == '\n')
			{
				sum++;
				break;
			}
			p[i][k] = text[sum];
			sum++;
		}
		p[i][++k] = '\0';
		p[i] = (char*)realloc(p[i], k * sizeof(char));
		if (p[i] == NULL)
		{
			fputs("Error memory reallocation for *p\n", stderr);
			exit(2);
		}
	}
}
