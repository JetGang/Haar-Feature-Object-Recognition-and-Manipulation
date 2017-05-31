#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include <iostream>

#include <sstream>

using namespace std;

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
    double sp,sl,ef,wf,g;
    cout<<">>"<<endl;
    cin>>sp>>sl>>ef>>wf>>g;
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line. For programmatic
   * remappings you can use a different version of init() which takes remappings
   * directly, but for most command-line programs, passing argc and argv is the easiest
   * way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "arm_shoulder_pan_joint");
  ros::init(argc, argv, "arm_shoulder_lift_joint");
  ros::init(argc, argv, "arm_elbow_flex_joint");
  ros::init(argc, argv, "arm_wrist_flex_joint");
  ros::init(argc, argv, "gripper_joint");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;

  /**
   * The advertise() function is how you tell ROS that you want to
   * publish on a given topic name. This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing. After this advertise() call is made, the master
   * node will notify anyone who is trying to subscribe to this topic name,
   * and they will in turn negotiate a peer-to-peer connection with this
   * node.  advertise() returns a Publisher object which allows you to
   * publish messages on that topic through a call to publish().  Once
   * all copies of the returned Publisher object are destroyed, the topic
   * will be automatically unadvertised.
   *
   * The second parameter to advertise() is the size of the message queue
   * used for publishing messages.  If messages are published more quickly
   * than we can send them, the number here specifies how many messages to
   * buffer up before throwing some away.
   */
  ros::Publisher a_pub = n.advertise<std_msgs::Float64>("arm_shoulder_pan_joint/command", 1000);
  ros::Publisher b_pub = n.advertise<std_msgs::Float64>("arm_shoulder_lift_joint/command", 1000);
  ros::Publisher c_pub = n.advertise<std_msgs::Float64>("arm_elbow_flex_joint/command", 1000);
  ros::Publisher d_pub = n.advertise<std_msgs::Float64>("arm_wrist_flex_joint/command", 1000);
  ros::Publisher e_pub = n.advertise<std_msgs::Float64>("gripper_joint/command", 1000);

  ros::Rate loop_rate(1);

  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
  int count = 0;
  while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    std_msgs::Float64 msg_1;
    std_msgs::Float64 msg_2;
    std_msgs::Float64 msg_3;
    std_msgs::Float64 msg_4;
    std_msgs::Float64 msg_5; 

    //msg=l;
    msg_1.data = sp;
    msg_2.data = sl;
    msg_3.data = ef;
    msg_4.data = wf;
    msg_5.data = g;

    ROS_INFO("%f", msg_1.data);
    ROS_INFO("%f", msg_2.data);
    ROS_INFO("%f", msg_3.data);
    ROS_INFO("%f", msg_4.data);
    ROS_INFO("%f", msg_5.data);

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
    a_pub.publish(msg_1);
    b_pub.publish(msg_2);
    c_pub.publish(msg_3);
    d_pub.publish(msg_4);
    e_pub.publish(msg_5);

    ros::spinOnce();

    loop_rate.sleep();
    if(count>5){
    break;
    }
    ++count;
  }


  return 0;
}
