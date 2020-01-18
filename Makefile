FLAGS = -lGL -lGLU -lglut

reflex_check.out : main.o objekti.o image.o
	gcc -o $@ $^ $(FLAGS)

main.o : main.c
	gcc -o $@ $< -c $(FLAGS)

objekti.o : objekti.c objekti.h
	gcc -o $@ $< -c $(FLAGS)

image.o: image.c
	gcc -o $@ $< -c $(FLAGS)

.PHONY:
	clean

clean:
	rm -rf *.o reflex_check.out
