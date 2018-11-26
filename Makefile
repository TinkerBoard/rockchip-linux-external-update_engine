PROJECT_DIR := $(shell pwd)
CC = gcc
PROM = update_engine
OBJ = log.o \
    partition.o \
    rkimage.o \
    tomcat.o \
    deviceInfo.o \
    kugou.o \
    bootcontrol.o \
    test_kugou.o

CFLAGS += -lcrypto -lssl -fPIC -std=c++11 -lcurl -lpthread

$(PROM): $(OBJ)
	$(CXX) -o $(PROM) $(OBJ) $(CFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf $(OBJ) $(PROM)

install:
	rm -rf ./bin/
	mkdir ./bin/
	cp -rf update.img ./bin/
	sudo install -D -m 755 update_engine -t ./bin/
