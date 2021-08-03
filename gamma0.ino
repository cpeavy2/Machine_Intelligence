  This is an example of "Machine Intelligence" as described by David L. Heiserman in his book "How to Build Your Own Self-Programming Robot". According to Heiserman "Alpha" level 
  machine intelligence can be thought of as a basic reflex. In this case the robot's goal is simply to move so it tries random motion patterns until it discovers a motion pattern 
  with displacement... that is it tries random motion patterns until it discovers either forward or backwards. "Beta" class machine intelligence features memory; that is for a given 
  motion pattern when the robot discovers "displacement" it remembers the successful response and uses that response the next time, when in that motion pattern, it encounters a stall 
  condition. It also increments and decrements the confidence level of that response depending on whether or not it continues to be successful. "Gamma" class machine intelligence 
  generalizes this information. That is when the robot encounters a stall condition in a motion pattern for which it has no Beta or memory responses it tries a high-confidence Beta 
  response from another motion pattern before reverting to Alpha level reflex responses. With each sequencial class of machine intelligence, Alpha, Beta and Gamma, the robot learns 
  the motion patterns which maximize displacement sooner and sooner.
  By Camp Peavy
  3/01/15
*/
 
#include <Servo.h>               // Load "Servo" library
 
int mobility_sensor = 2;         // Set "mobility_sensor" for digital pin 2 (The Roomba Caster, er, mobility sensor)
int mobility_read = 0;           // Initialize "mobility_read" value
int mobility_read_past = 0;      // Initialize "mobility_read_past" for comparison to new or current "mobiity_read"; this will determine whether or not the robot is moving
int stall_ticks = 0;             // Initialize "stall_ticks" variable to accumulate changes in value from "0" to "1"; when it stops ticking the robot has stalled
int MotionCode = 0;              // Random number generator creates variable for "Motion_Code"
int PastMotion = 0;              // Past motion pattern
int Confidence = 0;              // Confidence level
int Length = 0;                  // This is an abitrary distance which the robot must travel in order to be considered "success"
int MemArray[9][2] = {           // Memory array to track Motion, Response and Confidence
	{0,0},
	{0,0},
        {0,0},
  	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
    };
 
Servo servoLeft;                 // Left drive servo
Servo servoRight;                // Right drive servo
 
void setup()
{
  servoLeft.attach(3);                  // Set left servo to pin 3
  servoRight.attach(4);                 // Set right servo to pin 4
  pinMode(mobility_sensor, INPUT);      // Sets "mobility_sensor" as input
  randomSeed(analogRead(0));            // Initializes the pseudo-random number
}
 
void loop()
{
  mobility_read = digitalRead(mobility_sensor);         // Read mobility sensor
  if (mobility_read == mobility_read_past) {            // Check to see if mobility_value has changed; that is has the robot "moved"
    stall_ticks = stall_ticks + 1;                      // Accumulate "stall_ticks" readings
    delay (4);                                          // A delay for timing. This is adjustable.
}
    else {
    Length = Length +1;                                   // If the mobility sensor is near the change-point (from black-to-white or visa-versa) it could false trigger...
    if (Length < 4){                                      // This check makes sure the robot goes a mimimum distance before the motion is declared a success... this number is adjustable.
    mobility_read_past = mobility_read;                   // Change mobility reading to past
    loop ();}                                             // Go back to the loop if it hasn't traveled the minimum distance.
    (stall_ticks = 0);                                    // Resets "stall_ticks" in other words... the robot is moving
    MemArray[PastMotion][0] = MotionCode;                 // At this point the motion pattern is successful so associate "PastMotion" with "MotionCode"
                                                          // in other words use this MotionCode when in PastMotion and encounter a stall condition
    MemArray[PastMotion][1] = MemArray[PastMotion][1]+1;  // Increment confidence level
    if (MemArray[PastMotion][1] > 10) {                    // Limit confidence level maximum to 3
    MemArray[PastMotion][1] = 10;
    }      
}
    if (stall_ticks > 100) {                                      // Robot has stalled... this number is adjustable.
    MemArray[PastMotion][1] = MemArray[PastMotion][1]-1;          // Decrement confidence level      * This is where I got into trouble and had to abandon decrementing confidence level
    if (MemArray[PastMotion][1] < 0);                             // Limit Confidence level minimum to 0
    MemArray[PastMotion][1] = 0;
    Motion_Code();                                                // Go to random motion code
    }     else mobility_read_past = mobility_read;                // Change mobility reading to past
}

