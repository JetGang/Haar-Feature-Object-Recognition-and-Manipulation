#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include <iostream>

#include <sstream>
#define PI 3.14159265
using namespace std;

int main(int argc, char **argv)
{
  double x_1,x_2;
  x_1=0;
  x_2=0;

  cout<<"rotate_begin"<<endl;
  cin>>x_1;
  cout<<"rotate_end: "<<endl;
  cin>>x_2;

  ros::init(argc, argv, "rotate");

  
  ros::NodeHandle n;

  
  ros::Publisher rb_pub = n.advertise<std_msgs::Float64>("rotate_begin", 1000);
  ros::Publisher re_pub = n.advertise<std_msgs::Float64>("rotate_end", 1000);

  ros::Rate loop_rate(10);

    int count_1=0;
    int count_2=0;

  while (ros::ok())
  { 
 
    std_msgs::Float64 msg_1;
    std_msgs::Float64 msg_2;
  
    msg_1.data=x_1;
    msg_2.data=x_2;

    for(int j=0; j<1; j++)
    {
    ROS_INFO("%f", msg_1.data);

    rb_pub.publish(msg_1);

    loop_rate.sleep();
    ++count_1;
    }
    
    if(count_1>3)
    {
    for(int j=0; j<1; j++)
    {
    ROS_INFO("%f", msg_2.data);

    re_pub.publish(msg_2);

    loop_rate.sleep();
    ++count_2;
    }
    }

    
    if(count_2>0)
   break;
    
    ros::spinOnce();

  }


  return 0;
}
