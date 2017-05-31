import rospy
from geometry_msgs.Twist import Twist

def ping():
    pub = rospy.Publisher('/RosAria/cmd_vel', String, queue_size=10)
    rospy.init_node('ping', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        velocity.linear.x=0;
        velocity.linear.y=0;
        velocity.linear.z=0;
        velocity.angular.x=0;
        velocity.angular.y=0;
        velocity.angular.z=0;
        rospy.loginfo(velocity)
        pub.publish(velocity)
        rate.sleep()

if __name__ == '__main__':
    try:
        ping()
    except rospy.ROSInterruptException:
        pass
