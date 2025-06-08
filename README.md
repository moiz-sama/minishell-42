# minishell-42
As beautiful as a shells.
# 🧠 Overview
Minishell is a simplified Unix shell implemented in C. It replicates many basic features of bash, helping to understand how shells work under the hood — including process management, file descriptors, signals, and parsing.
# 🚀 Features
✅ Mandatory
Display prompt and wait for user commands.
Maintain a working command history.
Locate and launch executables via PATH or with relative/absolute paths.
Handle:
Quoting with ' and " (including $ expansion rules).
Environment variable expansion (e.g., $HOME, $?).
Redirections: <, >, <<, >>
Pipes: | chaining multiple commands.
Built-in commands:
echo, cd, pwd, export, unset, env, exit
Signal handling:
ctrl-C, ctrl-D, ctrl-\ behave like in bash.
# 🧰 Allowed Functions
Includes functions such as readline, fork, execve, pipe, dup2, wait, signal, getenv, tcsetattr, and many more.
# 🧪 Requirements
No memory leaks (except those from readline, which are tolerated).
Norm-compliant code.
Proper use of Makefile with rules: all, clean, fclean, re, bonus
# ⚙️ Compilation
make
./minishell
# 📝 Note
This project was part of the 42 curriculum and follows strict constraints for educational purposes. It is a learning tool, not a production-ready shell.
