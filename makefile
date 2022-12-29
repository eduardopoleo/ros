CC = gcc
CFLAGS = -Wall
OBJFILES = file.o interpreter.o main.o parser.o scanner.o token.o
TARGET = ros

all: $(TARGET)

$(TARGET) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~