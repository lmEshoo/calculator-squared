# Mathematical Association of America Spring 2013 - Calculator^(2) #

Event Info: [http://sections.maa.org/socalnv/Meeting2013Spring](http://sections.maa.org/socalnv/Meeting2013Spring.html)

The premise of Calculator^(2):
Calculator^(2) is a physical calculator. It is, quite literally, a calculator. 
The purpose of  Calculator^(2) was to recreate two widely used trigonometric algorithms, the Taylor Series and CORDIC algorithms, from scratch and test their computing times on a custom-built calculator.  The calculator uses an Arduino microcontroller, an off-the-shelf 4x4 keypad, and a hand-built 2x5 keypad, which all sit in a 3D-printed plastic case.  When collecting the computing times the variables used will be the number of iterations performed by the algorithms, computing time, and precision. Additionally, each algorithm will be tested against the Arduino compiler’s library trigonometric functions. 

Created by:

- Lini Mestar ([https://github.com/lmEshoo](https://github.com/lmEshoo))
- Jacob Getter
- Matt Remick

##Calculator Hardware Contents##

-	One large 16x2 Character Display for showing context-relevant title information
-	4x4 Matrix Membrane Keypad for number inputs
-	10 pushbuttons for selecting to show details of a particular 16x2 LCD
-	An Arduino UNO for all the control and processing

##System Operation Scheme##

1. 	Welcome screen telling hello to user
	- Welcome screen
	- Pierce Math w/ thumbs up & loading bar
	- user options
2.	Wait for user input
3.	Show input, operation, and checks if (=) is been pressed
4.	check if input is correct
5.	Computes the operation w/ proper input
6.	Show results in second line
7.	Wait 3 seconds then clear screen
8.	Show time it took to compute in milliseconds
9.	Wait 3 seconds then clear screen
10.	goes back to step 2

##External Resources for Arduino##

- Liquid Crystal Display Arduino Library: [http://www.arduino.cc/en/Tutorial/LiquidCrystal](http://www.arduino.cc/en/Tutorial/LiquidCrystal)
- Keypad Arduino Library: [http://playground.arduino.cc/code/Keypad](http://playground.arduino.cc/code/Keypad)
- Bounce Arduino Library [http://playground.arduino.cc/code/bounce](http://playground.arduino.cc/code/bounce)