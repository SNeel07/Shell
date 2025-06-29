#### Step-by-Step Tutorial: Building Your Own Shell/Terminal (Like a Super Cool Command Center!)



Hi there! Imagine you’re building your very own command center, like the control room in a spaceship, where you can type commands to make your computer do awesome things. That’s what a **shell** is —a program that lets you talk to your computer by typing commands. This tutorial will guide you, step by step, to create a simple shell in a language called **C**.

&nbsp;Think of it like building a toy robot—you’ll put together small pieces, and by the end, it’ll work like magic!



This shell will let you:



\- Change folders (like moving to a different room in your spaceship).

\- Show a help menu (like a guidebook for your command center).

\- Exit the shell (like turning off the spaceship’s controls).

\- Run other programs (like launching mini-robots from your command center).



We’ll explain every part of the code, including what each \*\*header file\*\* (like a toolbox) and \*\*function\*\* (like a robot worker) does. Let’s get started!



**--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------**



###### **Step 1: Understanding the Tools (Header Files)**



Before we build our shell, we need some toolboxes (called \*\*header files\*\* in C). These toolboxes give our program special powers to do things like print text or run other programs. Here’s what we’re using:



* **#include <stdio.h>**



&nbsp; - This is the \*\*Standard Input/Output\*\* toolbox.

&nbsp; - It lets our program \*\*print text\*\* to the screen (like saying “Hello!”) and \*\*read text\*\* you type (like listening to your commands).

&nbsp; - Example: It’s like a megaphone for talking and ears for listening.



* **#include <stdlib.h>**



&nbsp; - This is the \*\*Standard Library\*\* toolbox.

&nbsp; - It helps with things like \*\*allocating memory\*\* (reserving space in the computer’s brain for our work) and exiting the program safely.

&nbsp; - Example: It’s like a storage box where we keep extra paper to write notes.



* **#include <string.h>**



&nbsp; - This is the \*\*String Handling\*\* toolbox.

&nbsp; - It helps us work with \*\*text\*\* (called strings in coding), like splitting words or combining them.

&nbsp; - Example: It’s like scissors and glue for cutting and pasting words.



* **#include <windows.h>**



&nbsp; - This is a special \*\*Windows\*\* toolbox (only for Windows computers).

&nbsp; - It lets us do cool Windows-specific things, like changing folders or running other programs.

&nbsp; - Example: It’s like a control panel for your spaceship that only works on a Windows spaceship.



These toolboxes are included at the top of our program so we can use their tools later.



**--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------**



###### **Step 2: Setting Up the Command Center (main() )**



Our shell starts with a **main** function, which is like the control room where everything begins. Here’s what it does:



\- Prints a welcome message: When you start the shell, it says, “NEEL’s SHELL” and gives you instructions, like “Type ‘help’ to get started.”

\- Calls the lsh\_loop function: This is like turning on the spaceship’s engine—it keeps the shell running, waiting for your commands.



Here’s the code for the main function:



**int main()**

**{**

    **printf("NEEL's SHELL\\n");**

    **printf("This is just a basic implementation of a shell.....\\n");**

    **printf("Type the program names and arguments and press enter.\\n");**

    **printf("Type 'help' to get started\\n");**



    **lsh\_loop();**



    **return EXIT\_SUCCESS;**

**}**





* **What’s happening?**

&nbsp; - printf is like a megaphone from `<stdio.h>` that prints text to the screen.

&nbsp; - lsh\_loop() is a function we’ll build later—it’s the heart of the shell, listening for your commands.

&nbsp; - return EXIT\_SUCCESS tells the computer, “Everything worked perfectly!” when the shell closes.





**--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------**



###### **Step 3: The Heart of the Shell (lsh\_loop())**



The **lsh\_loop** function is like the engine of your spaceship—it keeps running, waiting for you to type commands. Here’s what it does:



\- Prints a prompt: Shows **“> ”** on the screen to say, “I’m ready for your command!”

\- Reads your command: Waits for you to type something and press Enter.

\- Splits the command: Breaks your command into pieces (like splitting “cd folder” into “cd” and “folder”).

\- Executes the command: Decides what to do with your command (like changing folders or running a program).

\- Repeats: Keeps doing this until you type “exit.”



Here’s the code:



**void lsh\_loop(void)**

**{**

    **char \*line;**

    **char \*\*args;**

    **int status;**

    

    **do**

    **{**

        **printf("> ");**

        **line = lsh\_read\_line();**

        **args = lsh\_split\_line(line);**

        **status = lsh\_execute(args);**



        **free(line);**

        **free(args);**

    **} while (status);**

**}**





