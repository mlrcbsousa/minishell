#!/bin/bash

echo "Error output tests."
./minishell

echo "Tests."
./minishell

# echo "Leaks."
# valgrind --tool=memcheck --leak-check=yes --show-reachable=yes \
# 					--num-callers=20 --track-fds=yes ./minishell
