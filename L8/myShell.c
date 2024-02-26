#include "myShell.h"
#include "myFunction.h"

int main()
{
    welcome();
    while (1)
    {
        getLocation();
        char *input = getInputFromUser();
        puts(input);
        char **arguments = splitArgument(input);
        for (int i = 0; *(arguments + i) != NULL; i++)
        {
            puts(*(arguments + i));
            puts(arguments[i]);
        }

        if (strcmp(input, "exit") == 0 || strncmp(input, "exit ", 5) == 0)
            logout(input);

        if (strcmp(input, "echo") == 0)
            echo(arguments);
        else if (strcmp(input, "cd") == 0)
            cd(arguments);
        else if (strcmp(input, "cp") == 0)
            cp(arguments);
        free(arguments);
        free(input);
        break;
    }
    char str[] = "Hello World";
    char *token = my_strtok(str, " ");
    while (token != NULL)
    {
        printf("Token: %s\n", token);
        token = my_strtok(NULL, " ");
    }

    return 0;
}

// יש לכתוב את פונקציית הברוכים הבאים כרצונכם אבל קצת יותר ממה שמוצג מטה לדוגמא:
void welcome()
{
    puts(
        "    AAAAA     L           M       M        OOOOOO        GGGGGGGG    |   Welcom to Almog Shell                           \n"
        "   A     A    L           MM     MM       O      O      G            |   Version 0.0.1                                   \n"
        "  A       A   L           M M   M M      O        O     G            |                                                   \n"
        "  AAAAAAAAA   L           M  M M  M     O          O    G   GGGGGG   |   https://github.com/<user>                       \n"
        "  A       A   L           M   M   M      O        O     G        G   |                                                   \n"
        "  A       A   L           M       M       O      O      G        G   |   Have Fun!                                       \n"
        "  A       A   LLLLLLLL    M       M        OOOOOO       GGGGGGGGGG   |                                                   \n");
}
