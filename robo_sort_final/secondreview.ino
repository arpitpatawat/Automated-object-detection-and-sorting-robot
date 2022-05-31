
//==============================================================
//                  INCLUDING LIBRARIES
//==============================================================
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>
#include <ESP_Mail_Client.h>
#include "ThingSpeak.h"
#include "index.h" //Our HTML webpage contents with javascripts

//==============================================================
//                  INITIAL PROPERTIES
//==============================================================
String sliderValue = "0";
const char* ssid = "Enter_your_SSID_name";
const char* pass = "Enter_your_wifi_password";
unsigned long counterChannelNumber = Thingspeak_channer_number; // Channel ID
const char * myCounterReadAPIKey = "Thingspeak_read_API_key"; // Read API Key
const int FieldNumber1 = 1;  // The field in which our object is
long data1,data2;

#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465
#define AUTHOR_EMAIL "Sender's_Email"
#define AUTHOR_PASSWORD "Sender's_Email_Password"
#define RECIPIENT_EMAIL "recipient"
/* The SMTP Session object used for Email sending */
SMTPSession smtp;

LiquidCrystal_I2C lcd(0x27, 16, 2);
ESP8266WebServer server(80); //Server on port 80
WiFiClient  client;
Servo servo; //for gripper
Servo servo1;// for forward/reverse
Servo servo2;//left/right
Servo servo3;//up down

//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  servo.attach(D3, 500, 2250);  //use in case of lafda 2400
  servo1.attach(D4, 500, 2250);  //use in case of lafda 2400
  servo2.attach(D5, 500, 2250);  //use in case of lafda 2400
  servo3.attach(D6, 500, 2250);  //use in case of lafda 2400
  pinMode(BUILTIN_LED, OUTPUT); //here builtin led works inverted
  Serial.begin(115200); //baud rate of nodemcu
  Wire.begin(D2, D1);     //Wire.begin(SDA,SCL)
  WiFi.disconnect();
  lcd.begin();
  lcd.backlight();
  lcdclear();
  lcdinit();
  delay(500);
  WiFi.begin(ssid,pass);
  while(WiFi.status()!=WL_CONNECTED) //if status is not connected to
  {
    Serial.print(".");
    delay(500);
    digitalWrite(BUILTIN_LED, HIGH); //here high means low
  }
  digitalWrite(BUILTIN_LED,LOW); //here low means high
  Serial.println("");
  Serial.print("Connected! IP Address is: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  lcdclear();
  lcd.print("SERVER ready,IP-");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
server.on("/slider", handleslider ) ;
  server.on("/sortingstate", handlestate);
  server.on("/readdata1", handledata1);
  server.on("/readdata2", handledata2);
  server.on("/mailstate", handlemail);
  server.begin();                  //Start server
  Serial.println("HTTP server started");
  ThingSpeak.begin(client);
  
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  label: server.handleClient();          //Handle client requests
  int pos;
  String t_state = server.arg("panelstate"); 
  if(t_state == "1")
  {
    lcdclear();
    lcd.print("Sorting Type -");
    lcdlinechange();
    lcd.print("Automatic Mode");
    //server.send(200, "text/plane", "OK"); //Send web page
    long obj = ThingSpeak.readLongField(counterChannelNumber, FieldNumber1, myCounterReadAPIKey);
    int statusCode = ThingSpeak.getLastReadStatus();
//    if (statusCode == 200)
//    {
      if(obj==1)
      {
        lcdclear();
        lcd.print("object 1");
        lcdlinechange();
        lcd.print("Place object!");
        delay(5000);
        leftsort();
        handledata1();
        goto label;
      }
      else if(obj ==2)
      {
        lcdclear();
        lcd.print("object 2");
        lcdlinechange();
        lcd.print("Place object!");
        delay(5000);
        rightsort();
        handledata2();
        goto label;
      }
        goto label;
    }//}
 
// else {
//    lcdclear();
//    lcd.print("Sorting Type -");
//    lcdlinechange();
//    lcd.print("Manual Mode");
// }
}


//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void handledata1(){
  data1 = ThingSpeak.readLongField(counterChannelNumber, FieldNumber1, "myCounterReadAPIKey");
  Serial.println(data1);
  server.send(200, "text/plane", String(data1));
}

void handledata2(){
  data2 = ThingSpeak.readLongField(counterChannelNumber, 2, "myCounterReadAPIKey");
  server.send(200, "text/plane", String(data2));
}

void handlemail(){
  if (server.arg("bin").toInt()== 1){
        lcdclear();
        lcd.print("Sending E-mail");
        sendmail();
        lcdlinechange();
        lcd.print("Email sent !");
    }
  }

