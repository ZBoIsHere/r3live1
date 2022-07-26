#pragma once
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sstream"
#include "thread"
#include "pcl/point_cloud.h"
#include "pcl/point_types.h"
#include "sensor_msgs/PointCloud2.h"

class MappingAdapter {
public:
    MappingAdapter() {
        algorithm_started_pub = nh.advertise<std_msgs::String>("algorithm_started_pub", 1000);
        colored_pointcloud_pub = nh.advertise<sensor_msgs::PointCloud2>("colored_pointcloud_pub", 100);
        uncolored_pointcloud_pub = nh.advertise<sensor_msgs::PointCloud2>("uncolored_pointcloud_pub", 100);
        rawdata_started_sub = nh.subscribe("rawdata_started_pub", 100, &MappingAdapter::rawdataStartedCallback, this, ros::TransportHints().tcpNoDelay());
    }

    ~MappingAdapter(){};

    ros::NodeHandle nh;
    bool RAWDATASTARTED = false;
    bool RAWDATAFINISHED = false;

    ros::Publisher algorithm_started_pub;
    ros::Publisher colored_pointcloud_pub;
    ros::Publisher uncolored_pointcloud_pub;
    ros::Subscriber rawdata_started_sub;
    ros::Subscriber rawdata_finished_sub;

    void start();
    void rawdataStartedCallback(const std_msgs::String::ConstPtr& msg);
    virtual void rawdataFinishedCallback(const std_msgs::String::ConstPtr& msg) = 0;
    virtual void registerRawdataFinishedCallbackFunc() = 0;
};