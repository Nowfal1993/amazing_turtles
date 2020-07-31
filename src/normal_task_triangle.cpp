#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"

ros::Publisher velocity_publisher;
ros::Subscriber pose_subscriber;
turtlesim::Pose turtlesim_pose;

double getDistance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow((x1-x2),2) + pow((y1-y2),2));
}

void moveGoal(turtlesim::Pose goal_pose)
{
	geometry_msgs::Twist vel_msg;

	ros::Rate loop_rate(10);

	do
	{
		// define velocity commands
		vel_msg.linear.x = 2.0;
		vel_msg.angular.z = 0;

		vel_msg.angular.z = atan2(goal_pose.y - turtlesim_pose.y, goal_pose.x - turtlesim_pose.x);

		velocity_publisher.publish(vel_msg);

		ros::spinOnce();
		loop_rate.sleep();
	}while(getDistance(turtlesim_pose.x , turtlesim_pose.y,  goal_pose.x, goal_pose.y)==0);
	std::stringstream ss;
	// ss << "Nowfal " << count;
	ss << "End of Goal";
	vel_msg.linear.x = 0.0;
	vel_msg.angular.z = 0;
	velocity_publisher.publish(vel_msg);

}

int main(int argc, char **argv){
    // Initialize ROS
    ros::init(argc, argv, "move2goal");// talker-> is the name of the rosnode, it will be replaced by the name of the node in th launch file if any

    ros::NodeHandle n; 

    velocity_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
    ros::Rate loop_rate(10);

    turtlesim::Pose goal_pose;
    goal_pose.x = 1;
    goal_pose.y = 2;
    goal_pose.theta = 0;


    moveGoal(goal_pose);

    loop_rate.sleep();

    ros::spin();

    // And make good on our promise
    return 0;
}
