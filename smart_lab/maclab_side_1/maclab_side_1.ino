
#include <ESP8266WiFi.h>
#include <ros.h>
#include <std_msgs/Int16.h>


// Init constants and global variables

#define DEBUG 1

// WiFi configuration. Replace '***' with your data

const char* ssid = "robot_r";
const char* password = "robin7624";
IPAddress server(192,168,43,94);      // Set the rosserial socket ROSCORE SERVER IP address
const uint16_t serverPort = 11413;    // Set the rosserial socket server port


// Functions definitions //

void setupWiFi() {                    // connect to ROS server as as a client
  if(DEBUG){
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
  }
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }
  if(DEBUG){
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

void light_Callback(const std_msgs::Int16& received_msg)
{  
      int my_payload=received_msg.data;
      
  if (my_payload==110)
      {
        digitalWrite(D1, HIGH);
      }
 else if(my_payload==111)
      {
        digitalWrite(D1, LOW);
      } 
 else if(my_payload==140)
      {
        digitalWrite(D2, HIGH);
      } 
 else if(my_payload==141)
      {
        digitalWrite(D2, LOW);
      } 
else if(my_payload==160)
      {
        digitalWrite(D3, HIGH);
      } 
 else if(my_payload==161)
      {
        digitalWrite(D3, LOW);
      } 
else if(my_payload==170)
      {
        digitalWrite(D3, HIGH);
      } 
 else if(my_payload==171)
      {
        digitalWrite(D3, LOW);
      } 
else if(my_payload==190)
      {
        digitalWrite(D4, HIGH);
      } 
 else if(my_payload==191)
      {
        digitalWrite(D4, LOW);
      }
 else if(my_payload==180)
      {
        digitalWrite(D5, HIGH);
      } 
 else if(my_payload==181)
      {
        digitalWrite(D5, LOW);
      }
 else if(my_payload==130)
      {
        digitalWrite(D6, HIGH);
      } 
 else if(my_payload==131)
      {
        digitalWrite(D6, LOW);
      }  
 else if(my_payload==210 or my_payload==220 or my_payload==280 or my_payload==270)
      {
        digitalWrite(D7, HIGH);
      }
 else if(my_payload==211 or my_payload==221 or my_payload==281 or my_payload==271)
      {
        digitalWrite(D7, LOW);
      } 
 else if(my_payload==240 or my_payload==230 or my_payload==250 )
      {
        digitalWrite(D0, HIGH);
      } 
  else if(my_payload==241 or my_payload==231 or my_payload==251 )
      {
        digitalWrite(D0, LOW);
      } 

   else if(my_payload==1 )
      {
        digitalWrite(D0, LOW);
        digitalWrite(D1, LOW);
        digitalWrite(D2, LOW);
        digitalWrite(D3, LOW);
        digitalWrite(D4, LOW);
        digitalWrite(D5, LOW);
        digitalWrite(D6, LOW);
        digitalWrite(D7, LOW);
      } 
      else if(my_payload==0 )
      {
        digitalWrite(D0, HIGH);
        digitalWrite(D1, HIGH);
        digitalWrite(D2, HIGH);
        digitalWrite(D3, HIGH);
        digitalWrite(D4, HIGH);
        digitalWrite(D5, HIGH);
        digitalWrite(D6, HIGH);
        digitalWrite(D7, HIGH);
      } 

}
// ROS nodes //
ros::NodeHandle nh;

// ROS topics object definitions PUBLISHERS
std_msgs::Int16 int_msg;

// ROS SUBSCRIBERS
ros::Subscriber<std_msgs::Int16> sub("light_status", &light_Callback );

void setup() {
  Serial.begin(115200);
  Serial.print("inside setup");
  if(DEBUG) Serial.begin(115200);
  Serial.print("setting up wifi");
  setupWiFi();
  delay(200);
//Ros objects constructors   
  nh.getHardware()->setConnection(server, serverPort);
  nh.initNode();
  nh.subscribe(sub);
// configure GPIO's and Servo
  pinMode(D1, OUTPUT); // 1,2EN aka D1 pwm left
  pinMode(D2, OUTPUT); // 3,4EN aka D2 pwm right
  pinMode(D3, OUTPUT); // 1A,2A aka D3
  pinMode(D4, OUTPUT); // 3A,4A aka D4
  pinMode(D5, OUTPUT); //  Left encoder
  pinMode(D6, OUTPUT); //  Right encoder
  pinMode(D7, OUTPUT); //  Ultrasonic Echo. D0 with 1k,2k voltage divisor
  pinMode(D0, OUTPUT); // Ultrasonic Trigger. D8 . Power Ultrasonic board with 5v.
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, HIGH);
  digitalWrite(D0, HIGH);
}


void loop() {

    //Serial.print("inside loop");
  if (nh.connected()) 
  {
    
    Serial.println("connected");
   
  } 
  else {
    if(DEBUG) Serial.println("Not Connected");
  }
  nh.spinOnce();
  delay(100);  // milliseconds
}
