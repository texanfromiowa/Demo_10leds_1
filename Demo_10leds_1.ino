/**************************************************************
  Name      Demo_10leds_1                                
  Author    Bob Powell 
            texanfromiowa@gmail.com
            Copyright (C) 2012-2013, Parallelus Automation, Inc.
          
  Date      Apr 2, 2013    
  Modified  Apr 2, 2013                                
  Version   1.0.0      
  Arduino   1.0.4
  
  Notes     Example using 10 leds directly from Arduino.

            This program is heavily commented to explain a number
            of concepts.  PLEASE READ!!!
            
            At a number of points in the code, you will see variations
            of this:   1<<i   This is bit shifting.  If you want a full
            explanation, go here: http://en.wikipedia.org/wiki/Logical_shift
            The bit shifting is used because of the inherent problems 
            with floating point numbers.  The preferred  method for 
            calculating an exponent would be, for example, to use:
            
            pow(2,3) which would equal 8 (the number 2, cubed (2^3))

            Unfortunately, the function returns a float which may not
            be exactly 8 (ie. 7.998761234).  Using C casting to force an
            integer would set this to a 7, which is unacceptable.  
            Rather than write code to fix this, bit shifting was used, which 
            ALWAYS gives you an integer, which is what we want anyway.
            
            
Legal Stuff:
============

            This program is free software: you can redistribute it and/or modify
            it under the terms of the GNU General Public License as published by
            the Free Software Foundation, either version 3 of the License, or
            at your option, any later version.
	 
            This program is distributed in the hope that it will be useful,
            but WITHOUT ANY WARRANTY; without even the implied warranty of
            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
            GNU General Public License for more details.
	 
            You should have received a copy of the GNU General Public License
            along with this program.  If not, see <http://www.gnu.org/licenses/>.
          
   
   
     
Personal note:
==============

            If you do something interesting with this code, expand it, or just
            have a question, please email me at the address above.  

            I hope you find this example helpful.  Enjoy.

            Bob

****************************************************************/
// THIS VARIABLE CHANGES.
// Set the number of leds your using.
const int NUM_LED = 10;     

// Set variables - Global variables, except for the Arduino
// pins, are CAPITALIZED.  This makes identification of local and 
// global variables easy to understand.

// These variables are too make things a little easier for humans to read.
// The "const" sets the variable so it cannot be changed
// later in the program (ie. make them constants).  The standard
// constants "true" and "false" function just as well as these.
const bool OFF = 0;
const bool ON = 1;


// Set up the array of leds that is used throughout the program
bool LED[NUM_LED];        
int PINS[] = {12,11,10,9,8,7,6,5,4,3};
  

/**************************************************************
Function: setup
Purpose:  set up Arduino
Args:     none
Returns:  nothing
Notes:    This function is required by the Arduino
***************************************************************/
void setup() {

  for(int i = 0; i < NUM_LED; i++){
        pinMode(PINS[i], OUTPUT);
  }
  

  // turn off all the LEDS, just in case
  allOff();
  writeBytes();
 
  // This is needed for the randomLeds() function below and
  // removed if this function is not used.  
  // From http://arduino.cc/en/Reference/random - 
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
  

}  // End of Arduino Setup 



/**************************************************************
Function: loop
Purpose:  loop funtion for Arduino
Args:     none
Returns:  nothing
Notes:    This function is required by the Arduino, and the 
          Arduino will loop through this function indefinately.
***************************************************************/
void loop() {
  
/*****  See detailed descriptions for each funcion below  *****/
  
  // Set a standard delay between each effect
  int loopDelay = 2000;  
  
  // Flash all leds, to let us know its on
  flashAll(500, 2);
  delay(loopDelay);

  // Meter effect
  for(int i = 0; i < 6; i++){
    int randomnum = random(NUM_LED);
    meter(50, randomnum, false);
  }
  delay(loopDelay);
  // Meter effect in reverse
  for(int i = 0; i < 6; i++){
    int randomnum = random(NUM_LED);
    meter(50, randomnum, true);
  }
  delay(loopDelay);
    
  // The Knight Rider effect
  knightRider(50, 5, 3);
  delay(loopDelay);
   
  // Flash odd only, then even only leds
  flashOdd(250, 2);
  flashEven(250, 2);
  delay(loopDelay);
  
  // Marque effect
  marque(150, 10);
  delay(loopDelay);
  
  // criss-cross effect
  crissCross(100, 5);
  delay(loopDelay);
  
  // Randomly turn on and off leds
  // Reminds me of Christmas lights...
  randomLeds(250,50);
  delay(loopDelay);  
  
  // Chase effect
  chase(100, 3, 3, false);
  delay(loopDelay);
  // Chase effect in reverse
  // Note that the only differnce is the "true"
  chase(100, 3, 3, true);
  delay(loopDelay);
 
  //  Flash again
  flashAll(500, 2);
  delay(2000);  
  
  // Count up from a number to another -- in binary!!
  countUp(0, 100, 50, false);
  delay(loopDelay);
  
  // count up again, but in reverse
  countUp(0, 64, 100, true);
  delay(loopDelay);
  
  // count down from a number to another
  countDown(128, 0, 50, true);
  delay(loopDelay);
   
   
  // Flash one last time 
  flashAll(1000, 1);

  setArray(1);
  writeBytes();
  delay(1000);
  allOff();
  writeBytes();
  
  delay(loopDelay);
  delay(loopDelay);

}  // End of Arduino Loop



