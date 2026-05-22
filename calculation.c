#include "main.h"
#include "calculation.h"
#include "validation.h"

int create_database(word_node** hash_table, file_list *file_head)
{
    while (file_head != NULL)
    {
        FILE *fptr = fopen(file_head->filename, "r");     
        if (fptr == NULL)
        {
            printf("Error: Could not open file %s\n", file_head->filename);
            file_head = file_head->next_file;
            continue;
        }

        char word[BUFF_SIZE];
        while (fscanf(fptr, "%s", word) != EOF)
        {
            int index = hash_function(word);
            word_node *prev_word = NULL;
            word_node *curr_word = hash_table[index];

            // Searching for the word in the hash table at the calculated index
            while (curr_word != NULL)
            {
                if (strcmp(curr_word->word, word) == 0)
                {
                    break;
                }
                prev_word = curr_word;
                curr_word = curr_word->next_word;
            }

            if (curr_word == NULL)
            {
                // If the word not found, create a new word_node
                word_node *new_word = malloc(sizeof(word_node));
                if (new_word == NULL)
                {
                    fclose(fptr);
                    return FAILURE;
                }
                strcpy(new_word->word, word);
                new_word->total_word_cnt = 1;
                new_word->next_word = NULL;

                // Create the first file_node for this word
                file_node *new_file = malloc(sizeof(file_node));
                if (new_file == NULL)
                {
                    free(new_word);
                    fclose(fptr);
                    return FAILURE;
                }
                strcpy(new_file->file_name, file_head->filename);
                new_file->word_cnt = 1;
                new_file->file_list = NULL;

                new_word->word_fptr = new_file;

                // Link the new word node into the hash table
                if (prev_word == NULL)
                {
                    hash_table[index] = new_word;
                }
                else
                {
                    prev_word->next_word = new_word;
                }
            }
            else
            {
                // If the Word is found, update the existing word_node
                curr_word->total_word_cnt++;

                // Search for the file in the word's file list
                file_node *prev_file_node = NULL;
                file_node *curr_file_node = curr_word->word_fptr;
                while (curr_file_node != NULL)
                {
                    if (strcmp(curr_file_node->file_name, file_head->filename) == 0)
                    {
                        break;
                    }
                    prev_file_node = curr_file_node;
                    curr_file_node = curr_file_node->file_list;
                }

                if (curr_file_node == NULL)
                {
                    // File is not found for this word, creating a new file_node and appending it
                    file_node *new_file = malloc(sizeof(file_node));
                    if (new_file == NULL)
                    {
                        fclose(fptr);
                        return FAILURE;
                    }
                    strcpy(new_file->file_name, file_head->filename);
                    new_file->word_cnt = 1;
                    new_file->file_list = NULL;
                    
                    if (prev_file_node != NULL)
                    {
                        prev_file_node->file_list = new_file;
                    }
                    else
                    {
                        curr_word->word_fptr = new_file;
                    }
                }
                else
                {
                    // If File is found, just increment the word count for this file
                    curr_file_node->word_cnt++;
                }
            }
        }
        fclose(fptr);   //closing the current file
        file_head = file_head->next_file;  // moving to the next file
    }
    return SUCCESS;
}
