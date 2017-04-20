Target = Sample
Source = Sample.cpp

all: $(Target) run clean

$(Target): $(Source)
	g++ -Wall -g $(Source) -o $(Target) Leap.h LeapMath.h libLeap.so 
run:
	./$(Target)
clean:
	rm -rf $(Target)
