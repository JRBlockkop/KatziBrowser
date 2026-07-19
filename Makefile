TARGET = katzi
GIT_HASH := $(shell git rev-parse --short HEAD)

CC = gcc

#jrb sdl3 lib
SDL3 = E:/SDL3/SDL3-3.4.8/x86_64-w64-mingw32
SDL3TTF = E:/SDL3_ttf/SDL3_ttf-3.2.2/x86_64-w64-mingw32

CFLAGS = -Wall -Wextra -O2 -std=c11
LDFLAGS = 
LDLIBS = -lSDL3 -lSDL3_ttf

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:.c=.o)

ifeq ($(OS),Windows_NT)
CFLAGS += -mwindows -I$(SDL3)/include -I$(SDL3TTF)/include
LDFLAGS += -mwindows -lws2_32 -L$(SDL3)/lib -L$(SDL3TTF)/lib
"E:\msys2\mingw64\bin\windres.exe" -O coff app.rc -o app.res
OBJS += app.res
endif

all: $(TARGET)

.PHONY: all clean

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	rm -fr lib
	rm -f app.res

