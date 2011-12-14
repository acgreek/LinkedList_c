CC=g++
CXXFLAGS= -g -Wall
LDFLAGS= -lunittest++


test: linkedlist_test.cpp linkedlist.h
	$(CC)  $(CXXFLAGS)  linkedlist_test.cpp -o linkedlist_test $(LDFLAGS)
	./linkedlist_test

clean: 
	rm linkedlist_test
