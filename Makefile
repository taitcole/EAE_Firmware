CC = gcc
CFLAGS = -g -Wall -Wextra

TARGET = plcController.exe

SRCS = plcController.c tempSensor.c statistics.c fan.c pump.c
OBJS = $(SRCS:.c=.o) 

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

run: $(TARGET)
	./$(TARGET)