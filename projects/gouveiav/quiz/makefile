CFLAGS = -Wall -fprofile-arcs -ftest-coverage -fpic -coverage -lm -std=c99

default: randomQuiz

randomQuiz:
	gcc -g -o randomQuiz testme.c $(CFLAGS)
	randomQuiz
clean:
	rm randomQuiz

cleanall:
	rm randomQuiz
	rm testme.gcda
	rm testme.gcno