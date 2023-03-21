 /* 
 * rosserial Ultrasound Example
 * 
 * This example is for the Maxbotix Ultrasound rangers.
 */
 
#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>

ros::NodeHandle  nh;

sensor_msgs::Range range_msg;
ros::Publisher pub_range( "/ultrasound", &range_msg);

const unsigned int   TRIG_PIN=8;
const unsigned int ECHO_PIN=5;
float duration=0;
float  distance;
char frameid[] = "/ultrasound";

float getRange_Ultrasound(int pin_num){
  return analogRead(pin_num)/322.519685;   // (0.0124023437 /4) ; //cvt to meters
}

void setup()
{
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  nh.initNode();
  nh.advertise(pub_range);
  
  
  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id =  frameid;
  range_msg.field_of_view = 0.1;  // fake
  range_msg.min_range = 0.0;
  range_msg.max_range = 6.47;
   
  
}

long range_time=0;
 

void loop()
{
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
    range_time =  millis() + 100;
  
  
  nh.spinOnce();
  delay(100);
}
