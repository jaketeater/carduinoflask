/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN takes care
  of use the correct LED pin whatever is the board used.
  If you want to know what pin the on-board LED is connected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald

  modified 2 Sep 2016
  by Arturo Guadalupi
*/

/*
To make things a little easier, we will give the arduino pins a variable that
matches the direction the pin will send the car.
 */
int F = 9;        // Forward
int B = 10;       // Backward
int L = 11;       // Left
int R = 12;       // Right

/*
This variable will assigned the value of incoming data from the serial connection
 */
int inByte = 0;   // incoming serial byte

// the setup function runs once when you press reset or power the board
void setup() {
  /*
  We want the car to be as responsive as possible, we will set the serial connection
  faster than default.
   */
  Serial.begin(115200);
  Serial.setTimeout(1);

  /*
  All of the pins connected to the car are output pins, since we will write a status
  to them.
   */
  pinMode(F, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(L, OUTPUT);
  pinMode(R, OUTPUT);

  /*
  Write HIGH as the initial status on all pins.  In my case, HIGH meant off, or not 
  connected.  This way the car doesn't start driving around when its powered up.
   */
  digitalWrite(F, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(L, HIGH);
  digitalWrite(R, HIGH);
}

// the loop function runs over and over again forever
void loop() {
  /*
  The first thing in the loop is the check if there is any data waiting in the serial
  buffer.  If there is, read it into the inByte variable.
   */
  if (Serial.available() > 0) {
    inByte = Serial.parseInt();
    
    /*
    Here is the meat of the code.

    For simplicity, I wanted to use a switch to handle the incoming byte. In Arduino, 
    switches only deal with ints.  So I will use ints that correspond with the layout
    of numpad arrows.  8=forward, 6=left, 2=backwards, 4=left.

    Basically, by writing a pin to LOW, that presses the button. But unlike the car's
    remote which has a momentary switch (a switch that is only on as long as you are 
    holding the button down), we don't need to keep 'pressing the button'.  Once the 
    pin has been written to, it will remain in that state until told otherwise.

    Because of this, we need a way to 'unpress the button'.  To do this, I added 2 
    cases to the switch, 5 and 0.  5 writes both forward (pin 9) and backward (pin 10)
    to HIGH. When you depress the button when you have the browser open on your phone,
    it sends a 5 to make the car stop.

    Similarly, when you drive straight, it sends the 0 byte and sets both the left and
    right pins, ensuring that the car will drive straight.

    You will also notice that each case writes to two pins. This is because we need to
    turn off the other pin just in case the user goes directly from left to right, 
    without triggiring the 0 byte (straight).  This avoids sending both the left and
    right signal to car.
    
    */
     
    switch (inByte) {
      case 8:
        digitalWrite(F, LOW);
        digitalWrite(B, HIGH);
        break;
      case 5: // Stop
        digitalWrite(F, HIGH);
        digitalWrite(B, HIGH);
        break;
      case 2:
        digitalWrite(F, HIGH);
        digitalWrite(B, LOW);
        break;
      case 4:
        digitalWrite(L, LOW);
        digitalWrite(R, HIGH);
        break;
      case 0: // Straight
        digitalWrite(L, HIGH);
        digitalWrite(R, HIGH);
        break;
      case 6:
        digitalWrite(L, HIGH);
        digitalWrite(R, LOW);
        break;
    }
  }
}
