#pragma once
#include <stdio.h>

extern struct Node;

enum ErrorCode {
	ERRFILE = 1,
	ERRPTR,
	ERRREADFILE,
	ERRALLOC
};

/// <summary>
/// Write data to the log file
/// </summary>
/// <param name="format">Format writing data</param>
/// <param name="">Params for writing</param>
void FileLogAkin(const char* format, ...);

/// <summary>
/// Allocate memory for node of the tree
/// </summary>
/// <returns>Pointer to allocated memory or nullptr if error occured</returns>
Node* CreateNode();


/// <summary>
/// Read a data from a file
/// </summary>
/// <param name="file">Reading file</param>
/// <param name="text">Array for data</param>
/// <param name="syms">Number of symbols</param>
/// <returns>-1 if an error occured, else 0</returns>
int GetParametersTree(FILE* file, char* text, int syms);

/// <summary>
/// Read all nodes of the tree and write them to the log file
/// </summary>
/// <param name="node">Transmitted root of the tree</param>
/// <returns>0</returns>
int ReadTree(Node* node);


/// <summary>
/// Request name of the all fields of a new node and add it to the tree
/// </summary>
/// <param name="node">Transmitted root of the tree</param>
/// <returns>-1 if an error occured, else 0</returns>
int NewAkElem(Node* node);


/// <summary>
/// Starts game and requests answers to questions to guess the character
/// </summary>
/// <param name="node">Transmitted root of the tree</param>
/// <returns>-1 if an error occured, else 0</returns>
int Akinator(Node* node);


/// <summary>
/// Write tree to the file in text format
/// </summary>
/// <param name="node">Transmitted root of the tree</param>
/// <param name="file">name of the file</param>
/// <returns>-1 if an error occured, else 0</returns>
int WriteTree(Node* node, FILE* file);


/// <summary>
/// Parse array of data to create struct of tree from the text format
/// </summary>
/// <param name="root">Transmitted root of the tree</param>
/// <param name="text">Data array</param>
/// <param name="sym">Number of symbols</param>
/// <returns>-1 if an error occured, else 0</returns>
int ReadFile(Node* node, char* text, int sym);


/// <summary>
/// Write tree in the dot format for png view
/// </summary>
/// <param name="node">Transmitted root of the tree</param>
void Dump(Node* node);


/// <summary>
/// Write to the file a data in dot format
/// </summary>
/// <param name="node">Transmitted root of the tree</param>
/// <param name="file">File for writing data</param>
/// <returns>Number of writed node</returns>
int DrawTree(Node* node, FILE* file);