/**************************************************************
Function: flashAll
Purpose:  Flashes all leds
Args:     int duration - how long an led is on 
          int count - how many times to flash
Returns:  nothing
Notes:    
***************************************************************/
void flashAll(int duration, int count)
{
  for(int i = 0; i < count; i++)
  {
    allOn();  
    writeBytes();  
    delay(duration);
    allOff();
    writeBytes();  
    delay(duration);
  }  
 
}  


/**************************************************************
Function: flashOdd
Purpose:  Flashes odd leds
Args:     int duration - how long an led is on 
          int count - how many times to flash
Returns:  nothing
Notes:    
***************************************************************/
void flashOdd(int duration, int count)
{
  allOff();
  
  for(int i = 0; i < count; i++)
  {
    oddOn();
    writeBytes();  
    delay(duration);
    allOff();
    writeBytes();  
    delay(duration);
  }
}  

/**************************************************************
Function: flashEven
Purpose:  Flashes even leds
Args:     int duration - how long an led is on 
          int count - how many times to flash
Returns:  nothing
Notes:    
***************************************************************/
void flashEven(int duration, int count)
{
  allOff();
  
  for(int i = 0; i < count; i++)
  {
    evenOn();
    writeBytes();  
    delay(duration);
    allOff();
    writeBytes();  
    delay(duration);
  }
}  


/**************************************************************
Function: crissCross
Purpose:  Criss-Cross effect
Args:     int duration - how long an led is on 
          int count - how many times to cycle through effect
Returns:  nothing
Notes:    
***************************************************************/
void crissCross(int duration, int count)
{
  // Clear the array and turns off any leds still on 
  allOff();
  writeBytes();
  
  // Create variables
  int firstled;
  int lastled;
  
  for(int i = 0; i < count; i++)
  {
    for(int j = 0; j < NUM_LED; j++)
    {
      // if its the start of a loop through the leds,
      // reset the variables to their starting position.
      if(j == 0){
        firstled = 0;
        lastled = NUM_LED -1;
      }
      LED[firstled] = ON;
      LED[lastled] = ON;
      writeBytes();
      // Skip the delay if the center leds are crossing
      // or if the leds have reached the ends.
      // This code was changed to be human readable and 
      // is not the most effecient.
      if(lastled == (firstled +1)){}
        // do nothing - skip delay
      else if (lastled == 0){}
        // do nothing - skip delay
      else
        delay(duration);
      // Turn off the last leds we just turned on
      LED[firstled] = OFF;
      LED[lastled] = OFF;
      // increment variables
      firstled++;
      lastled--;
    }
  }
  
  // turn the last leds off
  delay(duration);
  allOff();
  writeBytes();
}


/**************************************************************
Function: randomLeds
Purpose:  Randomly turn on and off leds
Args:     int duration - time between random number generations 
          int count - number of cycles through the loop
Returns:  nothing
Notes:    
***************************************************************/
void randomLeds(int duration, int count)
{
  // Clear the array and turns off any leds still on 
  allOff();
  writeBytes();
  
  // Create variables
  int randomnum;
  
  for(int i = 0; i < count; i++)
  {
    randomnum = random(NUM_LED);
    if(LED[randomnum] == ON)
    {
      LED[randomnum] = OFF;
      writeBytes();
    }
    else
    {
      LED[randomnum] = ON;
      writeBytes();
    }    
    delay(duration);
  }
  
  // Randomly turn off any remaining leds
  while(sumArray(LED) > 0)
  {
    randomnum = random(NUM_LED);
    LED[randomnum] = OFF;
      writeBytes();
    delay(duration);
  } 

  // turn the last leds off
  allOff();
  writeBytes();
}

