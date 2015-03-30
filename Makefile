#CC=g++ -std=c++0x
CC=gcc
INCS=Include/
PROJ_INC=Include/
LIBS=
LINKS=-lpthread
#SRCS=$(wildcard Source/*.cpp)
SRCS=$(wildcard Source/*.c)
EXNM=foodPicker

all: compile link
debug: db dblink

compile:
	$(CC) $(SRCS) -I$(INCS) -I$(PROJ_INC) -c

link:
	$(CC) $(SRCS) -I$(INCS) -I$(PROJ_INC) -o $(EXNM) $(LINKS)

db:
	$(CC) -g $(SRCS) -I$(INCS) -I$(PROJ_INC) -c

dblink:
	$(CC) -g $(SRCS) -I$(INCS) -I$(PROJ_INC) -o $(EXNM) $(LINKS)

cleano:
	rm *.o

clean:
	rm *.o $(EXNM)
