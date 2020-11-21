enigma: main.o enigma.o component.o plugboard.o reflector.o rotor.o helper.o
	g++ -g main.o enigma.o component.o plugboard.o reflector.o rotor.o  helper.o -o enigma

main.o: main.cpp enigma.h errors.h helper.h
	g++ -Wall -g -c main.cpp

enigma.o: enigma.h component.h plugboard.h reflector.h rotor.h errors.h helper.h
	g++ -Wall -g -c enigma.cpp

component.o: component.cpp component.h errors.h helper.h
	g++ -Wall -g -c component.cpp

plugboard.o: plugboard.cpp plugboard.h component.h errors.h helper.h
	g++ -Wall -g -c plugboard.cpp

reflector.o: reflector.cpp reflector.h component.h errors.h helper.h
	g++ -Wall -g -c reflector.cpp

rotor.o: rotor.cpp rotor.h component.h errors.h helper.h
	g++ -Wall -g -c rotor.cpp

helper.o: helper.cpp helper.h errors.h
	g++ -Wall -g -c helper.cpp

clean:
	rm -f *.o execute
