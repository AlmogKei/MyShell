#include "myFunction.h"

// בפונקציה הנ"ל קיבלנו את הנתיב ממנו אנחנו מריצים את התוכנית שלנו
//  עליכם לשדרג את הנראות של הנתיב כך ש-בתחילת הנתיב יופיע שם המחשב (כמו בטרמינל המקורי) בסוף יופיע הסימן דולר
//  ולאחר הדולר ניתן אפשרות למשתמש להזין מחרוזת מבלי שנרד שורה.
void getLocation()
{
    struct passwd *omen; // מצביע על פרטי המשתמש במערכת ההפעלה
    omen = getpwuid(getuid());
    if (omen == NULL)
    {
        printf("Error\n");
        return;
    }
    char location[SIZE_BUFF];
    if (getcwd(location, SIZE_BUFF) == NULL)
        printf("Error\n");
    else
    {
        printf("\033[0;31m"); // צבעית הטקסט באדום
        printf("%s", location);
        printf("Username: %s@%s\033[0m$ ", omen->pw_name, omen->pw_name);
        printf("\033[0m");
    }
}

char *getInputFromUser()
{
    char ch;
    int size = 1;
    int index = 0;
    char *str = (char *)malloc(size * sizeof(char));
    while ((ch = getchar()) != '\n')
    {
        *(str + index) = ch;
        size++;
        index++;
        str = (char *)realloc(str, size);
    }
    *(str + index) = '\0';
    return str;
}

// עליכם לממש את הפונקציה strtok כלומר שהפונקציה הנ"ל תבצע בדיוק אותו הדבר רק בלי השימוש בפונקציה strtok
char *my_strtok(char *str, const char *delim) {
    static char *next_token = NULL;  // נשמור את המצב של האינדקס בין הקריאות לפונקציה

    // אם str הוא NULL, זהו הקריאה הבאה למחרוזת הנוכחית
    if (str != NULL) {
        next_token = str;  // איפוס המצב והצבת המחרוזת החדשה לניתוח
    }

    // אם המצב הנוכחי הוא NULL, זהו הסיום של הניתוח
    if (next_token == NULL) {
        return NULL;
    }

    // מצא את המיקום הבא של התו המופיע ב-delimiter או הסוף של המחרוזת
    char *token_start = next_token;
    char *token_end = strpbrk(next_token, delim);

    // אם לא נמצא delimiter, אז זו הסיום של המחרוזת
    if (token_end == NULL) {
        next_token = NULL;  // הגדרת המצב ל־NULL לקראת הקריאה הבאה
    } else {
        *token_end = '\0';  // החלפת ה-delimiter ב־NULL terminator
        next_token = token_end + 1;  // הצבת המצב לאחר ה-delimiter לקראת הקריאה הבאה
    }

    return token_start;
}

char **splitArgument(char *str)
{
    char *subStr;
    subStr = strtok(str, " ");
    int size = 2;
    int index = 0;
    char **argumnts = (char **)malloc(size * sizeof(char *));
    *(argumnts + index) = subStr; // [subStr,subStr,subStr,subStr,NULL]
    while ((subStr = strtok(NULL, " ")) != NULL)
    {
        index++;
        size++;
        argumnts = (char **)realloc(argumnts, size * sizeof(char *));
        *(argumnts + index) = subStr;
    }
    *(argumnts + (index + 1)) = NULL;

    return argumnts;
}
    void logout(char *input)
    {
        free(input);
        puts("logout");
        exit(EXIT_SUCCESS); // EXIT_SUCCESS = 0
    }

    void echo(char **arguments)
{
    int i = 1;
    while (*(arguments + i))
        printf("%s ", *(arguments + i));
    i=1;
    while (arguments[i])
        printf("%s ", arguments[i]);

    while (*(++arguments))
        printf("%s ", *arguments);

    puts("");
}
    void cd(char **path)
    {
        // cd "OneDrive - Ariel University"

        // path = [cd,OneDrive,-,Ariel,University",NULL]
        if (strncmp(path[1], "\"", 1) != 0 && path[2] != NULL)
            printf("-myShell: cd: too many arguments\n");

        // else if (strncmp(path[4], "\"", 1) == 0)
        // {
        //     // path = [cd,"SoftwareTeach,-,Ariel,University",NULL]
        //     // int i = 2;
        //     // while (path[i] != NULL)
        //     // {
        //     //     i++;
        //     // }
        //     // path[i - 1];
        //     // size = strlen(path[i - 1])-1
        //     // strcmp(path[i - 1]+size, "\"") == 0
        //     // // path = [cd\0,"OneDrive\0,-\0,Ariel\0,University"\0,NULL]
        //     // // path = [cd\0,"OneDrive,-,Ariel,University"\0,NULL]
        //     if (chdir(path[1]) != 0)
        //     {
        //         printf("-myShell: cd: %s: No such file or directory", path[1]);
        //     }
        // }
        else if (chdir(path[1]) != 0)
            printf("-myShell: cd: %s: No such file or directory\n", path[1]);
    }

    void cp(char **arguments)
    {
        char ch;
        FILE *src, *des;
        if ((src = fopen(arguments[1], "r")) == NULL)
        {
            puts("error");
            return;
        }

        if ((des = fopen(arguments[2], "w")) == NULL)
        {
            puts("error");
            fclose(src);
            return;
        }
        while ((ch = fgetc(src)) != EOF)
            fputc(ch, des);

        fclose(src);
        fclose(des);
    }

// rm -f *.o *.out
// gcc -Wall -g -c myShell.c
// gcc -Wall -g -c myFunction.c
// gcc -Wall -g -o myShell myShell.o myFunction.o
// ./myShell

// בכל שינוי יש לבצע קומיט מתאים העבודה מחייבת עבודה עם גיט.
// ניתן להוסיף פונקציות עזר לתוכנית רק לשים לב שלא מוסיפים את חתימת הפונקציה לקובץ הכותרות