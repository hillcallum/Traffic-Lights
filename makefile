traffic: main.o trafficLight.o time.o
	g++ -g -Wall main.o trafficLight.o time.o -o traffic

main.o: main.cpp trafficLight.h time.h
	g++ -g -Wall -c main.cpp

trafficLight.o: trafficLight.cpp trafficLight.h
	g++ -g -Wall -c trafficLight.cpp

time.o: time.cpp time.h
	g++ -g -Wall -c time.cpp

clean:
	rm -f *.o traffic