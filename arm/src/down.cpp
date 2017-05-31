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
    signal_pub = n.advertise<std_msgs::Float64>("pickup_end/command", 1000);

    //Topic you want to subscribe
    
    d_sub = n.subscribe("down", 1, &SubscribeAndPublish::downcallback, this);

  }

  void downcallback(geometry_msgs::Point msg)
  {
    double D[1][3];
    std_msgs::Float64 msg_2;
    std_msgs::Float64 msg_3;
    std_msgs::Float64 msg_4;
    std_msgs::Float64 msg_5;
    std_msgs::Float64 signal;
    msg_2.data = msg.x;
    msg_3.data = msg.y;
    msg_4.data = msg.z;
    msg_5.data =1.57 ;
    signal.data = 0;
    ros::Rate loop_rate(5);
    int count_0 = 0,count_1=0,count_2=0;
    int i=0,j=0,k=0,l=0;
     while (ros::ok())
       {
       joint2_pub.publish(msg_2);
       ROS_INFO("%f", msg_2.data);
        loop_rate.sleep();
        ++k;
        if(k>3){
        break;
        }
       }

     while (ros::ok())
       {
       joint3_pub.publish(msg_3);
       joint4_pub.publish(msg_4);
       ROS_INFO("%f", msg_3.data);
       ROS_INFO("%f", msg_4.data);
        loop_rate.sleep();
        ++i;
        if(i>3)
        break;
       }

      int wait=0;
      while (ros::ok())
        {
      loop_rate.sleep();
       if(wait>6){
        break;
        }
        ++wait; 
       }
  /*        while (ros::ok())
       {
     
       joint2_pub.publish(msg_2);
       ROS_INFO("%f", msg_2.data);
        loop_rate.sleep();
        ++j;
        if(j>3)
        break;
       }
*/
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
    std_msgs::Float64 i_1;
    std_msgs::Float64 i_2;
    std_msgs::Float64 i_3;
    std_msgs::Float64 i_4;
   // i_2.data=0.4;
    i_2.data=1.05;
    i_3.data=-1.9;
    i_4.data=0.9;
  //  int count_0 = 0; 
     while (ros::ok())
       {
   //  joint2_pub.publish(i_2);
     joint2_pub.publish(i_2);
     joint3_pub.publish(i_3);
     joint4_pub.publish(i_4);
     ROS_INFO("%f", i_2.data);
     ROS_INFO("%f", i_3.data);
     ROS_INFO("%f", i_4.data);
     loop_rate.sleep();
     ++count_0;
       if(count_0>8){
        break;
        }
       }
    int time=0;
    while (ros::ok())
        {
   loop_rate.sleep();
       if(time>2){
        break;
        }
        ++time; 
       }
     i_1.data=-1.57;


     while (ros::ok())
       {
     joint1_pub.publish(i_1);
   //  joint2_pub.publish(i_2);
     ROS_INFO("%f", i_1.data);
   //  ROS_INFO("%f", i_2.data);
     loop_rate.sleep();
     ++count_2;
       if(count_2>10){
     signal_pub.publish(signal);
     ROS_INFO("%f", signal.data);
        break;
        }
       }

  }

private:
  ros::NodeHandle n;
  ros::Publisher joint1_pub;
  ros::Publisher joint2_pub; 
  ros::Publisher joint3_pub;
  ros::Publisher joint4_pub;
  ros::Publisher joint5_pub;
  ros::Publisher signal_pub;
// ros::Subscriber e_sub;
  ros::Subscriber d_sub;

};//End of class SubscribeAndPublish

int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "down");

  //Create an object of class SubscribeAndPublish that will take care of everything
  SubscribeAndPublish SAPObject;

  ros::spin();

  return 0;
}
