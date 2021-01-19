cc=gcc
cflags = -W -g
target = fmt

objects = main.o String_Manipulation.o Output.o

$(target) : $(objects)
	$(cc) $(cflags) -o $(target) $(objects)


%.o : %.c
	$(cc) $(cflags) -c -o $@ $<

main.o string_manipulation.o output.o : Header.h

.PHONY : clean
clean :
	rm $(target) $(objects)
