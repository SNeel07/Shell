#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>



//Declarations for the built-ins
//------------------------------

int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);



//Built-ins to be used
//--------------------

char *builtin_str[] = {
    "cd", 
    "help", 
    "exit"
};

int (*builtin_func[])(char **) = {
    &lsh_cd, 
    &lsh_help, 
    &lsh_exit
};

int lsh_num_builtins()
{
    return sizeof(builtin_str)/sizeof(char *);
}



//Implementing the built-in functions
//------------------------------------

//1. cd function
int lsh_cd(char **args)
{
    if(args[1] == NULL)
    fprintf(stderr, "lsh: expected argument to \"cd\"n");
    else
    {
        if(!SetCurrentDirectory(args[1]))
        fprintf(stderr, "sld: cd failed (%lu)\n", GetLastError());
        else
        {
            char cwd[512];

            GetCurrentDirectory(sizeof(cwd), cwd);
            printf("Now in: %s\n", cwd);
        }
    }

    return 1;
}


//2. help function
int lsh_help(char **args)
{
    printf("Built in commands: \n");
    printf("  cd <dir>\n");
    printf("  help\n");
    printf("  exit\n");

    return 1;
}

//3. exit function
int lsh_exit(char **args)
{
    printf("Exiting shell.....");
    return 0;
}



//Launch the program and wait for it to terminate.
//------------------------------------------------

int lsh_launch(char **args)
{
    char cmdLine[512] = "";

    int i;
    for(i=0;args[i]!=NULL;i++)
    {
        if(i>0)
        strcat(cmdLine, " ");
        if(strchr(args[i], ' '))
        {
            strcat(cmdLine, "\"");
            strcat(cmdLine, args[i]);
            strcat(cmdLine, "\"");
        }
        else
        strcat(cmdLine, args[i]);
    }


    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;


    //Create the process usingWindows API
    //------------------------------------

    BOOL success = CreateProcess(
        NULL,
        cmdLine,
        NULL, NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi
    );


    if(!success)
    fprintf(stderr, "lsh: CreateProcess failed (%lu)\n", GetLastError());
    else
    {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    return 1;
}


//Execute the shell
//------------------

int lsh_execute(char **args)
{
    if(args[0] == NULL)
    return 1;

    if(strcmp(args[0], "cd") == 0)
    return lsh_cd(args);
    else if(strcmp(args[0], "help") == 0)
    return lsh_help(args);
    else if(strcmp(args[0], "exit") == 0)
    return lsh_exit(args);
    else
    return lsh_launch(args);
}



//Read the given input line
//--------------------------

#define LSH_RL_BUFSIZE 1024

char *lsh_read_line(void)
{
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if(!buffer)
    {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        c = getchar();

        if(c == EOF)
        exit(EXIT_SUCCESS);
        else if(c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        buffer[position] = c;

        position ++;


        if(position>=bufsize)
        {
            bufsize += LSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);

            if(!buffer)
            {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}



//Split the command into tokens
//------------------------------

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char **lsh_split_line(char *line)
{
    int bufsize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token, **tokens_backup;

    if(!tokens)
    {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, LSH_TOK_DELIM);

    while(token!=NULL)
    {
        tokens[position] = token;
        position++;


        if(position>=bufsize)
        {
            bufsize += LSH_TOK_BUFSIZE;
            tokens_backup = tokens;
            tokens = realloc(tokens, bufsize *sizeof(char *));

            if(!tokens)
            {
                free(tokens_backup);
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, LSH_TOK_DELIM);
    }

    tokens[position] = NULL;

    return tokens;
}



//Execution loop
//--------------

void lsh_loop(void)
{
    char *line;
    char **args;
    int status;
    
    do
    {
        printf("> ");
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);

        free(line);
        free(args);
    } while (status);
    
}



//Driver Code
//-----------

int main()
{
    printf("NEEL's SHELL\n");
    printf("This is just a basic implementation of a shell.....\n");
    printf("Type the program names and arguments and press enter.\n");
    printf("Type 'help' to get started\n");


    lsh_loop();


    return EXIT_SUCCESS;
}