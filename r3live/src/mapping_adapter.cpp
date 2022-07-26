#include "mapping_adapter.hpp"

void MappingAdapter::start() {
    std_msgs::String algorithm_status;
    algorithm_status.data = "Success";

    while (RAWDATASTARTED != true) {
        algorithm_started_pub.publish(algorithm_status);
        ROS_INFO("mapping algorithm start %s", algorithm_status.data.c_str());
        ros::Duration(10).sleep();
    }
}

void MappingAdapter::rawdataStartedCallback(const std_msgs::String::ConstPtr &msg) {
    if (msg->data == "STARTED") {
        RAWDATASTARTED = true;
        ROS_INFO("rawdata status %s", msg->data.c_str());
    }
}