#!/bin/bash

while true
do
	leaks minishell
	ps aux | grep minishell
	echo "new"
	sleep 2
done