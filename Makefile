CC 			= gcc
CFLAGS 	= -Wall -Wextra
SO			=	libardiop.so
IOP 		= src/ardiop.o
HDR			=	src/ardiop.h
OBJ 		= src/ardiop.o src/main.o

.DEFAULT: shared

src/%.o: src/%.c
	$(CC) $(CFLAGS) $< -c -fPIC -o $@

libardiop.so: $(IOP)
	$(CC) $(CFLAGS) $(IOP) -o $(SO) -shared

shared: $(SO)

install: libardiop.so src/ardiop.h
	cp $(SO) /usr/lib/.
	cp $(HDR) /usr/include/.

uninstall:
	rm /usr/lib/$(SO)
	rm /usr/include/$(HDR)

serlist: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@
