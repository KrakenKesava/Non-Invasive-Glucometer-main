#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include "MAX30105.h"

// set the LCD number of columns and rows
MAX30105 particleSensor;
#define debug Serial

const char* ssid = "1234";
const char* password = "06102004";

String ApiKey_write = "KA74G0UQWB0IIZX1";
String ApiKey_read = "ZDDW6JOQAR00KHQQ";

const char* write_serverName = "http://api.thingspeak.com/update";
String i_read_serverName = "https://api.thingspeak.com/channels/2718503/fields/1.json" ;
             // &result=3 shows the 3 previous entries in ThingSpeak
String read_serverName = i_read_serverName + + "?api_key=" + ApiKey_read + "&results=3";

int buz=7;
int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  
char b , a;
void setup(){
  // pinMode(buz,OUTPUT);
  // digitalWrite(buz,0);
  lcd.init();                     
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Welcome, Place");
  lcd.setCursor(0, 1);
  lcd.println("Finger on sensor");

  Serial.begin(115200);
  Serial.println("MAX30102 basic reading example");

  if(particleSensor.begin() == false)
  {
    Serial.println("MAX30102 was not found. please check wiring/power.");
    while(1);  
  }
  particleSensor.setup();

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to Wifi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("1. 0-20");
  Serial.println("2. 21-65");
  Serial.println("3. 65 ABOVE");

    while (Serial.available()== 0) {} // wait for user input
    a = Serial.read(); // read the incoming character

  Serial.println("1. BEFORE FOOD");
  Serial.println("2. AFTER FOOD");
}