void handlestate(){
   if (server.arg("data").toInt()== 0){
    lcdclear();
    lcd.print("Sorting left");
    rightsort();
    
   }
   else 
  { lcdclear();
   lcd.print("Sorting Right");
   leftsort();}
}
void handleslider(){
    String inputMessage;// GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (server.arg("value1").toInt()!= 0) {
      inputMessage = server.arg("value1"); 
      sliderValue = inputMessage;
      //Serial.print("Slider 1 value is: ");
      lcdclear();
      lcd.print("moving Slider 1");
      lcdlinechange();
      lcd.print("forward/reverse");
      servo1.write(sliderValue.toInt()); 
      
    }
    else if(server.arg("value2").toInt()!= 0) {
      inputMessage = server.arg("value2"); 
      sliderValue = inputMessage;
      //Serial.print("Slider 2 value is: ");
     
      lcdclear();
      lcd.print("moving Slider 2");
      lcdlinechange();
      lcd.print("up / down");
       servo3.write(sliderValue.toInt()); 
    }
    else if(server.arg("value3").toInt()!= 0) {
      inputMessage = server.arg("value3"); 
      sliderValue = inputMessage;
     // Serial.print("Slider 3 value is: ");
      
      lcdclear();
      lcd.print("moving Slider 3");
      lcdlinechange();
      lcd.print("left / right");
      servo2.write(sliderValue.toInt()); 
    }
    else if(server.arg("value4").toInt()!= 0) {
      inputMessage = server.arg("value4"); 
      sliderValue = inputMessage;
      //Serial.print("Slider 4 value is: ");
      
      lcdclear();
      lcd.print("moving Slider 4");
      lcdlinechange();
      lcd.print("Gripper");
      servo.write(sliderValue.toInt()); 
    }
    server.send(200, "text/plain", "OK");
  }
//===============================================================
// LCD functions
//===============================================================
 void lcdinit(){
  lcd.setCursor(0, 0);
  lcd.print("Connecting To");
  lcd.setCursor(0, 1);
  lcd.print("Wifi Network ..."); 
 }

 void lcdclear(){
  lcd.clear();
  lcd.home();  
 }

 void lcdlinechange(){
  lcd.setCursor(0,1);
 }

 //===============================================================
// Servo functions
//================================================================
void leftsort(){
        int pos;
        for (pos = 90; pos <= 153; pos += 1) { 
          servo3.write(pos); //D1           
          delay(25);                       
        }
        for (pos = 90; pos <= 116; pos += 1) { 
          servo1.write(pos); //D1           
          delay(25);                       
        }
        servo.write(20);
        delay(2000);
        for (pos = 153; pos <= 180; pos += 1) { 
          servo3.write(pos); //D1           
          delay(25);                       
        }
        for (pos = 116; pos >= 60; pos -= 1) { 
          servo1.write(pos); //D1           
          delay(25);                       
        }
        for (pos = 90; pos >= 0; pos -= 1) { 
          servo2.write(pos); //D1           
          delay(25);                       
        }
        for (pos = 60; pos <= 90; pos += 1) { 
          servo1.write(pos); //D1           
          delay(25);                       
        }
        for (pos = 180; pos >= 90; pos -= 1) { 
          servo3.write(pos); //D1           
          delay(25);                       
        }
        delay(2000);
        servo.write(90);
       
        for (pos = 0; pos <= 90; pos += 1) { 
          servo2.write(pos); //D1           
          delay(25);                       
        }
        delay(2000);
      }

      
void rightsort(){
        int pos;
        for (pos = 90; pos <= 153; pos += 1) { 
          servo3.write(pos); //D1           
          delay(25);                       
        }
        for (pos = 90; pos <= 116; pos += 1) { 
          servo1.write(pos); //D1           
          delay(25);                       
        }
        servo.write(20);
        delay(2000);
        for (pos = 153; pos <= 180; pos += 1) { 
          servo3.write(pos); //D1           
          delay(25);                       
        }
        for (pos = 116; pos >= 60; pos -= 1) { 
          servo1.write(pos); //D1           
          delay(25);                       
        }
        for (pos = 90; pos <= 180; pos += 1) { 
          servo2.write(pos); //D1           
          delay(25);                       
        }
        for (pos = 60; pos <= 90; pos += 1) { 
          servo1.write(pos); //D1           
          delay(25);                       
        }
        for (pos = 180; pos >= 90; pos -= 1) { 
          servo3.write(pos); //D1           
          delay(25);                       
        }
        delay(2000);
        servo.write(90);
       
        for (pos = 180; pos >= 90; pos -= 1) { 
          servo2.write(pos); //D1           
          delay(25);                       
        }
        delay(2000);
      }

//===============================================================
// Sending Email
//================================================================
void sendmail(){
     /** Enable the debug via Serial port
   * none debug or 0
   * basic debug or 1
  */
  smtp.debug(1);

  /* Set the callback function to get the sending results */
  

  /* Declare the session config data */
  ESP_Mail_Session session;

  /* Set the session config */
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = "";

  /* Declare the message class */
  SMTP_Message message;
  message.sender.name = "Sender_name";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "Email_subject";
  message.addRecipient("Arpit", RECIPIENT_EMAIL);
  String htmlMsg = "<div style=\"color:#2f4468;\"><h1>Enter message</h1></div>";
  message.html.content = htmlMsg.c_str();
  message.html.content = htmlMsg.c_str();
  message.text.charSet = "us-ascii";
  message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
   /* Connect to server with the session config */
  if (!smtp.connect(&session))
    return;

  /* Start sending Email and close the session */
  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email, " + smtp.errorReason());
    }
