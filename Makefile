CC=g++
CFLAGS=-Wall -c -g
DICT_DIR=./dict
LFLAGS=-lcurl -lcurlpp -g -Wall
INST_FILE=/usr/local/bin/dictcc

dict : deen.o desv.o dict_imp.o dictcc.o make_lib
deen.o :
	$(CC) $(CFLAGS) $(DICT_DIR)/deen.cc
desv.o :
	$(CC) $(CFLAGS) $(DICT_DIR)/desv.cc
dict_imp.o :
	$(CC) $(CFLAGS) $(DICT_DIR)/dict_imp.cc
dictcc.o :
	$(CC) $(CFLAGS) dictcc.cc
make_lib :
	$(CC) dictcc.o deen.o desv.o dict_imp.o -o dictcc $(LFLAGS)
install:
	sudo ln -s $(PWD)/dictcc $(INST_FILE)
clean :
	rm *.o
