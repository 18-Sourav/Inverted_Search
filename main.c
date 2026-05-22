#include "main.h"
#include "validation.h"
#include "calculation.h"

/**
 * @brief Main entry point for the Inverted Search project.
 *        Handles command line arguments, validates files, and initiates database creation.
 */
int main(int argc, char *argv[])
{
    // Check if enough arguments are provided
    if (argc < 2)
    {
        printf("Usage: %s <file1.txt> <file2.txt> ...\n", argv[0]);
        return FAILURE;
    }

    // Initialize the hash table to NULL
    word_node *hash_table[SIZE] = {NULL};

    // Head of the list containing valid filenames
    file_list *file_head = NULL;

    // 1. Validate the input files provided via command line
    if (validate_file(argc, argv, &file_head) != SUCCESS)
    {
        printf("Error: File validation failed or no valid files provided.\n");
        return FAILURE;
    }

    // 2. Create the database (inverted index) from the validated files
    if (create_database(hash_table, file_head) == SUCCESS)
    {
        printf("Success: Database created successfully.\n");
    }
    else
    {
        printf("Error: Database creation failed.\n");
        return FAILURE;
    }

    // Note: In a complete implementation, we would add search, display, 
    // save, and update functionality here.

    return SUCCESS;
}