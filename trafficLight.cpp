#include <iostream>
#include "trafficLight.h"

using namespace std;

/**
 * This is the default constructor that initialises the time to 0:0:0.
 * 
 * This constructor sets the initial value of the global_time to 0 hours, 0 minutes, and 0 seconds, 
 * representing the start of the traffic light system. It ensures that the time is synchronised across 
 * all traffic light instances and can be updated globally as needed.
*/

Time TrafficLight::global_time(0, 0, 0);


/**
 * This constructor is for a TrafficLight with no collaborator light.
 * 
 * This constructor initialises the TrafficLight with a specified delay time for state transitions, 
 * a name to identify the light, and sets the initial state of the light to red. Since there is no 
 * collaborating traffic light, the collaborator_light is set to nullptr.
 * 
 * @param delay - delay time for state transitions (red, yellow, green).
 * @param light - name of the traffic light.
*/

TrafficLight::TrafficLight(Time delay, char* light) : delay_time(delay), light(light), current_colour(red), collaborator_light(nullptr) {}


/**
 * This constructor initialises the TrafficLight with a specified delay time for state transitions, 
 * a name to identify the light, sets the initial state of the light to red, and a reference to 
 * another TrafficLight that acts as its collaborator.
 * 
 * The constructor also ensures that the collaborating TrafficLight is aware of this instance by 
 * setting its collaborator_light member to point to the newly created TrafficLight. If the collaborator's 
 * collaborator_light is not set, it updates the collaborator's reference to this TrafficLight, 
 * allowing both traffic lights to be synchronised.
 * 
 * @param delay - delay time for state transitions (red, yellow, green).
 * @param light - name of the traffic light.
 * @param collab_light - the name of the collaborating traffic light.
*/

TrafficLight::TrafficLight(Time delay, char* light, TrafficLight& collab_light) : delay_time(delay), light(light), current_colour(red), collaborator_light(&collab_light) 
{
    if (collab_light.collaborator_light == NULL)
    {
        collab_light.collaborator_light = this;
    }
}

/** 
 * This method simulates a car requesting to cross at the traffic light.
 * 
 * When a car wants to cross:
 *      - If the current light is red and the collaborator light is green, it requests the 
 *        collaborator light to turn red.
 *      - If both the current light and its collaborator are red, the current light transitions to 
 *        yellow, then to green, following the delay time. 
 *      - If the current light is yellow or green, no action is required. 
 * 
 * This method ensures synchronisation between the two traffic lights, allowing one traffic light to 
 * chnage its state in response to the other. 
*/

void TrafficLight::carWantsToCross() 
{
    cout << endl;
    cout << "***  at " << global_time << " a car wants to cross light " << light 
    << ", with colour: "
    << (current_colour == red ? "red" : current_colour == yellow ? "yellow" : "green") 
    << endl;

    switch (current_colour) 
    {
        case red:
            // Check if the collaborator light is green
            if (collaborator_light && collaborator_light->current_colour == green)
            {
                collaborator_light->request_to_turn_red();
            }
            // If the collaborator light is red as well, change this light to yellow and then green
            else if (collaborator_light && collaborator_light->current_colour == red)
            {
                global_time.add(delay_time);
                current_colour = yellow;
                cout << "     at " << global_time << " " << light << " changes colour to yellow" << endl;
                global_time.add(delay_time);
                current_colour = green;
                cout << "     at " << global_time << " " << light << " changes colour to green" << endl;
            }
            break;
        case yellow: // No action for yellow light
            break;
        case green:
            break; // No action for green light
    }
}


/**
 * This method handles a request to turn this traffic light to red. 
 * 
 * It handles the following:
 *      - If the current light is already red, no action is taken.
 *      - If the current light is yellow, it transitions to red and then requests the collaborator
 *        light to turn green following the delay time.
 *      - If the current light is green, it first transitions to yellow and then requests
 *        the collaborator light to turn green following the delay time.
 * 
 * This method ensures that the traffic light and any collaborator lights are synchronised when
 * transitioning between states. 
*/

void TrafficLight::request_to_turn_red() 
{
    switch (current_colour) 
    {
        case red:
            break; // Already red, so no action required
        case yellow:
            // Transition from yellow to red
            global_time.add(delay_time);
            current_colour = red;
            cout << "     at " << global_time << " " << light << " changes colour to red" << endl;
            
            // Notify collaborator light to turn green, if present
            if (collaborator_light) 
            {
                collaborator_light->request_to_turn_green();
            }
            break;
        case green:
            // Transition from green to yellow
            global_time.add(delay_time);
            current_colour = yellow;
            cout << "     at " << global_time << " " << light << " changes colour to yellow" << endl;

            // Notify collabrator light to turn green, if present
            if (collaborator_light) // Check collaborator_light is valid and not a nullptr
            {
                collaborator_light->request_to_turn_green();
            }
            break;
    }
}


/**
 * This method handles a request to turn this traffic light to green. 
 * 
 * It handles the following:
 *      - If the current light is already green, no action is taken.
 *      - If the current light is yellow, it transitions to green following the delay time.
 *      - If the current light is red, it first transitions to yellow and then requests
 *        the collaborator light to turn red following the delay time.
 * 
 * This method ensures that the traffic light and any collaborator lights are synchronised when
 * transitioning between states.  
*/

void TrafficLight::request_to_turn_green() 
{
    switch (current_colour) 
    {
        case green:
            break; // Already green, no action required
        case yellow:
            // Transition from yellow to green
            global_time.add(delay_time);
            current_colour = green;
            cout << "     at " << global_time << " " << light << " changes colour to green" << endl;
            break;
        case red:
            // Transition from red to yellow
            global_time.add(delay_time);
            current_colour = yellow;
            cout << "     at " << global_time << " " << light << " changes colour to yellow" << endl;

            // Notify collaborator light to turn red, if present
            if (collaborator_light) // Check collaborator_light is valid and not a nullptr
            {
                collaborator_light->request_to_turn_red();
            }
            break;
    }
}


/** 
 * This method updates the global time variable with a new Time value. 
 *
 * This method sets the global time used for synchronisation across all traffic light instances 
 * to new_time. The argument is passed as a constant reference to avoid unnecessary 
 * copying and to ensure that the value is not modified within the method.
 * 
 * @param new_time - the new global time to set, passed as a constant reference to avoid 
 *                   unnecessary copying and ensure it remains unchanged during the operation.
*/

void TrafficLight::setTheTime(const Time& new_time) 
{
    global_time = new_time;
}


/** 
 * Overloads the output operator (<<) to display the traffic light's name.
 *
 * This method enables the use of the output stream (<<) to print the name of the 
 * traffic light object. It outputs the light attribute of the TrafficLight
 * class, which represents the name of the traffic light. The traffic light object is passed 
 * as a pointer, and the operator allows convenient printing of the object's name.
 *
 * @param stream - the output stream to which the traffic light's name will be written. 
 * @param light - a pointer to the TrafficLight object whose name is to be outputted.
 * @return - the updated output stream.
*/

ostream& operator << (ostream& stream, TrafficLight* light)
{
    stream << light->light; // Output the name of the traffic light
    return stream;
}