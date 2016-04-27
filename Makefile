all:
	make sample
sample:
	make sample-client && make sample-server
sample-client:
	gcc sample_client.c client.c error.c -lm -o client
sample-server:
	gcc sample_server.c server.c error.c -lm -o server
clean:
	rm server client
