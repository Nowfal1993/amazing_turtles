#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Spawn.h"
#include "amazing_turtles/ninja_srv.h"


class Node_Seviceserver
{
	private:
		ros::NodeHandle n;
    	ros::Subscriber sub;
    	ros::Publisher pub;
    	ros::ServiceServer srv;

    	geometry_msgs::Twist msg;
    	//geometry_msgs::Twist msg_2;

    	bool service_bool;

	public:

		void Move_callback(const geometry_msgs::Twist vel_msg)
    	{
      		this->msg=vel_msg;
    	}

    	bool Service_callback(amazing_turtles::ninja_srv::Request & request, amazing_turtles::ninja_srv::Response& response)
   		{
	   		if(request.ctrl)
	   		{
		        this->service_bool = true;
		    }
		    else
		    {

		        this->service_bool = false ;
		    }

	      	return true;
    	}

		Node_Seviceserver()
		{
	        this->n = ros::NodeHandle();
	        this->sub = n.subscribe("keyboard/cmd_vel", 1000, &Node_Seviceserver::Move_callback, this );
	        this->pub =  n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);

	        this->srv = n.advertiseService("ninja_service", &Node_Seviceserver::Service_callback, this);
	        //this->service = n.advertiseService("ninja_service", &Turtle_Srv::Service_callback, this);
	        ros::Duration(1).sleep();
    	}

    	


    	void run()
    	{

	        ros::Rate loop_rate(100);

	        while (ros::ok())
	        {
	        	if(this->service_bool)
	        	{
	           		this->pub.publish(this->msg);
	           	}
	        	ros::spinOnce();
	            loop_rate.sleep();
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