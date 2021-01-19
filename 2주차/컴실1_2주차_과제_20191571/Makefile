cc=gcc
cflags = -W -g
target = starwars

objects = main.o a.o b.o

$(target) : $(objects)
	$(cc) $(cflags) -o $(target) $(objects)


%.o : %.c
	$(cc) $(cflags) -c -o $@ $<

main.o string_manipulation.o output.o : header.h

.PHONY : clean
clean :
	rm $(target) $(objects)
