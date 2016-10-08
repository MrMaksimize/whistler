
// ------------
// Whistler
// ------------

#define N_PIXELS  12
//#define LED_PIN    D7  // NeoPixel LED strand is connected to GPIO #0 / D0
#define DC_OFFSET  0  // DC offset in mic signal - if unusure, leave 0
#define NOISE     100  // Noise/hum/interference in mic signal
#define SAMPLES   60  // Length of buffer for dynamic level adjustment
#define TOP       (N_PIXELS + 1) // Allow dot to go slightly off scale

/*byte
  peak      = 0,      // Used for falling dot
  dotCount  = 0,      // Frame counter for delaying dot-falling speed
  volCount  = 0;      // Frame counter for storing past volume data
*/

int whistleCB(String command);
//void blinkLed();

// First, we're going to make some variables.
// This is our "shorthand" that we'll use throughout the program:

int led1 = D6; // Red LED

int led2 = D7; // Built in Blue LED

//int mic = A4; // Microphone

int
  vol[SAMPLES],       // Collection of prior volume samples
  lvl       = 10,     // Current "dampened" audio level
  minLvlAvg = 0,      // For dynamic adjustment of graph low & high
  maxLvlAvg = 512;


void setup() {
	//memset(vol, 0, sizeof(vol));

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

	//pinMode(mic, INPUT);

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
	digitalWrite(led1,HIGH);
	digitalWrite(led2,HIGH);
	delay(5000);
	digitalWrite(led1,LOW);
	digitalWrite(led2,LOW);
	//blinkLed();
	//Serial.begin(9600);
  //Serial.println("Hello World!");
	/*uint8_t  i;
  uint16_t minLvl, maxLvl;
  int n, height;
  n = analogRead(mic);                 // Raw reading from mic
  n = abs(n - 512 - DC_OFFSET);            // Center on zero
  n = (n <= NOISE) ? 0 : (n - NOISE);      // Remove noise/hum
  lvl = ((lvl * 7) + n) >> 3;    // "Dampened" reading (else looks twitchy)

	//Serial.println("N " + n);
	Serial.println("lvl " + n);

  // Calculate bar height based on dynamic min/max levels (fixed point):
  height = TOP * (lvl - minLvlAvg) / (long)(maxLvlAvg - minLvlAvg);
	//Serial.println("height " + n);

  if(height < 0L)       height = 0;      // Clip output
  else if(height > TOP) height = TOP;
  if(height > peak)     peak   = height; // Keep 'peak' dot at top

	//analogWrite(ledPin, val/16)

	vol[volCount] = n;                      // Save sample for dynamic leveling
  if(++volCount >= SAMPLES) volCount = 0; // Advance/rollover sample counter

  // Get volume range of prior frames
  minLvl = maxLvl = vol[0];
  for(i=1; i<SAMPLES; i++) {
    if(vol[i] < minLvl)      minLvl = vol[i];
    else if(vol[i] > maxLvl) maxLvl = vol[i];
  }
  // minLvl and maxLvl indicate the volume range over prior frames, used
  // for vertically scaling the output graph (so it looks interesting
  // regardless of volume level).  If they're too close together though
  // (e.g. at very low volume levels) the graph becomes super coarse
  // and 'jumpy'...so keep some minimum distance between them (this
  // also lets the graph go to zero when no sound is playing):
  if((maxLvl - minLvl) < TOP) maxLvl = minLvl + TOP;
  minLvlAvg = (minLvlAvg * 63 + minLvl) >> 6; // Dampen min/max levels
  maxLvlAvg = (maxLvlAvg * 63 + maxLvl) >> 6; // (fake rolling average)*/
}

// this function automagically gets called upon a matching POST request
int whistleCB(String command)
{
  // look for the matching argument "coffee" <-- max of 64 characters long
  if (command == "whistle")
    {
	  	Particle.publish("soundDetected", "calm-hobbit", PRIVATE);
			//blinkLed();
      return 1;
    }
  else return -1;
}

/*void blinkLed()
{
	digitalWrite(led1,HIGH);
	digitalWrite(led2,HIGH);
	delay(5000);
	digitalWrite(led1,LOW);
	digitalWrite(led2,LOW);
}*/
