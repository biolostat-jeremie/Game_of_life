WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
            -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
            -Wstrict-prototypes
			#-Wconversion

CFLAGS=-std=c99 $(WARNINGS) -fsanitize=address -Isrc/ 
LDFLAGS=${WARNINGS} -fsanitize=address

RELEASE_FLAGS=-O3
DEBUG_FLAGS=-ggdb -g3 -O0 -fno-inline -fsanitize=address,undefined

SOURCES=
SOURCES+=main.c

OBJECTS  := $(patsubst %.c,build/%.o,$(SOURCES))
DEPFILES := $(patsubst %.o,%.d,$(OBJECTS))

.PHONY: all debug help clean mpropper

all: CFLAGS+=$(RELEASE_FLAGS)
all: LDFLAGS+=-s $(RELEASE_FLAGS)
all: main

-include $(DEPFILES)

debug: CFLAGS+=$(DEBUG_FLAGS)
debug: LDFLAGS+=$(DEBUG_FLAGS)
debug: main

help:
	@echo "   Makefile help"
	@echo "    make             Compiles and links the program (stripped)"
	@echo "    make debug       Compiles and links the program with debugging flags"
	@echo "    make clean       Cleans compilation temporary files (slow down subsequent ones)"
	@echo "    make mpropper    Cleans compilation files and executable"
	@echo "    make help        Displays this help"

main: $(OBJECTS)
	@$(CC) $^ $(LDFLAGS) -o main
	@echo "La compilation a réussie! Le programme s'apelle main, lancez le en terminal avec la commande ./main"

build:
	@mkdir -p build


build/%.o: src/%.c Makefile build
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	-rm -rf build

mpropper: clean
	-rm main
