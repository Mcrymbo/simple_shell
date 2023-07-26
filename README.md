
# 0x16C - Simple shell project (hsh)
hsh is a simple based command interpreter based on UNIX operating system
The interpreter works in the same manner as bash or Sh

## Execution
**hsh** is command line interpreter that executes command read from from a fstdin or a file.
**hsh** can be invoked by comiling all c files located in this repository. The interpreter can therefore be complied and run using this command.
```
#$. gcc -Wall -Werror -pedantic -Wextra -std=gnu89 -o hsh *.c ; ./hsh
```

**hsh** can be run both interractively and non-interactively. The interractive mode can be accessed by this command on the base directory.
```
#$ ./hsh
$
```

If the interpreter is invoked in this mode, **hsh** takes the first argument of the standard input as a file from which to read commands. If a file is provided instead of std, then the comand can be read directely from the file.
If the the command line arguments are read from the standard input(stdin). only the command is passed as sheon below;
```
#$ ./hsh
```

if the arguments are read from a file, then the file is passed alongside the **hsh** intepreter.
Example
```
#$. echo "echo 'This is read file' " > text
#$. ./hsh text
This is read file
#$.
```
### Signals
While in interractive mode, **hsh** ignores ignores ctrl+c. To exit the program, the program uses End-Of-File (ctrl+d) to exit the program.
```
$. ^d
```

### Exit status
**hsh** returns the exit status of the last command eecuted. 0 status indicates success and non-zeror number indicates failure.
if a command is not found then error status of 127 is returned, and if command found is not executable then error status of 126 is returned. If a system call fails then a status of -1 is returned. This retuen status are captured by error handling mechanism and appropriate error is displayed to the user,

### Environment
When **hsh** is invoked, it copies the environment of the parent process, which is a non-array string which describes variables.
Environment variable can be obtained as shown below;
```
#$. echo "env" | ./hsh
```
Some of the key environment variables include;
#### PATH
Provides a list of comma-separated directories in whcih the shell looks for command. Null directory name indicates current directory.
```
#$. echo "echo $PATH" | ./hsh

/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
```
#### HOME
Home directory indicates the current user and default directory argument

```
#$. echo "echo $HOME" | ./hsh
/home/croco
```
### Execution of command
**hsh** recieves command and tokenize it using `' '` as delimiter. First word is taken as the command and the remaining words are considered as argiments.
if the command does not contain (`/`) or (`.`), then the **hsh** searches for it in the builtins and if found then it is invoked.
If the command does not contain (`/`) or (`.`) and is not among the builtin then **hsh** searches for it in the **PATH** environment variable.
If the command is either (`/`) or (`.`) or the the other searches were successfull then the program is executed together with the remaining arguments.

### Builtins commands
**hsh** executes builtin commands such as cd, exit, env
#### cd - change directory
* Usage: `cd [DIRECTORY]` - changes the directory of a process to `DIRECTORY`
* If no argument is given after directory the it `[DIRECTORY]` is replaced with `$HOME`
* If `cd` is proceeded with `--` as the argument then it is interpreted as `cd $OLDPWD`
* If `cd` is proceeded with `-` is intepreyed as `cd $OLDPWD` and the pathname of the new directory is printed
Example
```
#$. ./hsh
$ pwd
/home/croco/simple_shell
$ cd ..
/home/croco
$ cd -
/home/croco/simple_shell
```
####
exit
* Usage: `exit' [STATUS] - exits the shell
* `[STATUS]` is integer passed as second argument to exit and if not given,
then it is interpreted as `exit 0`
Example
```
$#$. ./hsh
$ exit 98
$#$. echo $?
98
```
#### setenv
* Usage: `setenv `[VARIABLE] [VALUE]` - mofify and existing varible or,
* initializes a new environment variable
* prints an error upon failure
Example
```
$#$. ./hsh
$ setenv NAME 'Hello, world'
$ echo $NAME
Hello, world
```

#### unsetenv
* Usage: `usetenv [VARIABLE]` - removes and environment variable
* Error message is printed to `STDERR_FILENO` upon failure
Example
```
$#$. ./hsh
$ unsetenv NAME

$ echo $NAME

$
```

### Variable Replacement
**hsh** interprets the `$` character for replacment of variable.
```
#$. echo 'echo $?' | ./hsh
0
```
which indicates the return value of the last program executed

### Comments
Allows **hsh** to ignore all characters preceeded by `#` on the command line
Example
```
$ echo 'hshs' # ; ./hsh
hsh
```
### Operators
**hsh** interprets the following characters s operators
#### && - AND logical operator
used to indicate that atleast two or more commands returns exit status of zero
Example
```
#$. echo "echo 'My name is' &&  echo 'MArk'" | ./hsh
'My name i'
'MArk'
```
#### || - OR logical operator
Executes if atleast one of the command returns zero exit status
```
#$. echo "hasbhbaj || echo 'try this'" | ./hsh
./hsh: 1: hasbhbaj: not found
try this
```
#### ; - command separator
executes command separated by `;` sequentially
Example
```
#$. echo "echo 'hello' ; echo 'world'" | ./hsh
'hello'
'world'
```
## More Information
**hsh** is a simple_shell unix command line interpreter which emulates the workings of the **sh** and **bash** shells. It serves as a requirement for the completion of the ALX low-level programming module offered by the program. This README.md file therefore explains the workings of **hsh** provided here and emulates those found on the man pages of **bash**

## Author and Copyright
* Alphonce Mcrymbo <[Mcrymbo] (https://github.com/Mcrymbo)>
