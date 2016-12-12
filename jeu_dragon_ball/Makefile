dragon: main.o file.o play.o
	gcc -Wall -g main.o file.o play.o `sdl-config --cflags --libs` -o dragon -lm

main.o: main.c
	gcc -c -Wall -g main.c `sdl-config --cflags --libs` -o main.o -lm

file.o: file.c
	gcc -c -Wall -g file.c `sdl-config --cflags --libs` -o file.o -lm

play.o: play.c
	gcc -c -Wall -g play.c `sdl-config --cflags --libs` -o play.o -lm


clean:
	rm *.o
	rm dragon

rebuild: clean dragon


test: dragon
	./dragon
	make clean
	
