TARGET = katzi
GIT_HASH := $(shell git rev-parse --short HEAD)

CC = gcc

SDL3 = E:/SDL3/SDL3-3.4.8/x86_64-w64-mingw32

CFLAGS = -Wall -Wextra -O2 -std=c11 -I$(SDL3)/include
LDFLAGS = -L$(SDL3)/lib
LDLIBS = -lSDL3

ifeq ($(OS),Windows_NT)
CFLAGS += -mwindows
LDFLAGS += -mwindows -lws2_32
endif

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:.c=.o) #./lib/kurl/kurl.o

all: lib $(TARGET)

.PHONY: all clean lib

lib:
	mkdir -p lib
	cd lib && git clone https://github.com/KatziIndustries/kurl.git
	cd lib/kurl && ./lib.sh

$(TARGET): $(OBJS)
	"E:\msys2\mingw64\bin\windres.exe" -O coff app.rc -o app.res
	$(CC) $(OBJS) app.res -o $@ $(LDFLAGS) $(LDLIBS) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	rm -fr lib
	rm -f app.res

