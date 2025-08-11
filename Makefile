CC       :=gcc
AR       :=ar
CFLAGS   :=-Wall -Wextra -O2
PREFIX   :=/usr/local
LIBNAME  :=libnicelibs.a

SRC      :=$(wildcard *.c)
OBJ      :=$(SRC:.c=.o)
HEADERS  :=$(wildcard *.h)

.PHONY: all clean install uninstall

all: $(LIBNAME)

$(LIBNAME): $(OBJ)
	$(AR) rcs $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

install: $(LIBNAME)
	install -Dm644 $(LIBNAME) $(PREFIX)/lib/$(LIBNAME)
	for hdr in $(HEADERS); do \
		install -Dm644 $$hdr $(PREFIX)/include/$$hdr; \
	done

uninstall:
	rm -f $(PREFIX)/lib/$(LIBNAME)
	for hdr in $(HEADERS); do \
		rm -f $(PREFIX)/include/$$hdr; \
	done

clean:
	rm -f $(OBJ) $(LIBNAME)
