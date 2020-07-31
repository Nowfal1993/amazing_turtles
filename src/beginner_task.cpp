#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"


class NodeTalker
{
private:
    //The current nodeHandles
    //this-> = ros.NodeHandle();
    ros::NodeHandle n;
    //initialising the publisher
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
	
public:
	void run()
	{
        // Send messages in a loop
    	ros::Rate loop_rate(10);
		// int count = 0;
  		while (ros::ok())
  		{
			/**
		 	* This is a message object. You stuff it with data, and then publish it.
		 	*/
			std_msgs::String msg;

			std::stringstream ss;
			// ss << "Nowfal " << count;
			ss << "Nowfal ";
			msg.data = ss.str();

			//ROS_INFO("%s", msg.data.c_str());

			/**
		 	* The publish() function is how you send messages. The parameter
		 	* is the message object. The type of this object must agree with the type
		 	* given as a template parameter to the advertise<>() call, as was done
		 	* in the constructor above.
		 	*/
			chatter_pub.publish(msg);

			ros::spinOnce();

			loop_rate.sleep();
			// ++count;	
  		}
  	}

};
int main(int argc, char **argv){
    // Initialize ROS
    ros::init(argc, argv, "talker");// talker-> is the name of the rosnode, it will be replaced by the name of the node in th launch file if any

    // Create our controller object and run it
    auto node_tkr = NodeTalker();
    node_tkr.run();

    // And make good on our promise
    return 0;
}