/**************************************************************
Function: marque
Purpose:  Marque effect
Args:     int duration - how long an led is on 
          int count - how many times to cycle through effect
Returns:  nothing
Notes:    This funtion is flashing the odd leds, then 
          flashing even leds to create the marque effect.         
**************************************************************/
void marque(int duration, int count)
{
  // Clear the array and turns off any leds still on 
  allOff();
  writeBytes();
  
  for(int i = 0; i < count; i++)
  {
    oddOn();
    writeBytes();
    //writeBits(ODDLEDS);
    delay(duration);
    allOff();
    evenOn();
    writeBytes();
//    writeBits(EVENLEDS);
    delay(duration);  
        allOff();

  }
  
  // Turn off when finished
  allOff();
  writeBytes();
}

/**************************************************************
Function: chase
Purpose:  Chase effect
Args:     int duration - how long an led is on 
          int count - how many times to cycle through effect
          int numleds - how many leds are on at a time
          bool reverse - true or false - a value of true
                       - reverses the normal direction
Returns:  nothing
Notes:    
**************************************************************/
void chase(int duration, int count, int numleds, bool reverse)
{
  // Clear the array and turns off any leds still on 
  allOff();
  writeBytes();
  
  duration = duration / numleds;
  int trailingleds = numleds - 1;
  int ledcounter = NUM_LED + trailingleds;
  
  for(int i = 0; i < count; i++)
  {
    for(int j = 0; j < ledcounter; j++)
    {
      LED[j] = ON;
      if (reverse == true)
        writeBytesRev();
      else
        writeBytes();
      delay(duration);
      LED[j + 1] = ON;
      LED[j - trailingleds] = OFF;
    }    
  } 
  
  // turn off the last led
  allOff(); 
  writeBytes();
}

/**************************************************************
Function: meter
Purpose:  Meter effect
Args:     int duration - how long an led is on 
          int num - how many times to cycle through effect
          bool reverse - true or false - a value of true
                       - reverses the normal direction
Returns:  nothing
Notes:    
**************************************************************/
void meter(int duration, int num, bool reverse)
{
  // Clear the array and turns off any leds still on 
  allOff();
  writeBytes();
  
  // if the number is greater than the number of leds, then return
  if(num > NUM_LED)
    return;
    
    
  // turn on the leds  
  for(int i = 0; i < num; i++)
  {
    LED[i] = ON;
    if (reverse == true)
      writeBytesRev();
    else
      writeBytes();
    delay(duration);     
  } 

  // turn off the leds  
  for(int i = num; i > 0; i--)
  {
    LED[i] = OFF;
    if (reverse == true)
      writeBytesRev();
    else
      writeBytes();
    delay(duration);     
  }  
  // turn off the last led
  allOff(); 
  writeBytes();
}

/**************************************************************
Function: knightRider
Purpose:  "Knight Rider" effect from the TV show
Args:     int duration - how long an led is on 
          int count - how many times to cycle through effect
          int numleds - how many leds are on at a time
Returns:  nothing
Notes:    This is not a perfect implementaion of the effect.
          A perfect effect would include a dimming of the 
          trainling leds (using PWM). Its still cool! 
**************************************************************/
void knightRider(int duration, int count, int numleds)
{
  // Clear the array and turns off any leds still on 
  allOff();
  writeBytes();
  
  duration = duration / numleds;
  int trailingleds = numleds - 1;
  int ledcounter = NUM_LED + trailingleds;
  
  for(int i = 0; i < count; i++)
  {
    // cycle through one direction
    for(int j = 0; j < ledcounter -1 ; j++)
    {
      LED[j] = ON;
      writeBytes();
      delay(duration);
      LED[j + 1] = ON;
      LED[j - trailingleds] = OFF;
      writeBytes();
      // Skip the extra delay() commands as the 
      // trailing leds catch up.
      if(j < NUM_LED)
        delay(duration);    
    }
    // cycle back in the oppisite direction
    for(int j = ledcounter; j > -trailingleds; j--)
    {
      LED[j] = ON;
      writeBytes();
      // Skip the initial delay() commands as the 
      // trailing leds start back.
      if(j < NUM_LED -1)
        delay(duration);
      LED[j - 1] = ON;
      LED[j + trailingleds] = OFF;
      writeBytes();
      delay(duration);    
    }
  }
  
 // Turn the last led off 
 allOff(); 
 writeBytes();
}

/**************************************************************
Function: countUp
Purpose:  Count up, in binary, from one number to another
Args:     int duration - how long an led is on 
          int startNum - starting number
          int endNum - ending number
          bool reverse - true or false - a value of true
                       - reverses the normal direction
Returns:  nothing
Notes:    
**************************************************************/
void countUp(int startNum, int endNum, int duration, bool reverse)
{
 // Clear the array and turns off any leds still on 
 allOff(); 
 
 if((endNum <= startNum) || (endNum < 0))
    return;

  for (int numberToDisplay = startNum; numberToDisplay <= endNum; numberToDisplay++) {
  
    setArray(numberToDisplay);
    if(reverse == true){
      writeBytesRev();
    }
    else{
      writeBytes();
    }
    delay(duration);
  }
  
  allOff(); 
  writeBytes();

} 

