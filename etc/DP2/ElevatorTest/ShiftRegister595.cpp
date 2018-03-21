/*
	DesignLibre ShiftRegister595 Library - www.designlibre.com

	This file is part of the ShiftRegister595 Library, an Arduino library for 
	driving a 74H595 shift register IC.

    ShiftRegister595 Library is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ShiftRegister595 Library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with ShiftRegister595.  If not, see <http://www.gnu.org/licenses/>.
	
	

*/

#include "ShiftRegister595.h"

ShiftRegister595::ShiftRegister595( byte userLatchPin, byte userClockPin, byte userDataPin )
{
	//Save pins
	latchPin	= userLatchPin;
	clockPin	= userClockPin;
	dataPin	= userDataPin;
	
	
	//Set all pins to output mode
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	pinMode(latchPin, OUTPUT);
	
	//Set all pins low.
	digitalWrite(dataPin, LOW);
	digitalWrite(clockPin, LOW);
	digitalWrite(latchPin, LOW);

	//Set bufferByte to nothing
	bufferByte = 0;
}

void ShiftRegister595::buffer(byte out)
{
	//Record the what to write out
	bufferByte = out;
}

void ShiftRegister595::write()
{
	//Write out what's in the buffer
	write(bufferByte);

}

void ShiftRegister595::write(byte out)
{
	//Write out what was passed in
	
	//The latch pin is used to control the display of what's in the register.  
	//When the latch pin it toggled, the 595 will display the contents
	//of it's storage register
	

	
	//Turn off the latch pin
	digitalWrite(latchPin, LOW);
	
	//Write out the bits to the storage register
	shiftOut(out);   
	
	//Turn on the latch pin which will "display" the contents of the
	//storage register
	digitalWrite(latchPin, HIGH);
	
}

void ShiftRegister595::shiftOut(byte out)
{
	
	bool pinState = false;
	

	for (int i=7; i>=0; i--)  
	{
		//Turn off the clock pin in preparation for 
		//setting the next bit
		digitalWrite(clockPin, LOW);
		
		//out is an 8 bit binary number,  the number 00000001 represented by the byte 1
		// is left shifted by i bits and will act as a mask.  out & 1<<i will return true if bit i 
		// in out is 1.
		if ( out & (1<<i) ) 
		{
			pinState= true;
		}
		else 
		{	
			pinState= false;
		}
		//set the data pin
		digitalWrite(dataPin, pinState);
		//register the new bit and shift
		digitalWrite(clockPin, HIGH);
		//turn off the data pin
		digitalWrite(dataPin, LOW);
	}
	
	//Make sure all pins are low
	digitalWrite(clockPin, LOW);
	digitalWrite(dataPin, LOW);
}
