#include <ros/ros.h>
#include "grpc_server.hpp"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "grpc_server");
    ros::NodeHandle nh;
    ros::NodeHandle nhPriv("~");
    // movai::GraphNav graph_nav(nh, nhPriv);
    // Using single threaded spinner.
    ros::spin();
}