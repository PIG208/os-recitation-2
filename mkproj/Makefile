# Makefile

U = utils

FLAGS = -Wall

# Define rules
# for each rule, you can have targets and prerequisites
hello: hello.c $U/add.h $U/add.c
	# The recipe tells make how to create the target
	gcc hello.c $U/add.c $(FLAGS) -o hello

clean:
	rm -f hello

