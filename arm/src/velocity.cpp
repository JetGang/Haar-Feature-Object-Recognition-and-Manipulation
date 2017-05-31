#include <ros/ros.h>
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Float64.h"

 std_msgs::Float64 msg_5;
class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    //Topic you want to publish
    mobile_pub = n.advertise<geometry_msgs::Twist>("/RosAria/cmd_vel",1000);

    geometry_msgs::Twist twist;
    twist.linear.x=0;
    twist.linear.y=0;
    twist.linear.z=0;
    twist.angular.x=0;
    twist.angular.y=0;
    twist.angular.z=0;
    ros::Rate loop_rate(2);
     while (ros::ok())
       {
     mobile_pub.publish(twist);

     ROS_INFO("%f", twist.linear.x);
     ROS_INFO("%f", twist.linear.y);
     ROS_INFO("%f", twist.linear.z);
     ROS_INFO("%f", twist.angular.x);
     ROS_INFO("%f", twist.angular.y);
     ROS_INFO("%f", twist.angular.z);

     loop_rate.sleep();
        break;
       }

    //Topic you want to subscribe
    pose_sub = n.subscribe("pose_data", 1, &SubscribeAndPublish::mcallback, this);


  }
 
  void mcallback(geometry_msgs::Twist msg)
   {
    geometry_msgs::Twist msg_1;
    
    msg_1.linear.x = msg.linear.x;
    msg_1.linear.y = msg.linear.y;
    msg_1.linear.z = msg.linear.z;
    msg_1.angular.x=msg.angular.x;
    msg_1.angular.y=msg.angular.y;
    msg_1.angular.z=msg.angular.z;
    if(msg_1.angular.x>0)
    {
      msg_1.angular.z=-msg.angular.z;
    }
    ros::Rate loop_rate(10);
    int i=0;
    while(ros::ok())
    {
    mobile_pub.publish(msg_1);
     ROS_INFO("%f", msg_1.linear.x);
     ROS_INFO("%f", msg_1.linear.y);
     ROS_INFO("%f", msg_1.linear.z);
     ROS_INFO("%f", msg_1.angular.x);
     ROS_INFO("%f", msg_1.angular.y);
     ROS_INFO("%f", msg_1.angular.z);
    loop_rate.sleep();
    i++;
    if(i>0)
    break;
    }
   }

private:
  ros::NodeHandle n;
  ros::Publisher mobile_pub;
  ros::Subscriber pose_sub;

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
