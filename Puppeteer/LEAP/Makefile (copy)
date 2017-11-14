Target = LEAP
Source = prueba.cpp Leap.h LeapUtilGL.h LeapUtilGL.cpp sockets.cpp Sockets.h libLeap.so
CC= g++ -std=c++0x 
LFlags = -lGL -lglut -lGLU -lm -I /home/pabloav/Desktop/Leap/LEAP_dev/Cinder/include/
WFlags = -Wall -g
CFlags = -o

all: $(Target)

$(Target): $(Source)
	$(CC) $(WFlags) $(CFlags) $(Target) $(Source) $(LFlags)
run:
	./$(Target)
clean:
	rm -rf $(Target)
	
# Primero correr el cliente y luego el servidor
