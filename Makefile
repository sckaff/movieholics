
Movieholics: main.o Movie.o
	g++ main.o Movie.o -o Movieholics.exe

main.o: main.cpp
	g++ -c main.cpp
	
Movie.o: Movie.cpp
	g++ -c Movie.cpp

clean:
	rm *.o Movieholics.exe