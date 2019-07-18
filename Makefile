CC 			= gcc
CFLAGS 	= -Wall -Wextra
SO			=	libardiop.so
IOP 		= src/ardiop.o
HDR			=	src/ardiop.h

.DEFAULT: ardiop

src/%.o: src/%.c
	$(CC) $(CFLAGS) $< -c -fPIC -o $@

libardiop.so: $(IOP)
	$(CC) $(CFLAGS) $(IOP) -o $(SO) -shared

install: libardiop.so src/ardiop.h
	cp $(SO) /usr/lib/.
	cp $(HDR) /usr/include/.

uninstall:
	rm /usr/lib/$(SO)
	rm /usr/include/$(HDR)

serlist: src/main.c
	$(CC) $(CFLAGS) $< -o serlist -lardiop
