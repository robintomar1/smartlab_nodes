///////////////////////////////////////////////////////////////////////////////////////////
//
// Wifi ROS Car with ESP8266 and ultrasonic range servo. v3.2 09:50 15-Jun-2017
// Implements following Ros objects:
//
//   - odom.    Using simple wheel encoders (no quadrature)
//   - tf.      Defines 3 frames, Scenario, Car and Servo Range
//   - cmd_vel. differential_drive Twist commands for translation & rotation
//   - Range    To display in rviz walls and obstacle SLAM
//
// Includes PID_library from Brett Beauregard https://github.com/br3ttb/Arduino-PID-Library
// to control wheel speeds at wished velocity from Twist. There is a separated PID_test
// utility to calibrate Kp, Ki and Kd with your specific car configuration.
//
// Includes Servo library. Direct ultrasonic calculation of Range
// Includes rosserial compatibility via Wifi that can be activated with:
//
//   $ rosrun rosserial_python serial_node.py tcp
//
// Car can be monitored and managed within ROS with:
// 
//   $rosrun rviz rviz
//
// Find last versions at:
// https://github.com/agnunez/espros.git
//
// MIT License 2017 Agustin Nunez
//////////////////////////////////////////////////////////////////////////////////////////////

#include <ESP8266WiFi.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float64.h>
#include <ros/time.h>


// Init constants and global variables

#define DEBUG 1
#define TRIGGER D8  // ultrasonic trigger pin
#define ECHO    D0  // ultrasonic echo pin  (!!Note: use 5v Vcc on ultrasonic board & a 2k,1k divider for ECHO GPIO protection)


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
void command_Callback(const std_msgs::String& received_msg)
{   
      String my_payload;
      my_payload=received_msg.data;
      
  if (my_payload=="on_one")
      {
        digitalWrite(D3, HIGH);
      }
 else if(my_payload=="off_one")
      {
        digitalWrite(D3, LOW);
      } 
 else if(my_payload=="on_two")
      {
        digitalWrite(D4, HIGH);
      } 
 else if(my_payload=="off_two")
      {
        digitalWrite(D4, LOW);
      } 
        
}
// ROS nodes //
ros::NodeHandle nh;

// ROS topics object definitions PUBLISHERS
std_msgs::String str_msg;
std_msgs::Int16 int_msg;

ros::Publisher pub_value("sensor_value", &int_msg);


// ROS SUBSCRIBERS
ros::Subscriber<std_msgs::String> Sub("node_command", &command_Callback );

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
  nh.advertise(pub_value);
  nh.subscribe(Sub);
// configure GPIO's and Servo
  pinMode(A0, INPUT); // Ultrasonic Trigger
//  pinMode(D1, OUTPUT); // 1,2EN aka D1 pwm left
//  pinMode(D2, OUTPUT); // 3,4EN aka D2 pwm right
//  pinMode(D3, OUTPUT); // 1A,2A aka D3
//  pinMode(D4, OUTPUT); // 3A,4A aka D4
//  pinMode(D5, INPUT); //  Left encoder
//  pinMode(D6, INPUT); //  Right encoder
//  pinMode(ECHO, INPUT); //  Ultrasonic Echo. D0 with 1k,2k voltage divisor
//  pinMode(TRIGGER, OUTPUT); // Ultrasonic Trigger. D8 . Power Ultrasonic board with 5v.
}

// odometry configuration
ros::Time current_time = nh.now();
ros::Time last_time = current_time;

void loop() {
    //Serial.print("inside loop");
  if (nh.connected()) {
    current_time = nh.now();
    int_msg.data= analogRead(A0);
    Serial.println(int_msg.data);
    pub_value.publish(&int_msg);
  } else {
    if(DEBUG) Serial.println("Not Connected");
  }
  nh.spinOnce();
  // Loop aprox. every  
  delay(1000);  // milliseconds
}
