LCD Library for an STM32

you import the library to your code.
you do this by pressing right mouse button on your project folder then going to properties ->c/c++ build -> settings -> inlcude paths and add the path to the library folder in there.

you want to include the header file. 
you do this by writing #include "LCD.h" at the top of your main.c file

then in your main function you run the lcdSetup function.
this takes the following arguments lcdSetup(Port for data pins, Port for enable pin , Port for the R ports, RS pin, RW pin , EN pin, D4, D5, D6, D7).

After this you want to run the lcdInit function. 
It makes sure the display is set up correctly and is configured for 4 pin mode.

Now the display is ready to use.

You have the following commands you can use:

lcdChar
lcdString
lcdWriteInt
lcdWriteFloat
lcdSetCursor
lcdCustomCharacter
lcdClear
lcdCursorOFF
lcdCursorON
lcdCursorBlink
lcdCursorHome
lcdShiftRight
lcdShiftLeft
lcdOFF
lcdCursorLeft
lcdCursorRight


I will now quickly explain what all of them do and how to use them.

lcdChar -> This will print out a character on the display. You use it like this: lcdChar('x');
lcdString -> This will print out a string on the display. You use it like this: lcdString('Hello World');
lcdWriteInt -> This will print out an integer on the display. You use it like this: lcdWriteInt("%d",10);
lcdWriteFloat -> This will print out a float on the display. You use it like this: lcdWriteFloat("%f", 7.5);
lcdSetCursor -> This will set the cursor position on the 16 x 2 display. You use it like this: lcdSetCurso(0,0); ( for the the top left).
lcdClear -> This will clear the display. You use it like this: lcdClear();
lcdCursorOFF -> This will turn the cursor off. You use it like this : lcdCursorOFF();
lcdCursorON -> This will turn the cursor on. You use it like this: lcdCursorON();
lcdCursorBlink -> This will make the cursor blink. You use it like this: lcdCursorBlink();
lcdCursorHome -> This will make the cursor go back to the home position. You use it like this: lcdCursorHome();
lcdShiftRight -> This will make the display shift 1 position to the right. You use it like this: lcdShiftRight();
lcsShiftLeft -> This will make the display shift 1 posution to the left. You use it like this: lcsShiftLeft();
lcdOFF -> This will make the display turn off. You use it like this lcdOFF();
lcdCursorLeft -> This will move the cursor 1 spot to the left. You use it like this: lcdCursorLeft();
lcdCursorRight -> This will move the cursor 1 spot to the right. You use it like this: lcdCursorRight();
lcdCustomCharacter -> you can create your own custom character. You use it like this: 
    you want to create a custom character that is made out of hexadecimal values -> you call the function lcdCustomCharacter(0, cc) -> lcdClear to clear the display and make sure its in write mode again->
    you do lcdChar(position) to print it out. 


common errors:

lcdWriteFloat not working : make sure when you go to properties -> c/c++ build -> settings -> that use float with printf from newlib -nano (-u_printf_float) is enabled.
