//Header from the Stack project and it is at C:\Users\DELL\source\repos\Stack_dinamic\Stack_dinamic\stack.h
#include "..\..\Stack_dinamic\Stack_dinamic\stack.h"
//Header from the SortOnegin project and it is at C:\Users\DELL\source\repos\Sort_Onegin\Sort_Onegin\sort_text.h
#include "..\..\Sort_Onegin\Sort_Onegin\sort_text.h"
#include "akinator.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>



int main(){
    FILE* file = fopen("tree_data.txt", "rb");
    if (file == NULL)
        errno = ErrorCode::ERRFILE;
    int syms = CountSymbols(file);
    char* text = (char*)calloc((syms + 1), sizeof(char));
    if (text == NULL)
        errno = ErrorCode::ERRALLOC;
    GetParametersTree(file, text, syms);
    fclose(file);

    Node* akinator = CreateNode();
    ReadFile(akinator, text);
    Akinator(akinator);
    FILE* file2 = fopen("tree_data.txt", "w");
    if (file2 == NULL)
        errno = ErrorCode::ERRFILE;
    WriteTree(akinator, file2);
    fclose(file2);
    Dump(akinator);
    free(text);
    ClearTree(akinator);
}
