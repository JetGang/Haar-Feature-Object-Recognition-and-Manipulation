#include <ros/ros.h>
#include "geometry_msgs/Point.h"
#include "std_msgs/Float64.h"

class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    //Topic you want to publish
    joint1_pub = n.advertise<std_msgs::Float64>("arm_shoulder_pan_joint/command",1000);
    joint2_pub = n.advertise<std_msgs::Float64>("arm_shoulder_lift_joint/command", 1000);
    joint3_pub = n.advertise<std_msgs::Float64>("arm_elbow_flex_joint/command", 1000);
    joint4_pub = n.advertise<std_msgs::Float64>("arm_wrist_flex_joint/command", 1000);
    joint5_pub = n.advertise<std_msgs::Float64>("gripper_joint/command", 1000);
    std_msgs::Float64 i_1;
    std_msgs::Float64 i_2;
    std_msgs::Float64 i_3;
    std_msgs::Float64 i_4;
    std_msgs::Float64 i_5;
    i_1.data=0.0;
    i_2.data=1.05;
    i_3.data=1;
    i_4.data=-1.57;
    i_5.data=1.57;
    int count_0 = 0;
    ros::Rate loop_rate(2);
     while (ros::ok())
       {
     joint1_pub.publish(i_1);
     joint2_pub.publish(i_2);
     joint3_pub.publish(i_3);
     joint4_pub.publish(i_4);
     joint5_pub.publish(i_5);
     ROS_INFO("%f", i_1.data);
     ROS_INFO("%f", i_2.data);
     ROS_INFO("%f", i_3.data);
     ROS_INFO("%f", i_4.data);
     ROS_INFO("%f", i_5.data);
     loop_rate.sleep();
     ++count_0;
       if(count_0>3){
        break;
        }
       }

    //Topic you want to subscribe
    b_sub = n.subscribe("rotate_begin", 1, &SubscribeAndPublish::rbcallback, this);
    u_sub = n.subscribe("up", 1, &SubscribeAndPublish::upcallback, this);
    e_sub = n.subscribe("rotate_end",1,&SubscribeAndPublish::recallback,this);

  }
 
  void recallback(std_msgs::Float64 msg)
   {
    std_msgs::Float64 msg_e;
    
    msg_e.data = msg.data;
    ros::Rate loop_rate(10);
    int i=0;
    while(ros::ok())
    {
    joint1_pub.publish(msg_e);
    ROS_INFO("%f", msg_e.data);
    loop_rate.sleep();
    ++i;
    if(i>3)
    break;
    }
   }

 void rbcallback(std_msgs::Float64 msg)
  {
    double U[1][3];
    std_msgs::Float64 msg_b;

    msg_b.data = msg.data;

    ros::Rate loop_rate(10);
    int count_0 = 0,count_1=0;
    int i=0,j=0,k=0,l=0;
      while (ros::ok())
       {
     
       joint1_pub.publish(msg_b);
       ROS_INFO("%f", msg_b.data);
        loop_rate.sleep();
        ++j;
        if(j>3)
        break;
       }
    int time=0;
    while (ros::ok())
        {
    loop_rate.sleep();
       if(time>8){
        break;
        }
        ++time; 
       }
  }


  void upcallback(geometry_msgs::Point msg)
  {
    double U[1][3];
    std_msgs::Float64 msg_2;
    std_msgs::Float64 msg_3;
    std_msgs::Float64 msg_4;
    std_msgs::Float64 msg_5;
    msg_2.data = msg.x;
    msg_3.data = msg.y;
    msg_4.data = msg.z;
    msg_5.data =1.1 ;
    ros::Rate loop_rate(5);
    int count_0 = 0,count_1=0;
    int i=0,j=0,k=0,l=0;
     while (ros::ok())
       {
       joint2_pub.publish(msg_2);
       ROS_INFO("%f", msg_2.data);
        loop_rate.sleep();
        ++i;
        if(i>3)
        break;        
       }

      while (ros::ok())
       {
     
       joint3_pub.publish(msg_3);
       joint4_pub.publish(msg_4);
       ROS_INFO("%f", msg_3.data);
       ROS_INFO("%f", msg_4.data);
        loop_rate.sleep();
        ++j;
        if(j>3)
        break;
       }
 /*    while (ros::ok())
       {
       joint4_pub.publish(msg_4);
       ROS_INFO("%f", msg_4.data);
        loop_rate.sleep();
        ++k;
        if(k>3){
        break;
        }
       }
 */
     
     int wait=0;
    while (ros::ok())
        {
   loop_rate.sleep();
       if(wait>6){
        break;
        }
        ++wait; 
       }

     while (ros::ok())
       {
       joint5_pub.publish(msg_5);
       ROS_INFO("%f", msg_5.data);
        loop_rate.sleep();
        ++l;
        if(l>3){
        break;
        }
       }
    std_msgs::Float64 i_2;
    std_msgs::Float64 i_3;
    std_msgs::Float64 i_4;
    std_msgs::Float64 i_5;
   // i_2.data=0.4;
    i_3.data=1;
    i_4.data=-1.57;
  //  int count_0 = 0; 
     while (ros::ok())
       {
   //  joint2_pub.publish(i_2);
     joint3_pub.publish(i_3);
     joint4_pub.publish(i_4);
   //  ROS_INFO("%f", i_2.data);
     ROS_INFO("%f", i_3.data);
     ROS_INFO("%f", i_4.data);
     loop_rate.sleep();
     ++count_0;
       if(count_0>8){
        break;
        }
       }
    i_2.data=1.05;
  //  i_5.data=1.57;
     while (ros::ok())
       {
     joint2_pub.publish(i_2);
  //   joint5_pub.publish(i_5);
     ROS_INFO("%f", i_2.data);
   //  ROS_INFO("%f", i_5.data);
     loop_rate.sleep();
     ++count_1;
       if(count_1>2){
        break;
        }
       }
    int time=0;
    while (ros::ok())
        {
   loop_rate.sleep();
       if(time>8){
        break;
        }
        ++time; 
       }
  }

private:
  ros::NodeHandle n;
  ros::Publisher joint1_pub;
  ros::Publisher joint2_pub; 
  ros::Publisher joint3_pub;
  ros::Publisher joint4_pub;
  ros::Publisher joint5_pub;
  ros::Subscriber e_sub;
  ros::Subscriber b_sub;
  ros::Subscriber u_sub;

};//End of class SubscribeAndPublish

int main(int argc, char **argv)
{
  // int w=0;
  //Initiate ROS
  ros::init(argc, argv, "up");

  //Create an object of class SubscribeAndPublish that will take care of everything
  SubscribeAndPublish SAPObject;

  ros::spin();

  return 0;
}
