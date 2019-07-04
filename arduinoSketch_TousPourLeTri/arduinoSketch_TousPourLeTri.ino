
// Pin OpenClose Sensor 
#define Pin_OpenClose 2
// Basic LED (Sensor Testimony)
#define SensorView 13
bool openCloseVal;

// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      60

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Ratio goes from 0 to 100
int fillRatio;

// Serial reading
String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // put your setup code here, to run once:
  //start serial connection
  Serial.begin(9600);
  //configure pin 2 as an input and enable the internal pull-up resistor
  pinMode(Pin_OpenClose, INPUT);
  pinMode(SensorView, OUTPUT);

  openCloseVal = digitalRead(Pin_OpenClose);

  // Pixels
  pixels.begin(); // This initializes the NeoPixel library.
  
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  for(int i=0;i<NUMPIXELS;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,150,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
  
  // First ratio is Zero
  fillRatio = 0;
  
}

void loop() {
  
  // --------------------------------------------------------------------------------------
  // READ Open/Close ----------------------------------------------------------------------
  // put your main code here, to run repeatedly:
  //read the pushbutton value into a variable
  bool openCloseValInstant = digitalRead(Pin_OpenClose);
  digitalWrite(13, openCloseValInstant);
  
  if (openCloseVal == LOW && openCloseValInstant == HIGH) {
    // Impulse
    //print out the value of the pushbutton
    Serial.println("+1");
    
  }
  openCloseVal = openCloseValInstant;
  // --------------------------------------------------------------------------------------
  
  // --------------------------------------------------------------------------------------
  // READ SERIAL --------------------------------------------------------------------------
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println("Read : " + inputString);
    fillRatio = inputString.toInt();
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  // --------------------------------------------------------------------------------------
  
  // --------------------------------------------------------------------------------------
  // LEDS DISPLAY SECTION -----------------------------------------------------------------
  int realNumOfPixels = NUMPIXELS * (fillRatio / 100.0f);
  //Serial.println("realNumOfPixels :" + String(realNumOfPixels));

  //First Black
  for(int i=0;i<NUMPIXELS;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  
  // Then color
  for(int i=0;i<realNumOfPixels;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,150,0)); // Moderately bright green color.
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  // --------------------------------------------------------------------------------------

  
  //Serial.println(String(openCloseVal) + ";" + String(openCloseValInstant));
  delay(1);
  
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
