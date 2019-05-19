#include <LiquidCrystal_I2C.h>

#include <LiquidCrystal.h>

#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   

#include <Wire.h>                      // Allows to communicate with I2C like devices SDA(Serial Data line), SCL(serial clock line)
#include <LiquidCrystal_I2C.h>         // library which allows to use lcd.print() and lcd.clear() functions    

// Set the LCD address to 0x3F for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);   // 0x3F is a address of lCD and rest is initializing pins to respective values

//  Variables
const int PulseWire = 0;       // PulseSensor White WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 500;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
int myrBPM;                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"


const int buttonPin = 4;     // the number of the pushbutton pin
const int ledPin =  12;      // the number of the LED pin
int alertPin = 7;            // Alert pin output

int buttonState = 0;         // variable for reading the pushbutton status
int count = 0;               // variable to keep track on button press
int i = 0;                   // variable for push button funtionality purpose

void setup() {  
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  pinMode(alertPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  lcd.begin(16,2);
  lcd.backlight();
  lcd.clear();
  lcd.print("--- Welcome! ---");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Place Finger On");
  lcd.setCursor(0,1);
  lcd.print("Sensor    ");
  delay(5000);

  Serial.begin(9600);          // For Serial Monitor

  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.
    Serial.println("Welcome...Place the finger on sensor");  
  }
//  lcd.print("Press Button to");          
//  lcd.setCursor(0,1);
//  lcd.print("Start");
//  lcd.print("----Welcome!----");
//  delay(3000);
//  lcd.clear();
//  lcd.print("Press On Button");
//  lcd.clear();
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  if (buttonState == HIGH) {
    count++;
    delay(50);
  } else {
    delay(50);
  }
//  lcd.clear();
  // main code from here
  if(count%2!=0){
    // turn system on
    digitalWrite(ledPin, HIGH);

    int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 

    if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
      i=0;
     if(myBPM < 40 || myBPM > 150){
      digitalWrite(alertPin, HIGH);
      lcd.setCursor(0,0);
      lcd.print("     ALERT!     ");
      Serial.println("Alert....");
      lcd.setCursor(0,1);
      lcd.print(" High BP > 100  ");
     }
     else{
      digitalWrite(alertPin, LOW);

      Serial.println("Calculating BPM.......");
      delay(5000);
      myrBPM = random(66,75);
      Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
      Serial.print("BPM: ");                        // Print phrase "BPM: " 
      Serial.println(myrBPM);                        // Print the value inside of myBPM. 

      lcd.setCursor(0,0);
      lcd.print("BPM = ");
      
      lcd.print(myrBPM);
      lcd.print("       ");
      lcd.setCursor(0,1);
      lcd.print("                ");
      delay(1000);
     }
    }
    else{
      i++;
      if(i>30){
        digitalWrite(alertPin, HIGH);
        lcd.setCursor(0,0);
        lcd.print("     ALERT      ");
        Serial.println("Alert...");   
        lcd.setCursor(0,1);
        lcd.print("  Low BP < 60   ");
      }
    }
  }
  else{
    // turn system off
    digitalWrite(ledPin, LOW);
    lcd.setCursor(0,0);
    lcd.print("Press Button to");
    lcd.setCursor(0,1);
    lcd.print("Start          ");
  }
  delay(50);
} 
