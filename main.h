#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Return status codes
#define SUCCESS 0
#define FAILURE -1
#define NO_ELEMENTS -2
#define FILE_NOT_FOUND -3
#define WORD_NOT_FOUND -4

#define SIZE 27    //A-Z and others
#define BUFF_SIZE 255

//FILE LIST for storing the input file names
typedef struct _file_list
{
    char filename[BUFF_SIZE];
    struct _file_list *next_file;  //to point to the next input file given in CLI
}file_list;

//FILE LIST for storing the each word file list
typedef struct _file_node
{
    char file_name[BUFF_SIZE];
    int word_cnt;
    struct _file_node *file_list;  //to point to other files including the same word in it

}file_node;

// WORD LIST for storing the list of each alaphabet
typedef struct _word_node
{  
    char word[BUFF_SIZE];
    int total_word_cnt;
    file_node *word_fptr;
    struct _word_node *next_word; // to point to next word of the same alphabet
}word_node;

#endif