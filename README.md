# Minishell

As beautiful as a shell.
Creating our own little bash.
Through the Minishell project, you will get to the core of the Unix system and explore an important part of this system’s API: process creation and synchronisation. Executing a command inside a shell implies creating a new process, which execution and final state will be monitored by its parent’s process. This set of functions will be the key to success for your Minishell.

## Usage
- git clone the repository
- `cd` into directory and run `make`
```bash
./minishell
```
## Main project instructions
- The project must be written in accordance with the Norm. `(42Norm)`
- No Segmentation fault, bus error, double free, Leaks, etc.
- Show a prompt when waiting for a new command.
- Search and launch the right executable (based on the PATH  variable or by using relative or absolute path) like in bash.
- It must implement the builtins like in bash:
  - `echo` with option ’-n’.
  - `cd` with only a relative or absolute path.
  - `pwd` without any options.
  - `export` without any options.
  - `unset` without any options.
  - `env` without any options and any arguments.
  - `exit` without any options
-  `;` in the command should separate commands like in bash.
- `’` and `"` should work like in bash except for multiline commands.
- Redirections `< > “>>”` should work like in bash except for file descriptor aggregation.
- Pipes `|` should work like in bash except for multiline commands.
- Environment variables (`$` followed by characters) should work like in bash.
- `$?` should work like in bash.
- `ctrl-C`, `ctrl-D` and `ctrl-\` should have the same result as in bash.
- Use up and down arrows to navigate through the command history.

## Example
![alt text](https://github.com/Conanyedo/Push_swap/blob/master/Screen1.png?raw=true)
![alt text](https://github.com/Conanyedo/Push_swap/blob/master/Screen2.png?raw=true)