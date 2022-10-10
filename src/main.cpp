#include <Arduino.h>
#include <string.h>

short int pin = 14; // Teensy pin to output wave 14 is the TX pin of Serial3
unsigned int frequency = 400; // target frequency, must be greater than 35 Hz

short int mode = -1;


void setup() {
  
  Serial.begin(9600);

  getit:
    Serial.println("Please enter test mode: (LOW_test, BIN_test, or SQUARE_test");
    while (Serial.available() == 0) {}

    String reqest = Serial.readString();
    reqest.trim();

    if(reqest.equalsIgnoreCase("LOW_test"))
    {
      mode = 1;
      pinMode(pin, OUTPUT);
    }
    else if (reqest.equalsIgnoreCase("BIN_test"))
    {
      mode = 2;
      Serial3.begin(115200);
    }
    else if (reqest.equalsIgnoreCase("SQUARE_test"))
    {
      mode = 3;
      pinMode(pin, OUTPUT);
    }
    else
    {
        Serial.println("INVALID INPUT!");
        goto getit;
    }

    Serial.println("Beginning test in 5...");
    delay(1000);
    Serial.println("4...");
    delay(1000);
    Serial.println("3...");
    delay(1000);
    Serial.println("2...");
    delay(1000);
    Serial.println("1...");
    delay(1000);
    Serial.println("Beginning test");

    tone(pin, frequency);

    if(mode == 2)
    {
      Serial3.write(5);
    }
    else if (mode == 3)
    {
      for(int i = 0; i < 10; i++)
      {
        digitalWrite(pin, HIGH);
        digitalWrite(pin, LOW);
      }
    }
}

void loop() {
  if(mode == 1)
  {
    for(int i = 0; i < 4; i++)
    {
      digitalWrite(pin, LOW);
      delay(125);
      digitalWrite(pin, HIGH);
      delay(125);
    }
    delay(5000);
  }
}