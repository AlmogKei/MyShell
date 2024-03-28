#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <dirent.h>
#include <sys/wait.h>
#define SIZE_BUFF 4096
#define SIZE_HOSTNAME 64


void getLocation();

/**
 * @brief Reads input from the user until a newline character is encountered.
 * Example input: "ls -l"
 * @return A dynamically allocated string containing the user input.
 */
char *getInputFromUser();

/**
 * @brief Custom implementation of the strtok function to tokenize strings.
 * Example input: "cd Documents"
 * @param str The input string to be tokenized.
 * @param delim The delimiter characters.
 * @return A pointer to the next token in the string.
 */
char *my_strtok(char *str, const char *delim);

/**
 * @brief Splits a string into individual tokens based on space delimiter.
 * Example input: "cp source.txt destination.txt"
 * @param str The input string to be split.
 * @return An array of pointers to tokens.
 */
char **splitArgument(char *str);

/**
 * @brief Logs out the user and exits the program.
 * 
 * @param input The input string to be freed before logout.
 */
void logout(char *input);

/**
 * @brief Displays the arguments passed to the function.
 * 
 * @param arguments An array of strings representing the arguments.
 */
void echo(char **arguments);

/**
 * @brief Changes the current working directory.
 * Example input: "/path/to/source /path/to/destination"
 * @param path An array of strings representing the path.
 */
void cd(char **path);

/**
 * @brief Copies the contents of one file to another.
 * Example input: "/path/to/file.txt"
 * @param arguments An array of strings representing the source and destination files.
 */
void cp(char **arguments);

/**
 * 
 * @brief Lists the files in the current directory.
 */
void get_dir();

/**
 * @brief Deletes a file specified by the path.
 * 
 * @param path An array of strings representing the path of the file to be deleted.
 */
void delete(char **path);

/**
 * @brief Executes a system command.
 * 
 * @param arguments An array of strings representing the command and its arguments.
 */
void systemCall(char **arguments);

/**
 * @brief Executes two commands in a pipeline.
 * Example input: "ls -l | grep 'search_term'"
 * @param argv1 An array of strings representing the first command.
 * @param argv2 An array of strings representing the second command.
 */
void mypipe(char **argv1, char **argv2);

/**
 * @brief Moves a file from one location to another.
 * Example input: "/path/to/source /path/to/destination"
 * @param arguments An array of strings representing the source and destination paths.
 */
void move(char **arguments);

/**
 * @brief Counts the number of arguments passed to the function.
 * 
 * @param arguments An array of strings representing the arguments.
 */
void wordCount(char **arguments);

/**
 * @brief Prints the arguments passed to the function without spaces.
 * 
 * @param arguments An array of strings representing the arguments.
 */
void echoppend(char **arguments);

/**
 * @brief Prints the arguments passed to the function with spaces.
 * 
 * @param arguments An array of strings representing the arguments.
 */
void echorite(char **arguments);

/**
 * @brief Reads and prints the contents of a file.
 * 
 * @param arguments An array of strings representing the filename.
 */
void readfile(char **arguments);
