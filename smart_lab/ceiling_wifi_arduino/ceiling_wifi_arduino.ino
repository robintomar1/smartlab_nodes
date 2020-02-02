
#include <ESP8266WiFi.h>
#include <ros.h>
#include <std_msgs/Int16.h>


// Init constants and global variables

#define DEBUG 1

// WiFi configuration. Replace '***' with your data

const char* ssid = "robot_r";
const char* password = "robin7624";
IPAddress server(192,168,43,94);      // Set the rosserial socket ROSCORE SERVER IP address
const uint16_t serverPort = 11411;    // Set the rosserial socket server port


// Functions definitions //

void setupWiFi() {   
  WiFi.disconnect();// connect to ROS server as as a client
  WiFi.mode(WIFI_STA); 
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
std_msgs::Int16 int_msg_1;
std_msgs::Int16 int_msg_2;
std_msgs::Int16 int_msg_3;
std_msgs::Int16 int_msg_4;
std_msgs::Int16 int_msg_5;
std_msgs::Int16 int_msg_6;
std_msgs::Int16 int_msg_7;


// ROS nodes //
ros::NodeHandle nh;

// ROS topics object definitions PUBLISHERS
ros::Publisher pub_value_1("sensor_1_value", &int_msg_1);
ros::Publisher pub_value_2("sensor_2_value", &int_msg_2);
ros::Publisher pub_value_3("sensor_3_value", &int_msg_3);
ros::Publisher pub_value_4("sensor_4_value", &int_msg_4);
ros::Publisher pub_value_5("sensor_5_value", &int_msg_5);
ros::Publisher pub_value_6("sensor_6_value", &int_msg_6);
ros::Publisher pub_value_7("sensor_7_value", &int_msg_7);


void (*resetFunc)(void)=0;
// ROS SUBSCRIBERS

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
  nh.advertise(pub_value_1);
  nh.advertise(pub_value_2);
  nh.advertise(pub_value_3);
  nh.advertise(pub_value_4);
  nh.advertise(pub_value_5);
  nh.advertise(pub_value_6);
  nh.advertise(pub_value_7);

 


// configure GPIO's and Servo
  pinMode(D10, INPUT); // 1,2EN aka D1 pwm left
  pinMode(D11, INPUT); // 3,4EN aka D2 pwm right
  pinMode(D12, INPUT); // 1A,2A aka D3
  pinMode(D13, INPUT); // 3A,4A aka D4
  pinMode(D4, INPUT); //  Left encoder
  pinMode(A0, INPUT); //  Left encoder
  
 digitalWrite(D10,LOW);
 digitalWrite(D11,LOW);
 digitalWrite(D12,LOW);
 digitalWrite(D13,LOW);
 digitalWrite(D4,LOW);
}


void loop() {
  if ( WiFi.status() ==  WL_CONNECTED ) 
  {
    // WiFi is UP,  do what ever
     Serial.print(" wifi connected ");
  if (nh.connected()) 
  {
    
    Serial.println(" node connected ");
    int_msg_1.data = digitalRead(D13);
    pub_value_1.publish(&int_msg_1);
    int_msg_2.data= digitalRead(D12);
    pub_value_2.publish(&int_msg_2); 
    int_msg_3.data= digitalRead(D11);
    pub_value_3.publish(&int_msg_3);
    int_msg_4.data= digitalRead(D10); 
    pub_value_4.publish(&int_msg_4); 
    int_msg_5.data= digitalRead(D4);
    pub_value_5.publish(&int_msg_5);

    int_msg_7.data = analogRead(A0);
    pub_value_7.publish(&int_msg_7);   

   
  } 
  else {
    if(DEBUG) Serial.println("Node not Connected");
  }
  }
  else
  {
  Serial.println("calling reset function");
  resetFunc();
  }
 
  nh.spinOnce();
  delay(1000);  // milliseconds changed to 1000 from 300
}
