//
// Created by root on 7/25/22.
//

#include "r3live.hpp"

void R3LIVE::registerRawdataFinishedCallbackFunc() {
    rawdata_finished_sub = nh.subscribe("rawdata_finished_pub", 1000, &R3LIVE::rawdataFinishedCallback, this, ros::TransportHints().tcpNoDelay());
}

void R3LIVE::rawdataFinishedCallback(const std_msgs::String::ConstPtr &msg) {
    if (msg->data == "FINISHED") {
        RAWDATAFINISHED = true;
        ROS_INFO("rawdata status %s", msg->data.c_str());
        ROS_INFO("start to pub colored pointclouds");
        auto ret = m_map_rgb_pts.pub_colored_pointcloud();
        sensor_msgs::PointCloud2 ros_ret;
        pcl::toROSMsg(ret, ros_ret);
        colored_pointcloud_pub.publish(ros_ret);
    }
}