void loop()
{
  // debug.print(" R[");
  // debug.print(particleSensor.getRed());
  // debug.print("] IR[");
  // debug.print(particleSensor.getIR());
  // debug.print("] G[");
  // debug.print(particleSensor.getGreen());
  // debug.print("]");
  // debug.println();
  while (Serial.available()== 0) {} // wait for user input
      b = Serial.read(); // read the incoming character
      lcd.clear();
      lcd.setCursor(0,0);
    float PS_IR = particleSensor.getIR();
  if(a == '1' && b =='1'){
    lcd.setCursor(0, 0);
    lcd.println("enter into");
    if(PS_IR>100000 && PS_IR<=125000)
    {
      digitalWrite(buz,1);
      lcd.setCursor(0,0);
      lcd.print("IR:" + String(PS_IR/1000.0));
      lcd.print(" mg/dl");
    delay(150);
      lcd.setCursor(0,1);
      lcd.print("PRE DIABETIC");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" PRE DIABETIC");
       delay(10000);
 digitalWrite(buz,0);
      lcd.clear();

    }
    else if(PS_IR>125000)
    {
      digitalWrite(buz,1);
      lcd.setCursor(0,0);
      lcd.print("IR:" + String(PS_IR/1000.0));
      lcd.print(" mg/dl");
    delay(150);
      lcd.setCursor(0,1);
      lcd.print("DIABETIC");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" DIABETIC");
       delay(10000);
 digitalWrite(buz,0);
      lcd.clear();
    }
    else if(PS_IR>70000 && PS_IR<100000)
    {
      digitalWrite(buz,0);
      lcd.setCursor(0,0);
      lcd.print("IR:" + String(PS_IR/1000.0));
      lcd.print(" mg/dl");
    delay(150);
      lcd.setCursor(0,1);
      lcd.print("NORMAL DIABETES");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println( " NORMAL DIABETES");
       delay(10000);
 digitalWrite(buz,0);
      lcd.clear();
    }
    else if(PS_IR<70000)
    {
      digitalWrite(buz,0);
      lcd.setCursor(0,0);
      lcd.print("IR:" + String(PS_IR/1000.0));
      lcd.print(" mg/dl");
    delay(150);
      lcd.setCursor(0,1);
      lcd.print("LOW DIABETES");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" LOW DIABETES");
       delay(10000);
 digitalWrite(buz,0);
      lcd.clear();
    }
    else
    {
      digitalWrite(buz,0);
      
      lcd.setCursor(0,1);
      lcd.print("NORMAL DIABETES");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" NORMAL DIABETES");
    }
  }

 

  if(a =='1' && b == '2'){
     if(PS_IR>140000 && PS_IR<=200000)
    {
      digitalWrite(buz,1);
      lcd.setCursor(0,0);
      lcd.print("IR:" + String(PS_IR/1000.0));
      lcd.print(" mg/dl");
    delay(150);
      lcd.setCursor(0,1);
      lcd.print("PRE DIABETIC");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" PRE DIABETIC");
       delay(10000);
 digitalWrite(buz,0);
      lcd.clear();
    }
    else if(PS_IR>200000)
    {
      digitalWrite(buz,1);
      lcd.setCursor(0,0);
      lcd.print("IR:" + String(PS_IR/1000.0));
      lcd.print(" mg/dl");
    delay(150);
      lcd.setCursor(0,1);
      lcd.print("DIABETIC");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" DIABETIC");
       delay(10000);
 digitalWrite(buz,0);
      lcd.clear();
    }
    else if(PS_IR>100000 && PS_IR<140000)
    {
      digitalWrite(buz,0);
      lcd.setCursor(0,0);
      lcd.print("IR:" + String(PS_IR/1000.0));
      lcd.print(" mg/dl");
    delay(150);
      lcd.setCursor(0,1);
      lcd.print("NORMAL DIABETES");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" NORMAL DIABETES");
       delay(10000);
 digitalWrite(buz,0);
      lcd.clear();
    }
    else if(PS_IR<100000)
    {
      digitalWrite(buz,0);
      lcd.setCursor(0,0);
      lcd.print("IR:" + String(PS_IR/1000.0));
      lcd.print(" mg/dl");
    delay(150);
      lcd.setCursor(0,1);
      lcd.print("LOW DIABETES");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" LOW DIABETES");
       delay(10000);
 digitalWrite(buz,0);
      lcd.clear();
    }
    else
    {
      digitalWrite(buz,0);
      
      lcd.setCursor(0,1);
      lcd.print("NORMAL DIABETES");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" NORMAL DIABETES");
    }
  }

  

  if(a == '2' && b == '1'){
    if(PS_IR>100000 && PS_IR<=130000)
    {
      digitalWrite(buz,1);
      lcd.setCursor(0,0);
      lcd.print("IR:" + String(PS_IR/1000.0));
      lcd.print(" mg/dl");
    delay(150);
      lcd.setCursor(0,1);
      lcd.print("PRE DIABETIC");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" PRE DIABETIC");
       delay(10000);
 digitalWrite(buz,0);
      lcd.clear();
    }
    else if(PS_IR>130000)
    {
      digitalWrite(buz,1);
      lcd.setCursor(0,0);
      lcd.print("IR:" + String(PS_IR/1000.0));
      lcd.print(" mg/dl");
    delay(150);
      lcd.setCursor(0,1);
      lcd.print("DIABETIC");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" DIABETIC");
       delay(10000);
 digitalWrite(buz,0);
      lcd.clear();
    }
    else if(PS_IR>80000 && PS_IR<100000)
    {
      digitalWrite(buz,0);
      lcd.setCursor(0,0);
      lcd.print("IR:" + String(PS_IR/1000.0));
      lcd.print(" mg/dl");
    delay(150);
      lcd.setCursor(0,1);
      lcd.print("NORMAL DIABETES");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" NORMAL DIABETES");
       delay(10000);
 digitalWrite(buz,0);
      lcd.clear();
    }


    else if(PS_IR<80000)
    {
      digitalWrite(buz,0);
      lcd.setCursor(0,0);
      lcd.print("IR:" + String(PS_IR/1000.0));
      lcd.print(" mg/dl");
    delay(150);
      lcd.setCursor(0,1);
      lcd.print("LOW DIABETES");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" LOW DIABETES");
       delay(10000);
 digitalWrite(buz,0);
      lcd.clear();
    }
 else
    {
      digitalWrite(buz,0);
      
      lcd.setCursor(0,1);
      lcd.print("NORMAL DIABETES");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" NORMAL DIABETES");
    }

   

  }
  if(a == '2' && b == '2'){
    if(PS_IR>140000 && PS_IR<=200000)
    {
      digitalWrite(buz,1);
      lcd.setCursor(0,0);
      lcd.print("IR:" + String(PS_IR/1000.0));
      lcd.print(" mg/dl");
    delay(150);
      lcd.setCursor(0,1);
      lcd.print("PRE DIABETIC");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" PRE DIABETIC");
       delay(10000);
 digitalWrite(buz,0);
      lcd.clear();
    }
    else if(PS_IR>200000)
    {
      digitalWrite(buz,1);
      lcd.setCursor(0,0);
      lcd.print("IR:" + String(PS_IR/1000.0));
      lcd.print(" mg/dl");
    delay(150);
      lcd.setCursor(0,1);
      lcd.print("DIABETIC");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" DIABETIC");
       delay(10000);
 digitalWrite(buz,0);
      lcd.clear();
    }
    else if(PS_IR>100000 && PS_IR<140000)
    {
      digitalWrite(buz,0);
      lcd.setCursor(0,0);
      lcd.print("IR:" + String(PS_IR/1000.0));
      lcd.print(" mg/dl");
    delay(150);
      lcd.setCursor(0,1);
      lcd.print("NORMAL DIABETES");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" NORMAL DIABETES");
       delay(10000);
 digitalWrite(buz,0);
      lcd.clear();
    }
    else if(PS_IR<100000)
    {
      digitalWrite(buz,0);
      lcd.setCursor(0,0);
      lcd.print("IR:" + String(PS_IR/1000.0));
      lcd.print(" mg/dl");
    delay(150);
      lcd.setCursor(0,1);
      lcd.print("LOW DIABETES");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" LOW DIABETES");
       delay(10000);
 digitalWrite(buz,0);
      lcd.clear();
    }
    else
    {
      digitalWrite(buz,0);
      
      lcd.setCursor(0,1);
      lcd.print("NORMAL DIABETES");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" NORMAL DIABETES");
    }
  }
  
 

  if(a == '3' && b == '1'){
    if(PS_IR>130000 && PS_IR<=180000)
    {
      digitalWrite(buz,1);
      lcd.setCursor(0,0);
      lcd.print("IR:" + String(PS_IR/1000.0));
      lcd.print(" mg/dl");
    delay(150);
      lcd.setCursor(0,1);
      lcd.print("PRE DIABETIC");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" PRE DIABETIC");
       delay(10000);
 digitalWrite(buz,0);
      lcd.clear();
    }
    else if(PS_IR>180000)
    {
      digitalWrite(buz,1);
      lcd.setCursor(0,0);
      lcd.print("IR:" + String(PS_IR/1000.0));
      lcd.print(" mg/dl");
    delay(150);
      lcd.setCursor(0,1);
      lcd.print("DIABETIC");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" DIABETIC");
       delay(10000);
 digitalWrite(buz,0);
      lcd.clear();
    }
    else if(PS_IR>80000 && PS_IR<130000)
    {
      digitalWrite(buz,0);
      lcd.setCursor(0,0);
      lcd.print("IR:" + String(PS_IR/1000.0));
      lcd.print(" mg/dl");
    delay(150);
      lcd.setCursor(0,1);
      lcd.print("NORMAL DIABETES");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" NORMAL DIABETES");
       delay(10000);
 digitalWrite(buz,0);
      lcd.clear();
    }
    else if(PS_IR<80000)
    {
      digitalWrite(buz,0);
      lcd.setCursor(0,0);
      lcd.print("IR:" + String(PS_IR/1000.0));
      lcd.print(" mg/dl");
    delay(150);
      lcd.setCursor(0,1);
      lcd.print("LOW DIABETES");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" LOW DIABETES");
       delay(10000);
 digitalWrite(buz,0);
      lcd.clear();
    }
    else
    {
      digitalWrite(buz,0);
      
      lcd.setCursor(0,1);
      lcd.print("NORMAL DIABETES");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" NORMAL DIABETES");
    }
  }

 

  if(a == '3' && b == '2'){
    if(PS_IR>160000 && PS_IR<=200000)
    {
      digitalWrite(buz,1);
      lcd.setCursor(0,0);
      lcd.print("IR:" + String(PS_IR/1000.0));
      lcd.print(" mg/dl");
    delay(150);
      lcd.setCursor(0,1);
      lcd.print("PRE DIABETIC");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" PRE DIABETIC");
       delay(10000);
 digitalWrite(buz,0);
      lcd.clear();
    }
    else if(PS_IR>200000)
    {
      digitalWrite(buz,1);
      lcd.setCursor(0,0);
      lcd.print("IR:" + String(PS_IR/1000.0));
      lcd.print(" mg/dl");
    delay(150);
      lcd.setCursor(0,1);
      lcd.print("DIABETIC");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" DIABETIC");
       delay(10000);
 digitalWrite(buz,0);
      lcd.clear();
    }
    else if(PS_IR>90000 && PS_IR<160000)
    {
      digitalWrite(buz,0);
      lcd.setCursor(0,0);
      lcd.print("IR:" + String(PS_IR/1000.0));
      lcd.print(" mg/dl");
    delay(150);
      lcd.setCursor(0,1);
      lcd.print("NORMAL DIABETES");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" NORMAL DIABETES");
       delay(10000);
 digitalWrite(buz,0);
      lcd.clear();
    }
    else if(PS_IR<90000)
    {
      digitalWrite(buz,0);
      lcd.setCursor(0,0);
      lcd.print("IR:" + String(PS_IR/1000.0));
      lcd.print(" mg/dl");
    delay(150);
      lcd.setCursor(0,1);
      lcd.print("LOW DIABETES");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" LOW DIABETES");
       delay(10000);
 digitalWrite(buz,0);
      lcd.clear();
    }
    else
    {
      digitalWrite(buz,0);
      
      lcd.setCursor(0,1);
      lcd.print("NORMAL DIABETES");
      Serial.print("IR:" + String(PS_IR/1000.0));
      Serial.println(" NORMAL DIABETES");
    }
  }

  // else if( a == ' ' || b == ' ')
  // {
  //   lcd.setCursor(0,1);
  //   lcd.print("Enter response");
  // }

  else if(( a == '4' || '5' || '6' || '7' || '8' || '9' || '0') || 
            ( b == '3' || '4' || '5' || '6' || '7' || '8' || '9' || '0' ))
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Invalid Input");

  }


  else{
    lcd.setCursor(0,1);
    lcd.print("Enter response");
  }

  if(WiFi.status() == WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;

      if(isnan(PS_IR/1000.0)){
      Serial.println("Failed to read from IR sensor");
      return;
    }
                                                                                // writing data 
    http.begin(client , write_serverName);

    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String httpReqData= "api_key=" + ApiKey_write + "&field1=" + String(PS_IR/1000.0);   // writing the Glucose level into thing speak
    Serial.println(httpReqData);
    int httpResCode = http.POST(httpReqData);

    Serial.print("HTTP Response code:");
    Serial.println(httpResCode);

    http.end();                                                                          // writing completed and closed url

                                                                                    // READING data
    http.begin(client,read_serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    int httpResponseCode = http.GET(); 
    if (httpResponseCode > 0) {  
        String read_httpResData = http.getString();  
        Serial.print("HTTP Read Data: ");
        Serial.println(read_httpResData);  
    } else {
        Serial.print("Error on HTTP request: ");
        Serial.println(httpResponseCode); 
    }
    http.end();


    
  } 
  else{
    Serial.println("WiFi Disconnected");
  }

}