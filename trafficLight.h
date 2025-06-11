/* trafficLights.h - header file for the class trafficLights 
	This class simulates a traffic light, with controls for its state (red, yellow, green), 
	delay time for transitions, and collaboration with another TrafficLight object. 
*/

#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "time.h"
#include <iostream>

using namespace std;

/*********************** Class TrafficLight ***************************/
/** 
 * @class TrafficLight
 * 
 * This class represents a traffic light with states (red, yellow, green) and delay times. It provides
 * functionality for managing the light's behaviour, synchronises with other traffic lights and interacts with
 * the global time system.
*/

class TrafficLight {

	public:

	/**
	 * This constructor is for a TrafficLight with no collaborator light.
	 *
	 * This constructor initialises the traffic light with a given delay time for 
	 * transitions and a name. It is public because it needs to be called when creating a
	 * new TrafficLight object.
	 * 
	 * @param delay - delay time for transitions between states (red, yellow, green).
	 * @param light - name of the traffic light.
	 */

		TrafficLight(Time delay, char* light);


	/**
	 * This constructor is for a TrafficLight with a collaborator light.
	 * 
	 * This constructor initialises the traffic light with a given delay time, a name,
	 * and a reference to a collaborator light. This allows the two lights to work together to
	 * synchronise their state transitions. It is public because it needs to be called when 
	 * creating a new TrafficLight object that has a collaborator.
	 * 
	 * @param delay - delay time for transitions between states (red, yellow, green).
	 * @param light - name of the traffic light.
	 * @param collab_light - reference to the collaborator light.
	*/

		TrafficLight(Time delay, char* light, TrafficLight& collab_light); 


	/**
	 * This method handles the logic for when a car wants to cross the light.
	 * 
	 * It is public because it needs to be called when a car needs to request permission to cross.
	 * Depending on the current colour of the traffic light, the method determines whether the car can
	 * proceed or if it must wait for the light's state to change. This method performs the following:
	 * 		- If the light is red, it checks the state of the collaborator light:
	 * 			- If the collaborator light is green, it requests the collaborator light to turn red.
	 * 			- If the collaborator light is also red, the method transitions the light from red to 
	 * 			  yellow, then from yellow to green, updating the global time and outputting the state 
	 * 			  changes. 
	 * 		- If the light is yellow or green, no changes are made and the car must wait until the light
	 * 		  changes. 
	 * 
	 * This method ensures synchronisation with the collaborator light if present, and updating their states 
	 * to ensure coordinated flow of traffic. 
	*/

		void carWantsToCross();


	/** 
	 * This method sets the global time to a specific time for the TrafficLight system. 
	 * 
	 * It is public because it allows external classes to synchronise the traffic light system with a
	 * central time. The method ensures that the time is properly synchronised across all instances.
	 * 
	 * @param new_time - the new global time, which is passed as a constant reference to avoid unnecessary 
	 * 					 copying and to ensure the time is not modified. 
	*/

		static void setTheTime(const Time& new_time);


	/** 
	 * Overloads the output operator (<<) to output the TrafficLight's name. 
	 * 
	 * It is declared as a friend of the TrafficLight class because it needs direct access to the private
	 * memebrs of the TrafficLight class (e.g., the name of the traffic light) for printing to an output stream. 
	 * The operator is a friend so that it can access these private members without being a member function of the class. 
	 *
	 * @param stream - the output stream to which the traffic light will be written.
	 * @param light - a pointer to the TrafficLight object whose name will be displayed. 
	 * @return - the updated output stream.
	*/

		friend std::ostream& operator << (std::ostream& stream, TrafficLight* light);

		
	private:

		enum colour_of_light { red, yellow, green }; // Enum to represent the traffic light's current state.
		Time delay_time; // Delay time for the traffic light.
		char* light; // Name of the traffic light.
		colour_of_light current_colour; // Current state of the traffic light.
		TrafficLight* collaborator_light; // Pointer to the collaborating traffic light.
		static Time global_time; // Static global clock shared across all TrafficLight objects.

	/**
	 * This method handles the logic for requesting the light to turn red. It is private to ensure that
	 * changes to the light's state are controlled and should not be modified directly by external classes. 
	 * It should only be called within the TrafficLight class or by specific public methods, such as carWantsToCross(),
	 * that appropriately manage the state change in a controlled way.
	*/

		void request_to_turn_red();

	
	/** 
	 * This method handles the logic for requesting the light to turn green. It is private to ensure that
	 * changes to the light's state are controlled and should not be modified directly by external classes. 
	 * It should only be called within the TrafficLight class or by specific public methods, such as carWantsToCross(),
	 * that appropriately manage the state change in a controlled way.
	*/

		void request_to_turn_green();
	

};

#endif