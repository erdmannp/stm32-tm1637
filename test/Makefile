TARGET = main
LIBS = 
CC = gcc
POORTEST = 0
CFLAGS = -g -Wall -I. -I$(CURDIR) -I$(CURDIR)/.. -DPOORTEST=$(POORTEST)

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c)) ../stm32_tm1637.o
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

test:
	$(TARGET)

clean:
	-rm -f *.o
	-rm -f $(TARGET)