/**************************************************************
Function: countDown
Purpose:  Count down, in binary, from one number to another
Args:     int duration - how long an led is on 
          int startNum - starting number
          int endNum - ending number
          bool reverse - true or false - a value of true
                       - reverses the normal direction
Returns:  nothing
Notes:    
**************************************************************/
void countDown(int startNum, int endNum, int duration, bool reverse)
{
 // Clear the array and turns off any leds still on 
 allOff(); 

 if(endNum >= startNum)
    return;
    
  for (int numberToDisplay = startNum; numberToDisplay > endNum; numberToDisplay--) {
    setArray(numberToDisplay);

    if(reverse == true)
      writeBytesRev();
    else
      writeBytes();
    
    delay(duration);
  }
  
  // turn off the last led
  allOff(); 
  writeBytes();
}  
 
 
 
/**************************************************************
Function: sumArray
Purpose:  Take a binary representation of the array of ON and OFF
          positions, and generates an integer.
Args:     int array[]
Returns:  integer of the total
Notes:    See comments on bit shifting at the beginning
          of this file.
**************************************************************/  
int sumArray(bool array[])
{
   int total = 0;
   
   for (int i = 0; i < NUM_LED; i++)
   {
     if (array[i] == ON)
	 total = total + (1<<i);
   }
   
   return(total);
}

/**************************************************************
Function: setArray
Purpose:  Sets the primary array to the binary of the number
          given.
Args:     int num - number to put into array
Returns:  nothing
Notes:    See comments on bit shifting at the beginning
          of this file.  Since this is an integer, it must be
          between -32,768 and 32,767, HOWEVER, it should 
          always be a positive number (0 to 32,767).
**************************************************************/  
void setArray(int num)
{
  // Clear the array
  allOff();
  int i = 0;
  bool value;
  
   while (num > 0)
   {
     value = num & 1;
     if(value == true)
       LED[i] = ON;
     else
       LED[i] = OFF;
       
     num >>= 1;
     i++;
   }  
}

/**************************************************************
Function: evenOn
Purpose:  Turns ON even leds
Args:     none
Returns:  none
Notes:    
**************************************************************/  
void evenOn()
{
   for (int i = 1; i < NUM_LED; i += 2)
   {
     LED[i] = ON;
   }
}


/**************************************************************
Function: oddOn
Purpose:  Turns ON even leds
Args:     none
Returns:  none
Notes:    
**************************************************************/  
void oddOn()
{
   for (int i = 0; i < NUM_LED; i += 2)
   {
     LED[i] = ON;
   }
}


/**************************************************************
Function: allOn
Purpose:  Turns ON all leds
Args:     none
Returns:  none
Notes:    
**************************************************************/  
void allOn()
{
   for (int i = 0; i < NUM_LED; i++)
   {
     LED[i] = ON;
   }
}

/**************************************************************
Function: allOff
Purpose:  Turns OFF all leds
Args:     none
Returns:  none
Notes:    
**************************************************************/  
void allOff()
{
   for (int i = 0; i < NUM_LED; i++)
   {
     LED[i] = OFF;
   }
}



/**************************************************************
Function: writeBits
Purpose:  Write the array with Most Significant Bit first (MSFBFIRST)
Args:     none
Returns:  nothing
Notes:    This function is a wrapper function for outBytes()
***************************************************************/
void writeBytes()
{
  outBytes(MSBFIRST);
}


/**************************************************************
Function: writeBytesRev
Purpose:  Write the array with Least Significant Bit first (MSFBFIRST)
Args:     none
Returns:  nothing
Notes:    This function is a wrapper function for outBytes()
***************************************************************/
void writeBytesRev()
{
  outBytes(LSBFIRST);
}

/**************************************************************
Function: outBytes
Purpose:  Send array data to shift register
Args:     int dir - First or Least significant bit first
Returns:  nothing
Notes:    This is where data is actually sent out, but is not 
          intended to be used directly.  writeBytes() and
          writeBytesRev() should be used instead.
***************************************************************/
void outBytes(int dir)
{

  if(dir == MSBFIRST){
    for(int i = 0; i < NUM_LED; i++)
    {
      if(LED[i] == ON){
        digitalWrite(PINS[i], HIGH);
      }
      else{
        digitalWrite(PINS[i], LOW);
      }
    }
  }  
  else{ // (dir == LSBFIRST)
    int j = 0;
    for(int i = NUM_LED -1; i >= 0; i--)
    {
      if(LED[i] == ON)
        digitalWrite(PINS[j], HIGH);
      else
        digitalWrite(PINS[j], LOW);
        
      j++;
    }
  } 
}

//  End of program