* **What’s happening?**

&nbsp; - char \*line: This is like a notebook where we store the command you type.

&nbsp; - char \*\*args: This is like a list of words from your command (e.g., “cd” and “folder”).

&nbsp; - int status: This is like a signal that says, “Keep going” (1) or “Stop” (0).

&nbsp; - printf("> "): Shows the prompt so you know the shell is ready.

&nbsp; - lsh\_read\_line(): Reads what you type (we’ll build this next).

&nbsp; - lsh\_split\_line(line): Splits your command into words (we’ll build this too).

&nbsp; - lsh\_execute(args): Runs your command (we’ll build this later).

&nbsp; - free(line) and free(args): Cleans up the notebook and word list so the computer doesn’t run out of space.

&nbsp; - while (status): Keeps the loop running as long as `status` is 1 (stops when you type “exit”).





**--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------**



###### **Step 4: Reading Your Commands (lsh\_read\_line())**



The **lsh\_read\_line** function is like a librarian who reads what you type and writes it in a notebook. It:



\- Creates a buffer (a notebook) to store your command.

\- Reads each letter you type until you press Enter.

\- Makes sure the notebook is big enough, even if you type a long command.



Here’s the code:



**#define LSH\_RL\_BUFSIZE 1024**



**char \*lsh\_read\_line(void)**

**{**

    **int bufsize = LSH\_RL\_BUFSIZE;**

    **int position = 0;**

    **char \*buffer = malloc(sizeof(char) \* bufsize);**

    **int c;**



    **if (!buffer)**

    **{**

        **fprintf(stderr, "lsh: allocation error\\n");**

        **exit(EXIT\_FAILURE);**

    **}**



    **while (1)**

    **{**

        **c = getchar();**



        **if (c == EOF)**

            **exit(EXIT\_SUCCESS);**

        **else if (c == '\\n')**

        **{**

            **buffer\[position] = '\\0';**

            **return buffer;**

        **}**

        **else**

            **buffer\[position] = c;**



        **position++;**



        **if (position >= bufsize)**

        **{**

            **bufsize += LSH\_RL\_BUFSIZE;**

            **buffer = realloc(buffer, bufsize);**



            **if (!buffer)**

            **{**

                **fprintf(stderr, "lsh: allocation error\\n");**

                **exit(EXIT\_FAILURE);**

            **}**

        **}**

    **}**

**}**





* **What’s happening?**

&nbsp; - #define LSH\_RL\_BUFSIZE 1024: Sets the notebook size to 1024 letters (a big notebook!).

&nbsp; - char \*buffer = malloc(sizeof(char) \* bufsize): Creates a notebook using `malloc` (from `<stdlib.h>`) to store your command.

&nbsp; - int c = getchar(): Reads one letter at a time (from `<stdio.h>`).

&nbsp; - If you press Enter (`\\n`), it adds a special mark (`\\0`) to say, “This is the end of the command,” and returns the notebook.

&nbsp; - If you type Ctrl+D (`EOF`), it exits the shell.

&nbsp; - If you type too many letters, it makes the notebook bigger using `realloc` (from `<stdlib.h>`).

&nbsp; - If something goes wrong (like running out of space), it prints an error and stops.





**--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------**



###### **Step 5: Splitting Commands into Words (lsh\_split\_line())**



When you type a command like “cd folder,” the **lsh\_split\_line** function is like a chef who chops your command into pieces (“cd” and “folder”). It:



\- Takes the command from the notebook.

\- Splits it into words using spaces, tabs, or Enter as separators.

\- Stores the words in a list.



Here’s the code:



**#define LSH\_TOK\_BUFSIZE 64**

**#define LSH\_TOK\_DELIM " \\t\\r\\n\\a"**



**char \*\*lsh\_split\_line(char \*line)**

**{**

    **int bufsize = LSH\_TOK\_BUFSIZE, position = 0;**

    **char \*\*tokens = malloc(bufsize \* sizeof(char \*));**

    **char \*token, \*\*tokens\_backup;**



    **if (!tokens)**

    **{**

        **fprintf(stderr, "lsh: allocation error\\n");**

        **exit(EXIT\_FAILURE);**

    **}**



    **token = strtok(line, LSH\_TOK\_DELIM);**



    **while (token != NULL)**

    **{**

        **tokens\[position] = token;**

        **position++;**



        **if (position >= bufsize)**

        **{**

            **bufsize += LSH\_TOK\_BUFSIZE;**

            **tokens\_backup = tokens;**

            **tokens = realloc(tokens, bufsize \* sizeof(char \*));**



            **if (!tokens)**

            **{**

                **free(tokens\_backup);**

                **fprintf(stderr, "lsh: allocation error\\n");**

                **exit(EXIT\_FAILURE);**

            **}**

        **}**



        **token = strtok(NULL, LSH\_TOK\_DELIM);**

    **}**



    **tokens\[position] = NULL;**



    **return tokens;**

**}**





