all:
	gcc main.c -lm -lglut -lGL -lGLU -lm

spheres:
	gcc spheres.c -o spheres -lglut -lGL -lm

debug:
	gcc -g main.c -lm

clean:
	rm a.out