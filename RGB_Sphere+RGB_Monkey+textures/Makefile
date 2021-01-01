all:	VectorZL.o tp1.o 
	g++  VectorZL.o tp1.o -lfreeimage -o tst

	
main.o	: main.cpp
	g++ -c main.cpp

VectorZL.o	:	VectorZL.cpp VectorZL.h
	g++ -c VectorZL.cpp

tp1.o	: tp1.cpp
	g++ -c tp1.cpp
	
test:
	@./tst
	@xdg-open hello.png
	
clr:
	rm *.o
	rm tst
	rm *.png
	
clean:  
	find . -type f | xargs touch
	rm -rf $(OBJS)
