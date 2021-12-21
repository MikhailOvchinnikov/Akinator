//Header from the SortOnegin project
#include "..\..\Sort_Onegin\Sort_Onegin\sort_text.h"
//Header from the Stack project
#include "C:\Users\DELL\source\repos\Stack_dinamic\Stack_dinamic\stack.h"
#include "akinator.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>

#define ValidPtr(ptr) if(!ptr) {errno = ErrorCode::ERRPTR; return -1;}
#define LastNode(ptr) if(!ptr) {return 0;}


typedef struct Node {
    char field[100] = {};
    Node* left;
    Node* right;
} Node;


void FileLogAkin(const char* format, ...){
    static FILE* log_file = fopen("akin_log.txt", "w");
    va_list args;
    va_start(args, format);
    vfprintf(log_file, format, args);
    va_end(args);
}


Node* CreateNode(){
    Node* node = (Node*)calloc(1, sizeof(Node));
    if (node == NULL){
        errno = ErrorCode::ERRPTR;
        return nullptr;
    }
    node->left = NULL;
    node->right = NULL;
    return node;
}


int GetParametersTree(FILE* file, char* text, int syms){
    ValidPtr(text);
    if (fread(text, 1, syms, file) != syms){
        errno = ErrorCode::ERRREADFILE;
        return -1;
    }
    return 0;
}


int ReadTree(Node* node){
    LastNode(node);
    ReadTree(node->left);
    FileLogAkin("field %s\n", node->field);
    ReadTree(node->right);
    return 0;
}


int NewAkElem(Node* node){
    ValidPtr(node);
    char new_hero[50] = {};
    char answer[50] = {};
    printf("What did you wish for?\n");
    scanf("%s", new_hero);
    printf("Write a question to define a difference between %s and %s\n", new_hero, node->field);
    getchar();
    char sym = 0;
    for (int i = 0; i < 50; i++){
        if ((sym = getchar()) == '\n'){
            answer[i] = '\0';
            break;
        }
        answer[i] = sym;
    }
    node->left = CreateNode();
    node->right = CreateNode();
    if (node->left == NULL || node->right == NULL)
        return -1;
    strncpy(node->left->field, node->field, 100);
    strncpy(node->right->field, new_hero, 100);
    strncpy(node->field, answer, 100);
    return 0;
}


int Akinator(Node* node){
    LastNode(node);
    char answer[50] = {};
    printf("%s\n", node->field);
    if (node->left != NULL && node->right != NULL)
        scanf("%s", answer);
    else{
        printf("Right?\n");
        scanf("%s", answer);
        if (!strcmp(answer, "yes"))
            printf("The end of the game\n");
        else if (!strcmp(answer, "no"))
            NewAkElem(node);
        return 0;
    }

    if (!strcmp(answer, "yes"))
        Akinator(node->right);
    else if (!strcmp(answer, "no"))
        Akinator(node->left);
    return 0;
}


int WriteTree(Node* node, FILE* file){
    ValidPtr(file);
    LastNode(node);
    fprintf(file, "(");
    WriteTree(node->left, file);
    fprintf(file, "%s", node->field);
    WriteTree(node->right, file);
    fprintf(file, ")");
    return 0;
}


int ReadFile(Node* node, char* text, int sym){
    ValidPtr(text);
    LastNode(node);
    static int i = 1;
    char temp_str[100] = {};
    int ind = 0;
    if (text[i] == '('){
        node->left = CreateNode();
        i++;
        ReadFile(node->left, text, sym);
        ReadFile(node, text, sym);
        node->right = CreateNode();
        i++;
        ReadFile(node->right, text, sym);
    }
    else{
        ind = i;
        while (text[i] != ')' && text[i] != '('){
            temp_str[i - ind] = text[i];
            i++;
        }
        temp_str[i - ind] = '\0';
        strncpy(node->field, temp_str, 100);
        while (text[i] == ')')
            i++;
    }
    return 0;
}


int DrawTree(Node* node, FILE* file){
    static int i = 0;
    if (node->left == NULL && node->right == NULL){
        fprintf(file, "\t\"box %d\" [shape=plaintext, label=<\n<table>\n\t", i);
        fprintf(file, "<tr><td colspan='2' port='field'>%s</td></tr><tr><td port='left'>NULL</td><td port='right'>NULL</td></tr>\n\t",
            node->field);
        fprintf(file, "</table>\n\t>]; \n");
        i++;
        return 0;
    }
    fprintf(file, "\t\"box %d\" [shape=plaintext, label=<\n<table>\n\t", i);
    fprintf(file, "<tr><td colspan='2' port='field'>%s</td></tr><tr><td port='left'>no</td><td port='right'>yes</td></tr>\n\t",
        node->field);
    fprintf(file, "</table>\n\t>]; \n");
    i++;
    DrawTree(node->left, file);
    DrawTree(node->right, file);
    return i;
}


int DrawWays(Node* node, FILE* file, Stack* stack){
    if (node->left == NULL && node->right == NULL)
        return 0;
    static int i = 0;
    fprintf(file, "\t\"box %d\":left->\"box %d\":field;\n", i, i + 1);
    Push(stack, i);
    i++;
    DrawWays(node->left, file, stack);
    float ind = 0;
    Pop(stack, &ind);
    fprintf(file, "\t\"box %d\":right->\"box %d\":field;\n", (int)ind, i + 1);
    i++;
    DrawWays(node->right, file, stack);
    return 0;
}


void Dump(Node* node){
    FILE* file = fopen("akinator_graf.txt", "w");

    fprintf(file, "digraph List {\n");
    fprintf(file, "rankdir=TB;\n");

    DrawTree(node, file);

    Stack* stack = CreateStack("stack");
    DrawWays(node, file, stack);
    ClearStk(stack);
    fprintf(file, "}\n");
    fclose(file);
}