# Small shell for Linux

Program is implemented in C programming language, compile is done with GCC.

#### Shell has 13 own programs such as:
- cat - printing file 
- chmod - change permissions for files and directories
- copy - copies empty directory
- list - prints content of file, most of the info about file
- mkd - create emtpy directory
- mkf - create emtpy file
- move - moves directories and files to another location
- rm - deletes file or empty directory
- wc - prints chars/words/lines from file
- ps - prints information about current running processes, such as PID, STATE, TTY and COMMAND
- kill - kills process with SIGTERM signal not SIGKILL, provides an elegance way to kill process/program
- pipe(|) - passing data from one program stdout to a stdin of another program
- head - it prints first 10 lines of file, can be done with pipe


#### Builtin programs/functions of shell:
- exit - exits shell
- echo - prints string or system variable
- pwd - it printsa path of current working directory
- cdir - change path
- history - saves every commands that was passed to shell, history can be seen with up and down arrows
- ph - prints history of commands
- smart completion - auto complete names of directories/files with tab


### Installation

```
~/shell $ make all
~/shell/commands $ make all
~/shell $ ./shell_start
```

For installing Linux shall, it is necessary to start command "make all" from shell directory and also from shell/commands directory. When compiling is done, output file shell_start is created. Command ./shell_start starts the Linux shall. Directory of object files of programs that are used in shell is shell/obj_output


