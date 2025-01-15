# Caleb Iyob, G01257159
# Lab Section 215
# Project 3
#
CFLAGS = -g -Wall -std=c89 -pedantic-errors
CC = gcc
EXE = p3_ciyob_215 # replace username and labsection with your actual info
SOURCE = p3_ciyob_215.c # replace username and labsection with your actual info
OBJ = p3_ciyob_215.o # replace username and labsection with your actual info

all:	$(EXE)

$(EXE):	$(SOURCE) strcmpa.o
	$(CC) -o $@ $^ $(CFLAGS)
$(OBJ):	$(SOURCE)	order.h	list.h	strcmpa.h
	$(CC) -c $<
strcmpa.o:	strcmpa.c strcmpa.h
	$(CC) -c $<
clean:
	rm *.o
	rm $(EXE)
