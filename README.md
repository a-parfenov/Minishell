# Minishell
School 42 project. Implementation of a simple shell <minishell>.

## Features

* Builtins : ``` echo cd pwd env export unset exit ```
* Redirections : ``` cat < in >> out ```
* Pipes
* Simple and double quotes
* Backslash
* Environment variables : ``` echo $PATH ```
* Search in PATH for binaries
* Signals: `Ctrl-C`, `Ctrl-\`, `Ctrl-D`

## Ressources

For a small documentation of our minishell, please refer to the wiki .

* https://brennan.io/2015/01/16/write-a-shell-in-c/
* https://stackoverflow.com/questions/8082932/connecting-n-commands-with-pipes-in-a-shell
* man ``` write, open, read, close, fork, wait, waitpid, wait3, wait4, signal, kill, exit, getcwd, chdir, stat, lstat, fstat, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, errno ```
