# Minishell

**As beautiful as a shell. Creating our own little bash.**

Exploring process creation and synchronisation. Executing a command inside a shell implies creating a new process, which execution and final state will be monitored by its parent’s process.

## Usage

- Git clone the repository
- `cd` into directory and run `make`
```bash
./minishell
```

## Main project instructions

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
- Parsing
  -  `;` in the command should separate commands like in bash.
  - `’` and `"` should work like in bash except for multiline commands.
- Redirection
  - Redirections `< > “>>”` should work like in bash except for file descriptor aggregation.
  - Pipes `|` should work like in bash except for multiline commands.
- Expansion
  - Environment variables (`$` followed by characters) should work like in bash.
  - `$?` should work like in bash.
- Signals
  - `ctrl-C`, `ctrl-D` and `ctrl-\` should have the same result as in bash.
- Termcaps
  - Use up and down arrows to navigate through the command history.
  - Move cursor left and right using arrows.
  - Move to the beginning and end using HOME and END keys.

<!-- ## Example
![alt text](https://github.com/Conanyedo/Push_swap/blob/master/Screen1.png?raw=true)
![alt text](https://github.com/Conanyedo/Push_swap/blob/master/Screen2.png?raw=true) -->
