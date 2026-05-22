#ifndef VALIDATION_H
#define VALIDATION_H

#include "main.h"

//Fucntion to get the index of the input word
int hash_function(char *word);

// Validation of the inout file in the CLI
int validate_file(int argc, char *argv[], file_list **file_head);
#endif