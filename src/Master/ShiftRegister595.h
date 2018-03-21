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
		
	
	Original author: Alexander Brevig (alexanderbrevig@gmail.com) 
		4/13/2009 - First release
		
	Modifications: 
		1/8/2014 - DesignLibre.com
			-Added the code comments.  Fixed some indentation (4 spaces per tab)  
			-Emailed the original author for permission to license under LGPL.
		1/9/2014 - DesignLibre.com
			-Obtained permission from original author to release the library with changes under the 
			GNU Lesser General Public License V3.0.

*/

#ifndef SHIFTREGISTER595_H
#define SHIFTREGISTER595_H

#include <Arduino.h>


class ShiftRegister595 
{
	public:
		ShiftRegister595(byte userLatchPin, byte userClockPin, byte userDataPin);	
		
		virtual void buffer(byte out);
		virtual void write();
		virtual void write(byte out);
			
	private:
		void shiftOut(byte out);
		byte latchPin;
		byte clockPin;
		byte dataPin;
		byte bufferByte;
};

#endif

