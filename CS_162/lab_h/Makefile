# CS_162

# Lab G makefile

all : lab_h_file_create lab_h

lab_h_file_create : lib_arg_parse-create.cpp lib_flip_display.cpp fileCreator.cpp fileCreateApp.cpp

	g++ lib_arg_parse-create.cpp lib_flip_display.cpp fileCreator.cpp fileCreateApp.cpp -g -std=c++11 -o lab-h-create

lab_h : lib_arg_parse.cpp lib_flip_display.cpp mergeSortIterative.cpp mergeSortRecursive.cpp lab_h.cpp timer.cpp fileLoader.cpp

	g++ lib_arg_parse.cpp lib_flip_display.cpp mergeSortIterative.cpp mergeSortRecursive.cpp lab_h.cpp timer.cpp fileLoader.cpp -g -std=c++11 -o lab-h

clean :
	rm -f lab-h-create
	rm -f lab-h