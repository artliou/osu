all: lib

lib: libMain.o Album.o Book.o Library.o LibraryItem.o Movie.o Patron.o
	g++ -g libMain.o Album.o Book.o Library.o LibraryItem.o Movie.o Patron.o -o lib

libMain.o: libMain.cpp Library.hpp Patron.hpp Album.hpp Book.hpp Movie.hpp LibraryItem.hpp
	g++ -c libMain.cpp

Album.o: Album.cpp Album.hpp
	g++ -c Album.cpp

Book.o: Book.cpp Book.hpp
	g++ -c Book.cpp

Library.o: Library.cpp Library.hpp
	g++ -c Library.cpp

LibraryItem.o: LibraryItem.cpp LibraryItem.hpp
	g++ -c LibraryItem.cpp

Movie.o: Movie.cpp Movie.hpp
	g++ -c Movie.cpp

Patron.o: Patron.cpp Patron.hpp
	g++ -c Patron.cpp

# Main.o: Main.cpp Library.hpp
# 	g++ -c Main.cpp

clean:
	rm -f *.o