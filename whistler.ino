
// ------------
// Whistler
// ------------



int whistleCB(String command);

// First, we're going to make some variables.
// This is our "shorthand" that we'll use throughout the program:

int led1 = D3; // Red LED

int led2 = D7; // Built in Blue LED

int mic = A4; // Microphone

int activeNoiseLevel; // Store latest loudness level

int triggerNoiseLvl; // Level at which we send the trigger.


void setup() {

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(mic, INPUT);

  Serial.begin(9600);



  Particle.function("whistle", whistleCB);

	digitalWrite(led1,HIGH);
	digitalWrite(led2,HIGH);
	delay(5000);
	digitalWrite(led1,LOW);
	digitalWrite(led2,LOW);
}

// Next we have the loop function, the other essential part of a microcontroller program.
// This routine gets repeated over and over, as quickly as possible and as many times as possible, after the setup function is called.
// Note: Code that blocks for too long (like more than 5 seconds), can make weird things happen (like dropping the network connection).  The built-in delay function shown below safely interleaves required background activity, so arbitrarily long delays can safely be done if you need them.

void loop() {
  digitalWrite(led2,HIGH);
  delay(1000);
  digitalWrite(led2,LOW);
  delay(1000);


  activeNoiseLevel = analogRead(mic);
  analogWrite(led1, activeNoiseLevel/16);

  char line[32]; /* At least big enough for 31 chars + null. */
  sprintf(line, "Vol - %d; Pin - %d\n", activeNoiseLevel, activeNoiseLevel/16);
  Serial.print(line);

  delay(10);

}

// this function automagically gets called upon a matching POST request
int whistleCB(String command)
{
  // look for the matching argument "coffee" <-- max of 64 characters long
  if (command == "whistle")
    {
	  	Particle.publish("soundDetected", "calm-hobbit", PRIVATE);
			//blinkLed();
      digitalWrite(led1,HIGH);
    	delay(5000);
    	digitalWrite(led1,LOW);
      return 1;
    }
  else return -1;
}
