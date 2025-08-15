all:
	cc -std=c23 src/main.c -Wall -Wextra -g -O0 -o http_server

clean:
	rm -f http_server
	rm -rf http_server.dSYM
