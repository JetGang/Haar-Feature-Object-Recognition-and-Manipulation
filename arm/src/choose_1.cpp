#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include "std_msgs/Float64.h"
#include <iostream>

#include <sstream>
using namespace std;

int main(int argc, char **argv)
{
  double x_1,y_1,z_1,x_2,y_2,z_2,theta_1,theta_2;
  x_2=0;
  y_2=0;
  z_2=0;
  theta_1=0;
  theta_2=0;
  cout<<"object postion: "<<endl;
  cin>>x_1>>y_1>>z_1>>theta_1;
  cout<<"goal position: "<<endl;
  cin>>x_2>>y_2>>z_2>>theta_2;

  ros::init(argc, argv, "choose");

  
  ros::NodeHandle n;

  
  ros::Publisher start_pub = n.advertise<geometry_msgs::Point>("start", 1000);
  ros::Publisher end_pub = n.advertise<geometry_msgs::Point>("end", 1000);
  ros::Publisher rb_pub = n.advertise<std_msgs::Float64>("rotate_begin", 1000);
  ros::Publisher re_pub = n.advertise<std_msgs::Float64>("rotate_end", 1000);

  ros::Rate loop_rate(10);

  int count_1=0,count_2=0,count_3=0,count_4=0;

  while (ros::ok())
  { 
 
    geometry_msgs::Point msg_2;
    geometry_msgs::Point msg_4;
    std_msgs::Float64 msg_1;
    std_msgs::Float64 msg_3;
  
    msg_1.data=theta_1;
    msg_3.data=theta_2;
    msg_2.x=x_1;
    msg_2.y=y_1;
    msg_2.z=z_1;
    msg_4.x=x_2;
    msg_4.y=y_2;
    msg_4.z=z_2;

    for(int j=0; j<4; j++)
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
    ROS_INFO("%f", msg_2.x);
    ROS_INFO("%f", msg_2.y);
    ROS_INFO("%f", msg_2.z);

    start_pub.publish(msg_2);

    loop_rate.sleep();
    ++count_2;
    }
    }


    if(count_2>0)
    {
    for(int j=0; j<3; j++)
    {
    ROS_INFO("%f", msg_3.data);

    re_pub.publish(msg_3);

    loop_rate.sleep();
    ++count_3;
    }
    }

    if(count_3>2)
    {
    for(int j=0; j<2; j++)
    {
    ROS_INFO("%f", msg_4.x);
    ROS_INFO("%f", msg_4.y);
    ROS_INFO("%f", msg_4.z);

    end_pub.publish(msg_4);

    loop_rate.sleep();
    ++count_4;
    }
    }
    
    
    if(count_4>0)
   break;
    
    ros::spinOnce();

  }


  return 0;
}
