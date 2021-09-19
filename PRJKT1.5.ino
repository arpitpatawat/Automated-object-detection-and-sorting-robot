  #include "ThingSpeak.h"
  #include <ESP8266WiFi.h>
  #include <Servo.h>
  const char ssid[] = "i";  // your network SSID (name)
  const char pass[] = "12345678";   // your network password         
  WiFiClient  client;
  
  //---------Channel Details---------//
  unsigned long counterChannelNumber = 1384655;            // Channel ID
  const char * myCounterReadAPIKey = "E87YBV08BWJU8C3X"; // Read API Key
  const int FieldNumber1 = 1;  // The field in which our object is
  
  Servo servo; //for gripper
  Servo servo1;// for forward/reverse
  Servo servo2;//left/right
  Servo servo3;//up down
  
  void setup()
  {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    ThingSpeak.begin(client);
    servo.attach(D0); //for gripper
    servo1.attach(D1); // for forward/reverse
    servo2.attach(D2); //left/right
    servo3.attach(D3);//up down
    pinMode(D5,OUTPUT);
    pinMode(D6,OUTPUT);
  }
  
  void loop()
  {
    int pos;
    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.print("Connecting to ");
      Serial.print(ssid);
      Serial.println(" ....");
      while (WiFi.status() != WL_CONNECTED)
      {
        WiFi.begin(ssid, pass);
        delay(5000);
      }
      Serial.println("Connected to Wi-Fi Succesfully.");
    }
    servo.write(80);
    servo1.write(90);
    servo2.write(90);
    servo3.write(90);
    long obj = ThingSpeak.readLongField(counterChannelNumber, FieldNumber1, myCounterReadAPIKey);
    int statusCode = ThingSpeak.getLastReadStatus();
    if (statusCode == 200)
    {
      if(obj==1)
      {
        digitalWrite(D5,HIGH);
        digitalWrite(D6,LOW);
        Serial.print("object is Elephant\n");
        servo3.write(170);
        for (pos = 90; pos <= 120; pos += 1) { 
          servo1.write(pos); //D1           
          delay(25);                       
        }
        delay(1000);
        servo.write(20);
        for (pos = 120; pos >= 90; pos -= 1) { 
           servo1.write(pos);//D1          
           delay(25);                  
        }
        servo3.write(90);
        for (pos = 90; pos >= 0; pos -= 1) { 
          servo2.write(pos);//D2             
          delay(25);                  
        }
        for (pos = 90; pos <= 120; pos += 1) { 
          servo1.write(pos); //D1           
          delay(25);                       
        }
        delay(1000);
        servo.write(80);
        for (pos = 120; pos >= 90; pos -= 1) { 
           servo1.write(pos);//D1          
           delay(25);                  
        }
        delay(1000);
        for (pos = 0; pos <= 90; pos += 1) { 
           servo2.write(pos); //D2            
           delay(25);                  
        }
        delay(2000);
      }
      if(obj==2)
      {
        digitalWrite(D6,HIGH);
        digitalWrite(D5,LOW);
        Serial.print("object is Zebra\n");
        servo3.write(170);
        for (pos = 90; pos <= 110; pos += 1) { 
          servo1.write(pos); //D1           
          delay(25);                       
        }
        delay(1000);
        servo.write(20);
        for (pos = 110; pos >= 90; pos -= 1) { 
           servo1.write(pos);//D1         
           delay(25);                  
        }
        servo3.write(90);
        for (pos = 90; pos <= 180; pos += 1) { 
          servo2.write(pos);//D2             
          delay(25);                  
        }
        for (pos = 90; pos <= 110; pos += 1) { 
          servo1.write(pos); //D1           
          delay(25);                       
        }
        delay(1000);
        servo.write(80);
        for (pos = 110; pos >= 90; pos -= 1) { 
           servo1.write(pos);//D1          
           delay(25);                  
        }
        delay(1000);
        for (pos = 180; pos >= 90; pos -= 1) { 
           servo2.write(pos); //D2            
           delay(25);                  
        }
        delay(2000);
      }
      if(obj==0)
      {
      Serial.print("NULL request entered\n");
      digitalWrite(D6,HIGH);
      digitalWrite(D5,HIGH);
      }
    }
    else
    {
      Serial.println("Unable to read channel,trying again....");
    }
    delay(100);
  }
