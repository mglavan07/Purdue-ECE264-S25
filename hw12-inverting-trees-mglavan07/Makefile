CC = gcc

# compiles to debug
CFLAGS = -g -std=c99 -Wall -Wshadow -Wvla -pedantic

# compiles to release
OFLAGS = -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic

test: 
	$(CC) $(CFLAGS) *.c *.h -o hw12

hw12: 
	$(CC) $(OFLAGS) *.c *.h -o hw12

clean:
	rm -f vgcore.* *.o hw12 *.disc *.txt *.b
