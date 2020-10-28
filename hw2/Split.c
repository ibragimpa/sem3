#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void Split(const char* string, char*** strings, const char* tokens, const int* tokensCount);


int main()
{
    char** strings[100];
    for(int i = 0; i < 100; i++)
    {
        strings[i] = malloc(sizeof(char)*100);
    }
    char* string = malloc(sizeof(char)*1000);
    char* tokens = malloc(sizeof(char)*10);
    int number_of_tokens = 0;
    scanf("%d", &number_of_tokens);
    for(int i = 0; i < number_of_tokens; i++)
    {
        scanf("%c", &tokens[i]);
    }
    fgets(string, 120, stdin);
    Split(string, &strings, tokens, &number_of_tokens);
    for(int i = 0; i < 10; i++)
    {
        printf("%s ", strings[i]);
    }
    return 0;
}


void Split(const char* string, char*** strings, const char* tokens,const int* tokensCount)
{
    char* ptr;
    ptr = strtok(string,  tokens);
    while (ptr != NULL)
    {
        printf ("%s\n",ptr);
        ptr = strtok (NULL, tokens);
    }
}
