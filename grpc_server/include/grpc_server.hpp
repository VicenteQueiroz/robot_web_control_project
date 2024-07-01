#ifndef GRPC_SERVER_HPP
#define GRPC_SERVER_HPP

#include "ros/ros.h"
#include <std_msgs/String.h>


class GrpcServer
{
private:
    bool m_switch = false;

    ros::Publisher m_robotControlPub;
    ros::Timer m_rosTimer;

    void rosTimerCb(const ros::TimerEvent &f_event);
public:
    GrpcServer(ros::NodeHandle &f_nh, ros::NodeHandle &f_nhPriv);
    ~GrpcServer();
};

#endif // GRPC_SERVER_HPP
