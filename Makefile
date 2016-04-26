all:
	make clean && make server && make client
server:
	gcc server.c server.h -o server
client:
	gcc client.c client.h -o client
sample:
	make sample-client && make sample server
sample-client:
	gcc sample_client.c -o sample_client
sample-server:
	gcc sample_server.c -o sample_server
clean:
	rm server client
