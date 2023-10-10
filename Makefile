CC = gcc
C_FLAGS = -Wall

target = bin/isprime
c_srcs = isprime.c
libs = m

objs = $(patsubst %.c,tmp/%.o,$(c_srcs))

ifdef DEBUG
	C_FLAGS += -g
else
	C_FLAGS += -O2
endif


all: mkdir $(target)

$(target): $(objs)
	$(CC) -o $@ $^ $(addprefix -l,$(libs))

$(objs): tmp/%.o: %.c
	$(CC) $(C_FLAGS) -c $^ -o $@

clean:
	-rm -rf tmp
	-rm -rf bin

mkdir:
	-mkdir tmp
	-mkdir bin

.PHONY: all clean mkdir

