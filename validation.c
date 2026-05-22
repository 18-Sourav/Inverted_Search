#include <ctype.h>
#include <string.h>
#include "validation.h"
#include "main.h"

// Function to find the indexing of the word
int hash_function(char *word)
{
    // Get the first character and convert to lowercase for indexing
    int index = tolower(word[0]) - 'a';

    // If it's an alphabet, return index 0-25
    if (index >= 0 && index <= 25)
        return index;

    // For non-alphabetic characters, use the last index (26)
    return 26;
}

//Function to validate the input files
int validate_file(int argc, char *argv[], file_list **file_head)
{
    int found_valid = 0;

    for (int i = 1; i < argc; i++)
    {
        // Check if file has .txt extension
        char *ext = strrchr(argv[i], '.');
        if (ext == NULL || strcmp(ext, ".txt") != 0)  //checking if it ends only with .txt with no extra characters
        {
            printf("Warning: %s is not a .txt file. Skipping.\n", argv[i]);
            continue;
        }

        // Check if file exists and can be opened
        FILE *fptr = fopen(argv[i], "r");
        if (fptr == NULL)
        {
            printf("Warning: %s does not exist or cannot be opened. Skipping.\n", argv[i]);
            continue;
        }
        fclose(fptr);

        // Check for duplicate files in the list
        file_list *temp = *file_head;
        int duplicate = 0;
        while (temp)
        {
            if (strcmp(temp->filename, argv[i]) == 0)
            {
                duplicate = 1;
                break;
            }
            temp = temp->next_file;
        }

        if (duplicate)
        {
            printf("Warning: %s is a duplicate entry. Skipping.\n", argv[i]);
            continue;
        }

        // Create a new node for the valid file list
        file_list *new_node = malloc(sizeof(file_list));
        if (new_node == NULL)
        {
            return FAILURE;
        }

        strcpy(new_node->filename, argv[i]);
        new_node->next_file = NULL;

        // Add to the list
        if (*file_head == NULL)  //if the file list is empty
        {
            *file_head = new_node;
        }
        else
        {
            file_list *last = *file_head;
            while (last->next_file)
            {
                last = last->next_file;
            }
            last->next_file = new_node;
        }
        found_valid = 1;
    }

    return found_valid ? SUCCESS : FAILURE;
}
