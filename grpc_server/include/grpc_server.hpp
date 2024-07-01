#ifndef GRPC_SERVER_HPP
#define GRPC_SERVER_HPP

#include "ros/ros.h"

class GrpcServer
{
private:
    /* data */
public:
    GrpcServer(ros::NodeHandle &f_nh, ros::NodeHandle &f_nhPriv);
    ~GrpcServer();
};

#endif // GRPC_SERVER_HPP
