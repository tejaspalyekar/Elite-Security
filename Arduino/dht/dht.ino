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

int Buzzer = D3;
int val;


void setup() {
  
  
  pinMode(5, INPUT); 
  pinMode (Buzzer, OUTPUT); 
  
  Serial.begin(9600);
  delay(500);

  while (WiFi.status() == WL_DISCONNECTED) {
    myNetwork();
  }
  //digitalWrite(ON_Board_LED, HIGH);
  
  Serial.println("Successfully Connected ");
  //pinMode(ON_Board_LED, OUTPUT);
  
  /*WiFi.begin(ssid, password); 
  Serial.println("");
    
  pinMode(ON_Board_LED,OUTPUT); 
  digitalWrite(ON_Board_LED, HIGH); 

  pinMode(LED_D8,OUTPUT);  
  digitalWrite(LED_D8, LOW); 


  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
  
  }
  
  //----------------------------------------
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();*/
  //----------------------------------------

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  //----------------------------------------

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
          Serial.println("No of Network Available ==");
          Serial.print(network);
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
          Serial.println("No of Network Available ==");
          Serial.print(network);
          delay(2000);
          Serial.println("Connecting with Redmi9 Please Wait..");
          delay(2000);
          break;
        }
    }
  }

}

void loop() {
  
  val = digitalRead(5);
  String strHum = String(val); 


  if (!Ping.ping(remote_ip)) {
    Serial.println("No Internet");
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
  //----------------------------------------
  
  if (getData == "on") {
    //digitalWrite(LED_D8, HIGH);
    Serial.println("sensor On");
    Serial.println();
    
    if (val == 1) {                  //shutter close == 0  open == 1
         
         //tone(Buzzer, 1000, 100);
         digitalWrite (Buzzer, HIGH); //turn buzzer on
         delay(500);
         digitalWrite (Buzzer, LOW);  //turn buzzer off
         //delay(500);
     }
  }

     else if (getData == "off") 
     {
        //digitalWrite(LED_D8, LOW);
        //String change = "0";
        //strHum = change;
        Serial.println("sensor off");
        Serial.println();
     }

  else {
    Serial.print("give proper input:");
  }
  
  Firebase.setString("SensorData_And_Status/sensor value",strHum); 
  
  // Conditions for handling errors.
  if (Firebase.failed()) {
      Serial.print("setting data failed :");
      Serial.println(Firebase.error()); 
      delay(500); 
      return;
  }


  //----------------------------------------

  Serial.println("Setting successful");
  Serial.println();
   
  //delay(1000);
}