* **What’s happening?**

&nbsp; - #define LSH\_TOK\_BUFSIZE 64: Sets the list size to hold 64 words.

&nbsp; - #define LSH\_TOK\_DELIM " \\t\\r\\n\\a": Says, “Split the command at spaces, tabs, or Enter.”

&nbsp; - char \*\*tokens = malloc(...): Creates a list to store words (using `<stdlib.h>`).

&nbsp; - token = strtok(line, LSH\_TOK\_DELIM): Chops the first word (from `<string.h>`).

&nbsp; - The `while` loop keeps chopping words until there are none left.

&nbsp; - If the list gets full, it makes it bigger with `realloc`.

&nbsp; - tokens\[position] = NULL: Adds a special mark to say, “This is the end of the list.”

&nbsp; - Returns the list of words (e.g., `\["cd", "folder", NULL]`).





**--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------**



###### **Step 6: Built-In Commands (Like Special Buttons)**



Our shell has three special commands (called **built-ins**) that it knows how to do itself:



\- **cd**: Changes the folder you’re in.

\- **help:** Shows a list of commands.

\- **exit**: Turns off the shell.



We define these commands in a list so the shell knows they’re special:



**char \*builtin\_str\[] = {**

    **"cd",** 

    **"help",** 

    **"exit"**

**};**



**int (\*builtin\_func\[])(char \*\*) = {**

    **\&lsh\_cd,** 

    **\&lsh\_help,** 

    **\&lsh\_exit**

**};**



**int lsh\_num\_builtins()**

**{**

    **return sizeof(builtin\_str) / sizeof(char \*);**

**}**





* **What’s happening?**

&nbsp; - builtin\_str\[]: A list of command names (like a menu).

&nbsp; - builtin\_func\[]: A list of workers (functions) that handle each command.

&nbsp; - lsh\_num\_builtins(): Counts how many built-in commands we have (3 in this case).



Now, let’s look at each built-in function:



**>> 6.1: cd Command (lsh\_cd()):**



The **cd** command changes the folder you’re in, like moving to a different room. Here’s the code:



**int lsh\_cd(char \*\*args)**

**{**

    **if (args\[1] == NULL)**

        **fprintf(stderr, "lsh: expected argument to \\"cd\\"\\n");**

    **else**

    **{**

        **if (!SetCurrentDirectory(args\[1]))**

            **fprintf(stderr, "lsh: cd failed (%lu)\\n", GetLastError());**

        **else**

        **{**

            **char cwd\[512];**

            **GetCurrentDirectory(sizeof(cwd), cwd);**

            **printf("Now in: %s\\n", cwd);**

        **}**

    **}**



    **return 1;**

**}**





* **What’s happening?**

&nbsp; - args is the list of words (e.g., `\["cd", "folder", NULL]`).

&nbsp; - If `args\[1]` is `NULL` (no folder name), it says, “You forgot to tell me which folder!”

&nbsp; - SetCurrentDirectory(args\[1]): Tries to change to the folder (using `<windows.h>`).

&nbsp; - If it fails, it prints an error with `GetLastError()` (a Windows tool to explain what went wrong).

&nbsp; - If it works, `GetCurrentDirectory` gets the new folder’s name and prints it.

&nbsp; - Returns `1` to keep the shell running.





**>> 6.2: help Command (lsh\_help()):**



The **help** command is like a guidebook that lists what the shell can do:



**int lsh\_help(char \*\*args)**

**{**

    **printf("Built in commands: \\n");**

    **printf("  cd <dir>\\n");**

    **printf("  help\\n");**

    **printf("  exit\\n");**



    **return 1;**

**}**





* **What’s happening?**

&nbsp; - Prints a list of commands you can use.

&nbsp; - Returns `1` to keep the shell running.





**>> 6.3: exit Command (lsh\_exit()):**



The **exit** command turns off the shell:



**int lsh\_exit(char \*\*args)**

**{**

    **printf("Exiting shell.....");**

    **return 0;**

**}**





