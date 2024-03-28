#include "myFunction.h"

void getLocation() {
    struct passwd *omen = getpwuid(getuid());
    if (omen == NULL) {
        perror("getpwuid");
        exit(EXIT_FAILURE);
    }

    char location[SIZE_BUFF];
    if (getcwd(location, SIZE_BUFF) == NULL) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    printf("\033[0;31m%s", location);
    printf("Username: %s@%s\033[0m$ ", omen->pw_name, omen->pw_name);
}

char *getInputFromUser() {
    int size = 1;
    int ch;
    char *str = (char *)malloc(size * sizeof(char));
    if (str == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        str[size - 1] = ch;
        size++;
        str = (char *)realloc(str, size * sizeof(char));
        if (str == NULL) {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
    }

    str[size - 1] = '\0';
    return str;
}

char *my_strtok(char *str, const char *delim) {
    static char *next_token = NULL;

    if (str != NULL) {
        next_token = str;
    } else {
        if (next_token == NULL || *next_token == '\0')
            return NULL;
    }

    char *token = next_token;
    next_token = strpbrk(next_token, delim);

    if (next_token != NULL) {
        *next_token = '\0';
        next_token += 1;
    }

    return token;
}

char **splitArgument(char *str) {
    char *subStr;
    subStr = strtok(str, " ");
    int size = 2;
    int index = 0;
    char **arguments = (char **)malloc(size * sizeof(char *));
    if (arguments == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    arguments[index] = subStr;
    while ((subStr = strtok(NULL, " ")) != NULL) {
        index++;
        size++;
        arguments = (char **)realloc(arguments, size * sizeof(char *));
        if (arguments == NULL) {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        arguments[index] = subStr;
    }
    arguments[index + 1] = NULL;

    return arguments;
}

void logout(char *input) {
    free(input);
    puts("logout");
    exit(EXIT_SUCCESS);
}

void echo(char **arguments) {
    int i = 1;
    while (arguments[i] != NULL) {
        printf("%s ", arguments[i]);
        i++;
    }
    printf("\n");
}

void cd(char **path) {
    if (path[1] == NULL) {
        printf("-myShell: cd: missing directory\n");
        return;
    }
    if (path[2] != NULL) {
        printf("-myShell: cd: too many arguments\n");
        return;
    }
    if (chdir(path[1]) != 0) {
        perror("-myShell: cd");
    }
}

void cp(char **arguments) {
    if (arguments[1] == NULL || arguments[2] == NULL) {
        printf("-myShell: cp: missing source or destination file\n");
        return;
    }
    FILE *src = fopen(arguments[1], "r");
    if (src == NULL) {
        perror("-myShell: cp");
        return;
    }

    FILE *des = fopen(arguments[2], "w");
    if (des == NULL) {
        perror("-myShell: cp");
        fclose(src);
        return;
    }

    int ch;
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, des);
    }

    fclose(src);
    fclose(des);
}

void get_dir() {
    DIR *dir = opendir("./");
    if (dir == NULL) {
        perror("-myShell: get_dir");
        return;
    }

    struct dirent *ent;
    while ((ent = readdir(dir)) != NULL) {
        printf("%s ", ent->d_name);
    }
    puts("");
    closedir(dir);
}

void delete(char **path) {
    if (path[1] == NULL) {
        printf("-myShell: delete: missing filename\n");
        return;
    }
    if (unlink(path[1]) != 0) {
        perror("-myShell: delete");
    }
}

void systemCall(char **arguments) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        if (execvp(arguments[0], arguments) == -1) {
            perror("-myShell: execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        wait(NULL);
    }
}

void mypipe(char **argv1, char **argv2) {
    int fildes[2];
    if (pipe(fildes) == -1) {
        perror("-myShell: pipe");
        return;
    }

    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        return;
    }

    if (pid1 == 0) {
        close(fildes[0]);
        dup2(fildes[1], STDOUT_FILENO);
        close(fildes[1]);
        execvp(argv1[0], argv1);
        perror("-myShell: execvp");
        exit(EXIT_FAILURE);
    }

    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        return;
    }

    if (pid2 == 0) {
        close(fildes[1]);
        dup2(fildes[0], STDIN_FILENO);
        close(fildes[0]);
        execvp(argv2[0], argv2);
        perror("-myShell: execvp");
        exit(EXIT_FAILURE);
    }

    close(fildes[0]);
    close(fildes[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

void move(char **arguments) {
    if (arguments[1] == NULL || arguments[2] == NULL || arguments[3] != NULL) {
        printf("-myShell: move: invalid arguments\n");
        return;
    }
    if (rename(arguments[1], arguments[2]) != 0) {
        perror("-myShell: move");
    }
}

void wordCount(char **arguments) {
    int count = 0;
    while (arguments[count] != NULL) {
        count++;
    }
    printf("Number of arguments: %d\n", count);
}

void echoppend(char **arguments) {
    int i = 1;
    while (arguments[i] != NULL) {
        printf("%s", arguments[i]);
        i++;
    }
    printf("\n");
}

void echorite(char **arguments) {
    int i = 1;
    while (arguments[i] != NULL) {
        printf("%s ", arguments[i]);
        i++;
    }
    printf("\n");
}

void readfile(char **arguments) {
    if (arguments[1] == NULL) {
        printf("-myShell: readfile: missing filename\n");
        return;
    }
    FILE *file = fopen(arguments[1], "r");
    if (file == NULL) {
        perror("-myShell: readfile");
        return;
    }

    char buffer[SIZE_BUFF];
    while (fgets(buffer, SIZE_BUFF, file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);
}


// rm -f *.o *.out
// gcc -Wall -g -c myShell.c
// gcc -Wall -g -c myFunction.c
// gcc -Wall -g -o myShell myShell.o myFunction.o
// ./myShell

// בכל שינוי יש לבצע קומיט מתאים העבודה מחייבת עבודה עם גיט.
// ניתן להוסיף פונקציות עזר לתוכנית רק לשים לב שלא מוסיפים את חתימת הפונקציה לקובץ הכותרות