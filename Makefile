all:
	gcc main.c -lm -lglut -lGL -lGLU -lm

spheres:
	gcc spheres.c -o spheres -lglut -lGL -lm

debug:
	gcc main.c -lm -lglut -lGL -lGLU -lm -g

clean:
	rm a.out