void Motion_Code()
{
  stall_ticks = 0;                                      // Reset "stall_ticks" for new motion code 
  PastMotion = MotionCode;                              // Change motion code to past
  MotionCode = random(9);                               // Generate new random Motion Code
 
    if (MemArray[MotionCode][1]>=1) {                  // if this motioncode has experienced a successful response (that is MotionCode][1]>=1) then use the previously successful response.
    MotionCode = MemArray[MotionCode][0];              // After the robot stalls this displaces the random Motioncode with the the previously successful response.
    } else Gamma();

 if (MotionCode == 0) {
    Still();
  }
 
 if (MotionCode == 1) {
    LeftForward();
  }

 if (MotionCode == 2) {
    LeftRear();
  }

 if (MotionCode == 3) {
    RightForward();
  }

 if (MotionCode == 4) {
    Forward();
  }

 if (MotionCode == 5) {
    CounterClockwise();
  }

 if (MotionCode == 6) {
    RightRear();
  }

 if (MotionCode == 7) {
    ClockWise();
  }
  
 if (MotionCode == 8) {
    Reverse();
  }
}

void Still()
{
  servoLeft.write(96);
  servoRight.write(94);
  delay(10);
}

void LeftForward()
{
  servoLeft.write(180);
  servoRight.write(94);
  delay(10);
}

void LeftRear()
{
  servoLeft.write(0);
  servoRight.write(94);
  delay(10);
}  

void RightForward()
{
  servoLeft.write(96);
  servoRight.write(0);
  delay(10);
}
 
void Forward()
{
  servoLeft.write(180);
  servoRight.write(0);
  delay(10);
}

void CounterClockwise()
{
  servoLeft.write(0);
  servoRight.write(0);
  delay(10);
}  

void RightRear()
{
  servoLeft.write(96);
  servoRight.write(180);
  delay(10);
}  

void ClockWise()
{
  servoLeft.write(180);
  servoRight.write(180);
  delay(10);
}  

void Reverse()
{
  servoLeft.write(0);
  servoRight.write(180);
  delay(10);
}

void Gamma()
{                                                       // This is the Gamma routine where the robot is checking all the confidence levels to see if any are over 3
                                                      // if so try this pattern before reverting to Alpha
                                                      // check each "MemArray[9][2]" to see if any are confidence level 3
     if (MemArray[0][1]>=3) {                         // if this motioncode has experienced a successful response (that is MotionCode][1]>=1) then use the previously successful response.
     MotionCode = MemArray[MotionCode][0];            // After the robot stalls this displaces the random Motioncode with the the previously successful response.
     loop();
     }                                                // if this motioncode has experienced a successful response (that is MotionCode][1]>=1) then use the previously successful response.
     if (MemArray[1][1]>=3) {                         // if so try it before reverting to Alpha
     MotionCode = MemArray[MotionCode][0];    
     loop();
     }
     if (MemArray[2][1]>=3) {                 
     MotionCode = MemArray[MotionCode][0];
     loop();
     }
     if (MemArray[3][1]>=3) {                 
     MotionCode = MemArray[MotionCode][0];
     loop();
     }
     if (MemArray[4][1]>=3) {                 
     MotionCode = MemArray[MotionCode][0];
     loop();
     }
     if (MemArray[5][1]>=3) {                 
     MotionCode = MemArray[MotionCode][0];
     loop();
     }
     if (MemArray[6][1]>=3) {                 
     MotionCode = MemArray[MotionCode][0];
     loop();
     }
     if (MemArray[7][1]>=3) {                 
     MotionCode = MemArray[MotionCode][0];
     loop();
     }
     if (MemArray[8][1]>=3) {                 
     MotionCode = MemArray[MotionCode][0];
     loop();
     }
}
