TARGET 	= ls
OBJS 	= main.o dir.o ls.o 
CC		= gcc
CFLAGS	= -c

$(TARGET) : $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $<

clean : 
	rm -f $(OBJS) $(TARGET)