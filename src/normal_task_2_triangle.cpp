#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include "turtlesim/Spawn.h"
#include <math.h>




ros::Publisher velocity_publisher;
ros::Subscriber pose_subscriber;
turtlesim::Pose turtlesim_pose;
//the name of the turtle we are controlling
std::string turtle_name;



//callback function for the pose
void poseCallback(const turtlesim::Pose::ConstPtr & pose_message)
{
	turtlesim_pose.x = pose_message->x;
	turtlesim_pose.y = pose_message->y;
	turtlesim_pose.theta = pose_message->theta;
}

//function to find the distance between two points
double getDistance(double x1, double y1, double x2, double y2)
{
	double distance_cal = sqrt(pow((x1-x2),2) + pow((y1-y2),2));
	return distance_cal;
}

//function to find the angle between two points
double calculateAngle(turtlesim::Pose pose_1, turtlesim::Pose pose_2)
{
	double relative_angle = atan2(pose_2.y - pose_1.y,  pose_2.x - pose_1.x);
	return relative_angle;
}

//function to go the three vertices of the triangle(arguments are the 3 poses)
void moveGoal(turtlesim::Pose goal_pose , turtlesim::Pose goal_pose_2, turtlesim::Pose initial_pose)
{
	geometry_msgs::Twist vel_msg;

	ros::Rate loop_rate(30);

	double current_angle = 0.0;
	double angular_speed;

	// starting the loop
	while (ros::ok())
    {

	//########################### first side ##################

    	//rotating to the first position

		do
		{
			//defining a propotional controller
			//the erros is the angle between the next position and the current turtle pose
			//the kp is given by trial and error

			// the loop should continue until the differnece between the turtlesim.pose.theta and the angle between 
			// the current position and the next postion approaches the threashold(0.01)
			vel_msg.angular.z = 0.1*calculateAngle(turtlesim_pose, goal_pose);

			velocity_publisher.publish(vel_msg);
	    
	    	ros::spinOnce();
			loop_rate.sleep();
		}while(abs(turtlesim_pose.theta - calculateAngle(initial_pose, goal_pose)) > 0.01);
		

		vel_msg.linear.x = 0.0;
		vel_msg.angular.z = 0.0;
		velocity_publisher.publish(vel_msg);


		//moving to the first position.  
		//the loop should continue untill the distance between the current turtlesim.pose and the goal pose
		do
		{
			// define velocity commands
			vel_msg.linear.x = 0.5;
			vel_msg.angular.z = 0;

			

			velocity_publisher.publish(vel_msg);

			ros::spinOnce();
			loop_rate.sleep();

		}while(abs(turtlesim_pose.x-goal_pose.x) > 0.02 &&  abs(turtlesim_pose.y - goal_pose.y) > 0.02);

		vel_msg.linear.x = 0;
		vel_msg.angular.z = 0;

		velocity_publisher.publish(vel_msg);


		//########################### second side ##################

		//rotating to second position
		
		//defining a propotional controller
		//the erros is the angle between the next position and the current turtle pose
		//the kp is given by trial and error

		// the loop should continue until the differnece between the turtlesim.pose.theta and the angle between 
		// the current position and the next postion approaches the threashold(0.01)

		do
		{

			vel_msg.angular.z = 0.4*calculateAngle(turtlesim_pose, goal_pose_2);

			velocity_publisher.publish(vel_msg);
	
	    	ros::spinOnce();
			loop_rate.sleep();
		}while(abs(turtlesim_pose.theta - calculateAngle(goal_pose, goal_pose_2)) > 0.1);


		//}while(current_angle < relative_angle);

		vel_msg.linear.x = 0.0;
		vel_msg.angular.z = 0.0;
		velocity_publisher.publish(vel_msg);

		//moving to the second position
		do
		{
			vel_msg.linear.x = 0.25;
			vel_msg.angular.z = 0;

			velocity_publisher.publish(vel_msg);

			ros::spinOnce();
			loop_rate.sleep();

		}while(abs(turtlesim_pose.x-goal_pose_2.x) > 0.02 && abs(turtlesim_pose.y - goal_pose_2.y) > 0.02);
		//}while(getDistance(turtlesim_pose.x , turtlesim_pose.y,  goal_pose.x, goal_pose.y)< 0.1);
		vel_msg.linear.x = 0;
		vel_msg.angular.z = 0;


		velocity_publisher.publish(vel_msg);

		
		//########################### third side ##################

		//rotating to the third position

		//defining a propotional controller
		//the erros is the angle between the next position and the current turtle pose
		//the kp is given by trial and error

		// the loop should continue until the differnece between the turtlesim.pose.theta and the angle between 
		// the current position and the next postion approaches the threashold(0.01)

		do
		{
			vel_msg.angular.z = 0.4*calculateAngle(turtlesim_pose, initial_pose);
			velocity_publisher.publish(vel_msg);
	    
	    	ros::spinOnce();
			loop_rate.sleep();
		}while(abs(turtlesim_pose.theta - calculateAngle(goal_pose_2, initial_pose)) > 0.01);


		vel_msg.linear.x = 0.0;
		vel_msg.angular.z = 0.0;
		velocity_publisher.publish(vel_msg);


		//moving to the initial position
		//the loop should continue untill the distance between the current turtlesim.pose and the goal pose

		do
		{
			// define velocity commands
			vel_msg.linear.x = 0.25;
			vel_msg.angular.z = 0;

			
			velocity_publisher.publish(vel_msg);

			ros::spinOnce();
			loop_rate.sleep();

		}while(abs(turtlesim_pose.x-initial_pose.x) > 0.02 &&  abs(turtlesim_pose.y - initial_pose.y) > 0.02);
		
		vel_msg.linear.x = 0;
		vel_msg.angular.z = 0;


		velocity_publisher.publish(vel_msg);

		}

}

int main(int argc, char **argv){
    // Initialize ROS
    ros::init(argc, argv, "talker");// talker-> is the name of the rosnode, it will be replaced by the name of the node in th launch file if any

    ros::NodeHandle n; 

    velocity_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);

    pose_subscriber = n.subscribe("/turtle1/pose", 10, poseCallback);

    //ros::Rate loop_rate(10);

    turtlesim::Pose goal_pose;
    goal_pose.x = 3;
    goal_pose.y =  3;
    goal_pose.theta = 0;

    turtlesim::Pose goal_pose_2;
    goal_pose_2.x = 7;
    goal_pose_2.y =  1;
    goal_pose_2.theta = 0;

    turtlesim::Pose initial_pose;
    initial_pose.x = 5.544444561;
    initial_pose.y = 5.544444561;
    initial_pose.theta = 0;

    moveGoal(goal_pose, goal_pose_2, initial_pose);

    return 0;
}
