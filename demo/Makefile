CC= gcc
CFLAGS= -Wall -Wextra -pedantic
LDFLAGS= -L../ -Wl,-rpath=../ -lSDL3 -lm -lhitbox

EXEC= demo_hitbox
DEMO_SRC= demo.c
LIBSO= ../libhitbox.so

run: $(EXEC)
	@./$(EXEC)

all: $(EXEC)

$(EXEC): $(LIBSO) $(DEMO_SRC)
	$(CC) $(CFLAGS) -o $@ $(DEMO_SRC) $(LDFLAGS)

clean:
	@rm -f $(EXEC)
