 /* 
 * rosserial with arduino and Ultrasound Sensor SRF05 Exemple
 * 
 * Writting by chiha_wissem
 * 
 * !!!pin OUT of the sensor is not wired to the arduino !!!
 * 
 */
//include build-in libraries

#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>   //specific ros-arduino library for range sensors 

//create a ros node handler named nh
ros::NodeHandle  nh;

//
sensor_msgs::Range range_msg;
ros::Publisher pub_range( "/ultrasound", &range_msg);

const unsigned int   TRIG_PIN=8;  //digital pin 8 
const unsigned int ECHO_PIN=5;    //digital pin 5
float duration=0;
float  distance;
char frameid[] = "/ultrasound";

 

void setup()
{
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  nh.initNode();
  nh.advertise(pub_range);
  
  //defin static parameters of the range_msgs message 
  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id =  frameid;
  range_msg.field_of_view = 0.1;   
  range_msg.min_range = 0.0;        //minimun distance mesured 
  range_msg.max_range = 6.47;       //maximum distance mesured 
   
  
}
//time scrolling variable
long range_time=0;
 

void loop()
{ 
 //first send one pulse to the trig pin of the sensor (>10 microseconds)
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
 duration= pulseIn(ECHO_PIN, HIGH); 
 distance= duration/29/2;

    range_msg.range =  distance;
    range_msg.header.stamp = nh.now();
    pub_range.publish(&range_msg);
    //update time : print range every 0.1 second  
    range_time =  millis() + 100;
  
  
  nh.spinOnce();
  delay(100);
}
