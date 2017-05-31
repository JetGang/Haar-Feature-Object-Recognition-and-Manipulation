//This main function of this node is subscribe topics from other parts of whole system, 
//and then publish to position data to follow-up inverse kinematic node.

#include <ros/ros.h>
#include "geometry_msgs/Point.h"
#include "std_msgs/Float64.h"

class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    //Topic you want to publish

     start_pub = n.advertise<geometry_msgs::Point>("start", 1000);
     end_pub = n.advertise<geometry_msgs::Point>("end", 1000);
     rb_pub = n.advertise<std_msgs::Float64>("rotate_begin", 1000);
     re_pub = n.advertise<std_msgs::Float64>("rotate_end", 1000);
     signal_pub = n.advertise<std_msgs::Float64>("pickup_end/command", 1000);

    //Topic you want to subscribe
    choose_sub = n.subscribe("choose_begin", 1, &SubscribeAndPublish::choosecallback, this);


  }
 
  void choosecallback(geometry_msgs::Point msg)
   {
    geometry_msgs::Point msg_up;
    geometry_msgs::Point msg_down;
    std_msgs::Float64 msg_1;
    std_msgs::Float64 msg_3;
    std_msgs::Float64 signal;

    //pick up position
    msg_up.x=msg.x;// distance between object and manipulator
    msg_up.y=msg.y;//height of object
    msg_up.z=0; 
    
    //place position
    msg_down.x=42; 
    msg_down.y=0;
    msg_down.z=0;
    
    msg_1.data=msg.z; // up rotation for shoulder
    msg_3.data=0.0; //down rotation for shoulder
    signal.data=1; //signal for starting picking and placing

    ros::Rate loop_rate(10);

  int count_1=0,count_2=0,count_3=0,count_4=0;

  while (ros::ok())
     { 
    ROS_INFO("%f", signal.data);

    signal_pub.publish(signal);
 
    ROS_INFO("%f", msg_1.data);

    rb_pub.publish(msg_1);

    loop_rate.sleep();
    count_1++;
    if(count_1>3)
    break;
    
    }
  while (ros::ok())
     {   
    ROS_INFO("%f", msg_up.x);
    ROS_INFO("%f", msg_up.y);
    ROS_INFO("%f", msg_up.z);

    start_pub.publish(msg_up);

    loop_rate.sleep();
    count_2++;
    if(count_2>0)
    break;
    }

  while (ros::ok())
     { 
    ROS_INFO("%f", msg_3.data);

    re_pub.publish(msg_3);

    loop_rate.sleep();
    count_3++;
    if(count_3>2)
    break;  
    }

  while (ros::ok())
     {

    ROS_INFO("%f", msg_down.x);
    ROS_INFO("%f", msg_down.y);
    ROS_INFO("%f", msg_down.z);

    end_pub.publish(msg_down);

    loop_rate.sleep();
    ++count_4;
    if(count_4>1)
    break;
 }   

 }

 

private:
  ros::NodeHandle n;
  ros::Publisher start_pub;
  ros::Publisher end_pub; 
  ros::Publisher rb_pub;
  ros::Publisher re_pub;
  ros::Publisher signal_pub;
  ros::Subscriber choose_sub;


};//End of class SubscribeAndPublish

int main(int argc, char **argv)
{
  // int w=0;
  //Initiate ROS
  ros::init(argc, argv, "choose");

  //Create an object of class SubscribeAndPublish that will take care of everything
  SubscribeAndPublish SAPObject;

  ros::spin();

  return 0;
}
