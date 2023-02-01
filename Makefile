all:
	gcc main.c -lm

debug:
	gcc -g main.c -lm

clean:
	rm a.out