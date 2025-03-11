CC = gcc
CFLAGS = -I.
DEPS = headers.h
OBJ = main.o admin.o student.o transactions.o utils.o database.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

library_management_system: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
