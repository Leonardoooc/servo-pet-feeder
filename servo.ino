#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID           "TMPL2akAUf5Ay"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>
Servo myservo;

int servoPin = 26;
int buttonPin = 12;

// Enter your Auth token
char auth[] = "7pt25Ug-3CQKSGy6f1ZfIQAZCH1C7OOs";

//Enter your WIFI SSID and password
char ssid[] = "ENG_SOFT";
char pass[] = "flamengo";

void setup(){
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  myservo.setPeriodHertz(50); 
  myservo.attach(13);

  pinMode(12, INPUT);

  pinMode(2, OUTPUT); 
}

int pos = 0;
int buttonState = 0;

int blynkButton = false;

BLYNK_WRITE(V1) // this command is listening when something is written to V1
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  
  if (pinValue == 1){
    blynkButton = true;
  } else if (pinValue == 0) {
    blynkButton = false;
  }
  
  Serial.print("V1 button value is: "); // printing value to serial monitor
  Serial.println(pinValue);
}

void loop(){



  buttonState = digitalRead(buttonPin);
  if (blynkButton || buttonState == HIGH) {
    Serial.println("ligado");
    myservo.attach(13);
    for (pos = 0; pos <= 5; pos += 1) {
      myservo.attach(13);
      myservo.write(90);
      delay(100);
      myservo.detach();
      delay(500);
    }
    delay(1000);
  } else {
    myservo.detach();
  }
  
  digitalWrite(2, HIGH); 

  /*myservo.attach(13);
  myservo.write(180);
  delay(3000);
  myservo.write(0);
  delay(3000);
  myservo.detach();
  delay(5000);*/

  /*for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(1);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(1);                       // waits 15ms for the servo to reach the position
  }*/
  Blynk.run();
}