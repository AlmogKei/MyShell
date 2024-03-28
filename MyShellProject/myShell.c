#include "myShell.h"
#include "myFunction.h"

int main()
{
    welcome(); // Assuming welcome() is a function that displays a welcome message
    
    while (1)
    {
        // Get current location and display prompt
        getLocation();
        
        // Get user input
        char *input = getInputFromUser();
        
        // Display the input for verification
        puts(input);
        
        // Split the input into arguments
        char **arguments = splitArgument(input);
        
        // Display each argument for verification
        for (int i = 0; *(arguments + i) != NULL; i++)
        {
            puts(*(arguments + i));
            puts(arguments[i]);
        }
        
        // Check for exit command
        if (strcmp(input, "exit") == 0 || strncmp(input, "exit ", 5) == 0)
            logout(input);
        
        // Check for echo command
        if (strcmp(input, "echo") == 0)
            echo(arguments);
        
        // Check for cd command
        else if (strcmp(input, "cd") == 0)
            cd(arguments);
        
        // Check for cp command
        else if (strcmp(input, "cp") == 0)
            cp(arguments);
        
        // Check for delete command
        else if (strcmp(input, "delete") == 0)
            delete(arguments);
        
        // Check for dir command
        else if (strcmp(input, "dir") == 0)
            get_dir();
        
        // Check for move command
        else if (strcmp(input, "move") == 0)
            move(arguments);
        
        // Check for wordCount command
        else if (strcmp(input, "wordCount") == 0)
            wordCount(arguments);
        
        // Check for echoppend command
        else if (strcmp(input, "echoppend") == 0)
            echoppend(arguments);
        
        // Check for echorite command
        else if (strcmp(input, "echorite") == 0)
            echorite(arguments);
        
        // Check for readfile command
        else if (strcmp(input, "readfile") == 0)
            readfile(arguments);
        
        // Execute other commands using system call
        else
        {
            systemCall(arguments);
            wait(NULL);
        }
        
        // Free allocated memory
        free(arguments);
        free(input);
    }
    
    return 0;
}



void welcome()
{
    puts(
        "    AAAAA     L           M       M        OOOOOO        GGGGGGGG    |   Welcom to Almog Shell                           \n"
        "   A     A    L           MM     MM       O      O      G            |   Version 0.0.1                                   \n"
        "  A       A   L           M M   M M      O        O     G            |                                                   \n"
        "  AAAAAAAAA   L           M  M M  M     O          O    G   GGGGGG   |   https://github.com/AlmogKei/MyShell                       \n"
        "  A       A   L           M   M   M      O        O     G        G   |                                                   \n"
        "  A       A   L           M       M       O      O      G        G   |   Have Fun!                                       \n"
        "  A       A   LLLLLLLL    M       M        OOOOOO       GGGGGGGGGG   |                                                   \n");
}
