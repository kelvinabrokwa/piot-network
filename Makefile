all:
	gcc server.c -o server
run:
	make all && ./server
clean:
	rm server
