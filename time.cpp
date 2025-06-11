#include <iostream>
#include "time.h"

using namespace std;

/**
 *  This is the default constructor that initialises the time to 0:0:0.
*/

Time::Time() : theHour(0), theMins(0), theSecs(0) {}


/** 
 * This constructor initialises the time with particular values for hours, 
 * minutes and seconds. It also ensures values are normalised to their correct 
 * ranges. 
 * 
 * @param hours - number of hours ('0'-'23').
 * @param mins - number of minutes ('0'-'59').
 * @param secs - number of seconds ('0'-'59').
*/

Time::Time(int hours, int mins, int secs) 
{
  theSecs = secs%60; // Normalise the seconds. 
  theMins = mins%60 + secs/60; // Normalise the minutes and add the overflow from seconds.
  theHour = (hours + (mins + secs/60)/60)%24; // Normalise the hours and add the overflow from minutes.
}


/** 
 * 
 * This method adds another time object to the current time, updating the 
 * hours, minutes and seconds. It also ensures values are normalised to their correct 
 * ranges (e.g., minutes are between 0 and 59, hours are between 0 and 23)
 *
 * @param anotherTime - a constant reference to the Time object to add. We have made it
 *                      constant to ensure that it is not modified. 
*/ 

void Time::add(const Time& anotherTime) 
{
  // Add the seconds first and normalise
  theSecs += anotherTime.theSecs;
  theMins += theSecs / 60;
  theSecs %= 60;  

  // Then add the minutes and normalise
  theMins += anotherTime.theMins;
  theHour += theMins / 60;
  theMins %= 60;

  // Then add the hours and normalise
  theHour += anotherTime.theHour;
  theHour %= 24; // To ensure that the hours are within a 24-hour range
}


/**
 *  We are overloading the output operator (<<) to display the time in hours:minutes:seconds format.
 * 
 * @param stream - the output stream to which the Time object will be written.
 * @param t1 - constant reference to the Time object to display, ensuring it is not modified and
 *             saving memory. 
 * @return - the updated output stream. 
*/

ostream& operator << (ostream& stream, const Time& t1) 
{
  stream << t1.theHour << ":" << t1.theMins << ":" << t1.theSecs;
  return stream;
}