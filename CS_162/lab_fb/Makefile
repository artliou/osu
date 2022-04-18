# CS_162

# Lab Fb makefile

sources_test = lib_arg_parse.cpp lib_flip_display.cpp lab_fb_test.cpp Queue.cpp Stack.cpp
sources      = lib_arg_parse.cpp lib_flip_display.cpp lab_fb.cpp calculator.cpp Stack.cpp

all : lab_fb_test lab_fb

lab_fb_test : $(sources_test)

	g++ $(sources_test) -g -std=c++11 -o lab-fb-test
	./lab-fb-test

lab_fb : $(sources)

	g++ $(sources) -g -std=c++11 -o lab-fb

clean :
	rm -f lab-fb-test
	rm -f lab-fb
