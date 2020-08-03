#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Spawn.h"

geometry_msgs::Twist vel_msg;

void callback(const geometry_msgs::Twist & msg)
{
	vel_msg.linear.x = msg.linear.x;
	vel_msg.linear.y = msg.linear.y;
	vel_msg.linear.z = msg.linear.z;
	vel_msg.angular.x = msg.angular.x;
	vel_msg.angular.y = msg.angular.y;
	vel_msg.angular.z = msg.angular.z;
}


class Node_Seviceserver
{
	private:
		ros::NodeHandle n; 
    	//initialising the publisher
		ros::Publisher pub = n.advertise<std_msgs::String>("turtle1/cmd_vel", 1000);    	
		ros::Subscriber sub = n.subscribe("turtle_server/cmd_vel", 1000, callback);

	public:
    	//TurtleController()
    	//{
        	// Initialize ROS
        	//ros::NodeHandle n;

        	// Create a publisher object, able to push messages
        	//cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000); //1000 means we are creating a buffer for 1000 messages
   		 //}



    	void run()
    	{
	        // Send messages in a loop
	        ros::Rate loop_rate(10);
	        geometry_msgs::Twist msg;
	        while (ros::ok())
	        {
	        	this->pub.publish(msg);
	            ros::spinOnce();

	            loop_rate.sleep(); // this is basically how we  defining the rate
	        }	
    	}



};





int main(int argc, char **argv){
    // Initialize ROS
    ros::init(argc, argv, "ninja_server");// talker-> is the name of the rosnode, it will be replaced by the name of the node in th launch file if any

    // Create our controller object and run it
    auto ninja_con = Node_Seviceserver();
    ninja_con.run();

    // And make good on our promise
    return 0;
}