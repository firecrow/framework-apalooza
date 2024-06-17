CC = /usr/bin/clang 
CFLAGS = --target=x86_64-unknown-linux-musl -g -Werror
INC = -I/usr/local/musl/include/ -I./ 

obj = filedb.o mem.o string.o error.o

all: filedb

clean:
	rm -Rf build/*

libbasic.a: 
	cd /mnt/basic/basictypes && make

filedb: dirs $(obj)
	$(CC) $(CFLAGS) $(INC) $(LIBS) -o build/filedb main.c $(addprefix build/, $(obj))

dirs:
	mkdir -p build

$(obj): %.o:%.c 
	$(CC) -c $(CFLAGS) $(INC) $< -o build/$@
