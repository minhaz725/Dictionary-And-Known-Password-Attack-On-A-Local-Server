#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    FILE *dictionary;
    char str[200];
    char *user_input;
    char string[200];
    int found = 0;

    dictionary = fopen("/home/spellbreaker/SecurityProject/wordlist.txt", "r");

    while (fgets(str, sizeof(str), dictionary) != NULL)
    {
        int len_str = strlen(str) - 1;
        //int len_userinput = strlen(user_input) - 1;
        if(str[len_str] == '\n') str[len_str] = 0;

        printf("%s\n", str);
        //if( strcmp(string, str) == 0)
        //{
        //    printf("Found: %s\n", str);
        //    found++;
        //}
    }
    if(found == 0) printf("Not Found!\n");
    fclose(dictionary);
    return 0;
}
