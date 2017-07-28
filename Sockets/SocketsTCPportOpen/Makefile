# ./server <PortToOpen>	-------------- ./server 3000
# ./client <hostIP> <hostPort> ------- ./client 127.0.0.1 3000

all: client_main.cpp server_main.cpp sockets.cpp Sockets.h
	g++ -o server server_main.cpp sockets.cpp Sockets.h
	g++ -o client client_main.cpp sockets.cpp Sockets.h

clean:
	rm -rf server client *.~ *.o
