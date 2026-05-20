#include<ctype.h>
#include "hash.h"

//Function to map each with the respective index
int hash_function(char *word)
{
    int index = tolower(word[0])-'a';

    if(index >=0 && index <=25)
        return index;   //for alphabets return the alphabetical index

    //for others return the last index    
    return 26;
}