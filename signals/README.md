##**Project**'C - Signals'

## Introduction
> This README is for the C - Signals project at Atlas.

### Requirements
- Allowed editors: vi, vim, emacs
- All your files will be compiled on Ubuntu 14.04 LTS
- Your C programs and functions will be compiled with gcc 4.8.4 using the flags -Wall -Werror -Wextra and -pedantic
- A README.md file, at the root of the folder of the project, is mandatory
- All your header files should be include guarded
- Your code should use the Betty style
- You are allowed to have more than 5 functions per file
- The prototypes of all your functions should be included in your header file called signals.h

### Repo Files
| **File** | *__Description__* |
|----------|----------------:|
|signals.h| Header file for all C source code|
|0-handle_signal.c| function that set a handler for the signal SIGINT|
|1-current_handler_signal.c| function that retrieves the current handler of the signal SIGINT|
|2-handle_sigaction.c| function that set a handler for the signal SIGINT|
|3-current_handler_sigaction.c| function that retrieves the current handler of the signal SIGINT|
|4-trace_signal_sender.c| function that defines a handler for the signal SIGQUIT|
|5-signal_describe.c| program that prints a description of a given signal|
|6-suspend.c| program that sets a handler for the signal SIGINT, and exits right after the signal is received and handled|
|7-signal_send.c| program that sends the signal SIGINT to a process, given its PID|
|8-signal_send.sh| sh script that sends the signal SIGQUIT to a process, given its PID|
|9-handle_signal.sh| sh script that set a handler for the signals SIGABRT, SIGIO and SIGTERM|
|10-pid_exist.c| function that tests if a process exists, given its PID|

#### Authors
Logan Savage