#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include<ESP8266Ping.h>

#define FIREBASE_HOST "elite-security-e996a-default-rtdb.europe-west1.firebasedatabase.app"                                                        
#define FIREBASE_AUTH "y3YB9XT4XHfomI5CHgmBk347vxbRd93cCSTVR1DG"                                                              
                                      

#define ON_Board_LED 2  //--> Defining an On Board LED, used for indicators when the process of connecting to a wifi router

//#define LED_D8 15 //--> Defines an LED Pin. D8


const char* ssid1 = "tejas"; 
const char* password1 = "9869268482"; 

const char* ssid2 = "Redmi9"; 
const char* password2 = "vaishali"; 

const IPAddress remote_ip(208, 80, 153, 224);

int Buzzer = D0;
int Buzzer1 = D2;
int val;



void setup() {
  
  
  pinMode(5, INPUT); 
  pinMode (Buzzer, OUTPUT); 
  pinMode (Buzzer1, OUTPUT);
  
  Serial.begin(115200);
  delay(500);

  while (WiFi.status() == WL_DISCONNECTED) {
    myNetwork();
  }  
  Serial.println("Successfully Connected ");
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);


  delay (500);

  
  Firebase.setString("SensorData_And_Status/Status","on");

  // Conditions for handling errors.
  if (Firebase.failed()) {
      Serial.print("Failed to create SensorValueAndLEDStat");
      Serial.println(Firebase.error());  
  }
 
}


void myNetwork() {
  int flag = 1;
  Serial.println("Searching Wifi......");
  int network = WiFi.scanNetworks();          
  for (int i = 0 ; i < network; i++) {
    switch (flag) {
      case 1:  
        flag =2;
        if (WiFi.SSID(i) == ssid1) {
          WiFi.begin(ssid1, password1);                 
          Serial.println("Wifi Found"); 
          buzzer_nonet();    
          delay(2000);
          Serial.println("Connecting with Tejas Please Wait..");
          delay(2000);
          break;
        }
        case 2:
           flag =1;
           if (WiFi.SSID(i) == ssid2) {
          WiFi.begin(ssid2, password2);          
          Serial.println("Wifi Found");
          buzzer_nonet();
          delay(2000);
          Serial.println("Connecting with Redmi9 Please Wait..");
          delay(2000);
          break;
        }
    }
  }

}

void buzzer(){   
   val = digitalRead(5);
   String getData = Firebase.getString("SensorData_And_Status/Status");
    while (val == 1 && getData == "on") {                                                     //shutter close == 0  open == 1     
         tone(Buzzer, 450);
         tone(Buzzer1, 450);
         delay(500);
         noTone(Buzzer);
         noTone(Buzzer1);
         delay(500);
         tone(Buzzer, 450);
         tone(Buzzer1, 450);
         delay(500);
         noTone(Buzzer);
         noTone(Buzzer1);
         delay(500);
         tone(Buzzer, 450);
         tone(Buzzer1, 450);
         delay(500);
         noTone(Buzzer);
         noTone(Buzzer1);
         Serial.println("buzzer On!!");
         val = digitalRead(5);
         String getData = Firebase.getString("SensorData_And_Status/Status");
         String strHum = String(val); 

         Firebase.setString("SensorData_And_Status/sensor value",strHum);   
                            // Conditions for handling errors.
         if (Firebase.failed()) {
             Serial.print("setting data failed :");
             Serial.println(Firebase.error()); 
             delay(500); 
             return;
            }
        else{
            Serial.println("Setting successful");   
            }
       delay(250);
    }
}

void buzzer_nonet(){
  val = digitalRead(5);
    while (val == 1) {                                                     //shutter close == 0  open == 1     
         tone(Buzzer, 450);
         tone(Buzzer1, 450);
         delay(500);
         noTone(Buzzer);
         noTone(Buzzer1);
         delay(500);
         tone(Buzzer, 450);
         tone(Buzzer1, 450);
         delay(500);
         noTone(Buzzer);
         noTone(Buzzer1);
         delay(500);
         tone(Buzzer, 450);
         tone(Buzzer1, 450);
         delay(500);
         noTone(Buzzer);
         noTone(Buzzer1);
         Serial.println("buzzer On when no net!!");
         val = digitalRead(5);        
         delay(250);

    }
}



void loop() {
    val = digitalRead(5);
  String strHum = String(val); 

  Firebase.setString("SensorData_And_Status/sensor value",strHum); 
  
  // Conditions for handling errors.
   if (Firebase.failed()) {
      Serial.print("setting data failed :");
      Serial.println(Firebase.error()); 
      delay(500); 
      return;
     }
   else{
      Serial.println("Setting successful");   
   }
   
  if (!Ping.ping(remote_ip)) {
    Serial.println("No Internet");
    buzzer_nonet();
    myNetwork();
   } 
  else {
    Serial.println("Internet Access");
    Firebase.setString("SensorData_And_Status/online_Status","0");  
   }

  String getData = Firebase.getString("SensorData_And_Status/Status");

  // Conditions for handling errors.
  if (Firebase.failed()) {
      Serial.print("Getting /Status failed :");
      Serial.println(Firebase.error()); 
      delay(500); 
      return;
  }
  
  if (getData == "on") {   
    Serial.println("System On");
    Serial.println();
    buzzer();
    
   /* while (val == 1) {                                                     //shutter close == 0  open == 1     
         tone(Buzzer, 800, 500);
         tone(Buzzer1, 800, 500);
         //delay(250);

     }*/
    /*if (val == 0) {                                                     //shutter close == 0  open == 1     
         digitalWrite (Buzzer, LOW);
         digitalWrite (Buzzer1, LOW);                                    //turn buzzer on
         //delay(2000);

     }*/
  }

     else if (getData == "off") 
     {
        
        Serial.println("System off");
        Serial.println();
     }

  else {
    Serial.print("give proper input:");
  }

 /*if (getData == "on") {   
   Serial.println("System On");
   Serial.println();
   buzzer();*/
  delay(500); 

}
