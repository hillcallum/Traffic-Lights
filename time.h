/* time.h - header file for the class Time 
   This class provides a representation of time in terms of hours, minutes, and
   seconds. It supports addition of time values and ensures we handle the time 
   overflow correctly (e.g, 75 seconds becomes 1 minute and 15 seconds, and 63 minutes
   becomes 1 hour and 3 minutes).
*/

#ifndef TIME_H
#define TIME_H

#include <iostream>

/*********************** Time Class ***************************/

/**  
 * @class Time
 * 
 * This class represents time in the format hours:minutes:seconds.
*/

class Time {

	public:
	/**
	 * This is the default constructor that initialises the time to 0:0:0.
	*/

    	Time();


	/** 
	 * This constructor initialises the time with particular values for hours, 
	 * minutes and seconds. 
	 * 
	 * @param hours - number of hours ('0'-'23').
	 * @param mins - number of minutes ('0'-'59').
	 * @param secs - number of seconds ('0'-'59').
	*/

		Time(int hours, int mins, int secs);


	/** 
	 * 
	 * This method adds another time object to the current time, updating the 
	 * hours, minutes and seconds. We have made it constant to ensure that it 
	 * is not modified. 
	 *
	*/ 	

		void add(const Time& anotherTime);
			/* adds seconds to seconds, minutes to minutes and
			hours to hours, taking into account that 
			a day has 24 hours, an hour has 60 minutes
			and a minute has 60 seconds */


	/**
	 * We are overloading the output operator (<<) to print Time objects in the format:
	 * hours:minutes:seconds
	 * 
	 * This operator is declared as a friend of the class to grant it access to the private
	 * members (e.g., theHour, theMins, theSecs) of the Time object, which are required for the 
	 * output.
	 * 
	 * @param stream - the output stream to which the Time object will be written.
	 * @param t1 - constant reference to the Time object to display, ensuring it is not modified and
     *             saving memory. 
	 * @return - the modified output stream.
	*/

		friend std::ostream& operator << (std::ostream&, const Time&);


	private:

		int theHour; // Stores the hour ('0'-'23')
		int theMins; // Stores the minutes ('0'-'59')
		int theSecs; // Stores the seconds ('0'-'59')	
		
};

#endif