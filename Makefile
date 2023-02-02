all:
	gcc main.c -lm

spheres:
	gcc spheres.c -o spheres -lglut -lGL -lm

debug:
	gcc -g main.c -lm

clean:
	rm a.out spheres