* **What’s happening?**

&nbsp; - Prints “Exiting shell.....”.

&nbsp; - Returns `0` to stop the `lsh\_loop` (because `while (status)` stops when `status` is 0).





**--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------**



###### **Step 7: Running Other Programs (lsh\_launch())**



If you type a command that’s not a built-in (like “notepad” to open Notepad), the **lsh\_launch** function runs it. It’s like sending a mini-robot to do a task. Here’s the code:



**int lsh\_launch(char \*\*args)**

**{**

    **char cmdLine\[512] = "";**



    **int i;**

    **for (i = 0; args\[i] != NULL; i++)**

    **{**

        **if (i > 0)**

            **strcat(cmdLine, " ");**

        **if (strchr(args\[i], ' '))**

        **{**

            **strcat(cmdLine, "\\"");**

            **strcat(cmdLine, args\[i]);**

            **strcat(cmdLine, "\\"");**

        **}**

        **else**

            **strcat(cmdLine, args\[i]);**

    **}**



    **STARTUPINFO si = { sizeof(si) };**

    **PROCESS\_INFORMATION pi;**



    **BOOL success = CreateProcess(**

        **NULL,**

        **cmdLine,**

        **NULL, NULL,**

        **FALSE,**

        **0,**

        **NULL,**

        **NULL,**

        **\&si,**

        **\&pi**

    **);**



    **if (!success)**

        **fprintf(stderr, "lsh: CreateProcess failed (%lu)\\n", GetLastError());**

    **else**

    **{**

        **WaitForSingleObject(pi.hProcess, INFINITE);**

        **CloseHandle(pi.hProcess);**

        **CloseHandle(pi.hThread);**

    **}**



    **return 1;**

**}**





* **What’s happening?**

&nbsp; - cmdLine: A string that combines all words (e.g., `\["notepad", "file.txt"]` becomes `"notepad file.txt"`).

&nbsp; - If a word has a space (e.g., “My File.txt”), it adds quotes (e.g., `"My File.txt"`).

&nbsp; - CreateProcess: A Windows tool (from `<windows.h>`) that starts the program.

&nbsp; - WaitForSingleObject: Waits for the program to finish before the shell asks for another command.

&nbsp; - CloseHandle: Cleans up after the program finishes.

&nbsp; - Returns `1` to keep the shell running.





**--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------**



###### **Step 8: Deciding What to Do (lsh\_execute())**



The **lsh\_execute** function is like a traffic cop—it looks at your command and decides what to do:



**int lsh\_execute(char \*\*args)**

**{**

    **if (args\[0] == NULL)**

        **return 1;**



    **if (strcmp(args\[0], "cd") == 0)**

        **return lsh\_cd(args);**

    **else if (strcmp(args\[0], "help") == 0)**

        **return lsh\_help(args);**

    **else if (strcmp(args\[0], "exit") == 0)**

        **return lsh\_exit(args);**

    **else**

        **return lsh\_launch(args);**

**}**





* **What’s happening?**

&nbsp; - If `args\[0]` is `NULL` (you pressed Enter without typing anything), it does nothing and returns `1`.

&nbsp; - `strcmp` (from `<string.h>`) checks if the first word is “cd”, “help”, or “exit”.

&nbsp; - If it’s a built-in command, it calls the right function (`lsh\_cd`, `lsh\_help`, or `lsh\_exit`).

&nbsp; - If it’s not a built-in, it calls `lsh\_launch` to run the program.





**--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------**



###### **Step 9: Putting It All Together**



Here’s how the shell works when you run it:



1\. The `main` function prints a welcome message and starts `lsh\_loop`.

2\. `lsh\_loop` shows “\&gt; ” and waits for you to type a command.

3\. `lsh\_read\_line` reads your command (e.g., “cd folder”).

4\. `lsh\_split\_line` splits it into words (e.g., `\["cd", "folder", NULL]`).

5\. `lsh\_execute` checks if it’s a built-in command:

&nbsp;  - If it’s “cd”, “help”, or “exit”, it runs the right built-in function.

&nbsp;  - Otherwise, it runs `lsh\_launch` to start a program.

6\. The loop repeats until you type “exit” (which returns 0).





**--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------**



###### **Step 10: What’s Next?**



Congratulations! You’ve built a basic shell! You can make it even cooler by adding features like pipelines, history tracking, etc. 



This shell is like a toy spaceship—simple but awesome. Keep experimenting, and soon you’ll be building a giant starship!
















