

.PHONY:all
all:client server

client:client.c
	gcc -o $@ $^
server:server.c
	gcc -o $@ $^

.PHONYY:clean
clean:
	rm -f client server
