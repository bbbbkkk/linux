dy_lib=libmethod.so
static_lib=libmymath.a
.PHONY:all
all:$(dy_lib) $(static_lib)

$(static_lib):mymath.o
        ar -rc $@ $^
$(dy_lib):test.o mymath.o
        gcc -shared -o $@ $^
test.o:test.c
        gcc -fPIC -c $^
mymath.o:mymath.c
        gcc -fPIC -c $^
.PHONY:clean
clean:
        rm -rf *.a *.o *.so mylib
.PHONY:output
output:
        mkdir -p mylib/include
        mkdir -p mylib/lib
        cp *.h mylib/include/
        cp *.a mylib/lib
        cp *.so mylib/lib
