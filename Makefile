OBJS=    main.o
CFLAGS=  -Wfatal-errors
LDFLAGS= $(shell pkg-config --libs SDL_mixer)

all: met
met: $(OBJS)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)
clean:
	$(RM) met $(OBJS) *.o
.PHONY: all clean
