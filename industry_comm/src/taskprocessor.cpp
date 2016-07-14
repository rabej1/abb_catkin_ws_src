#include "ros/ros.h"
#include "industry_comm_msg/TaskProcessor.h"

#include <tf/transform_listener.h>

#include <actionlib/client/simple_action_client.h>

#include <ar_track_alvar_msgs/AlvarMarkers.h>
#include <visualization_msgs/Marker.h>

#include <tf/transform_datatypes.h>

std::vector<int> tagid;

class Processor {

protected:

	ros::NodeHandle nh_;
	ros::Subscriber sub;
	ros::ServiceServer service;
	std::string action_name_;
	tf::TransformListener listener;

public:

	Processor(std::string name):
		action_name_(name) {

		sub = nh_.subscribe("/visualization_marker", 100, &Processor::poseCB, this);
		service = nh_.advertiseService("TaskProcessor", &Processor::task, this);

		ros::AsyncSpinner spinner(1);
		spinner.start();
	}

	void poseCB(const visualization_msgs::Marker msg){
		if(msg.ns == "basic_shapes")
			tagid.push_back((int)msg.id);
	}






	bool task(industry_comm_msg::TaskProcessor::Request  &req,
			industry_comm_msg::TaskProcessor::Response &res)
	{
		//Go and get something
		if(req.get){
			ROS_WARN("This Robot is not able to move");
		}

		//Bring something
		if(req.bring){
			ROS_WARN("This Robot is not able to move");
		}

		//Roll the dice
		if(req.diceroll){
			ROS_WARN("This Robot is not able to roll the dice");
		}

		//Put item back into storage
		if(req.bringback){
			ROS_WARN("This Robot is not able to move");
		}

		res.success = true;
		return true;
	}

};

int main(int argc, char **argv)
{
	ros::init(argc, argv, "TaskProcessor");

	Processor task_processor(ros::this_node::getName());

	ros::spin();

	return 0;
}
