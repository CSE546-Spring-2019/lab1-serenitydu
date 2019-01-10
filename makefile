all:count

count:count.c
		gcc -g -Wall count.c -o count

clean:
		rm count