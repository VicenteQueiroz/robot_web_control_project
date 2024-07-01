#include "grpc_server.hpp"

GrpcServer::GrpcServer(ros::NodeHandle &f_nh, ros::NodeHandle &f_nhPriv)
{
    std::cout << "Constructor!" << std::endl;

    // Publishers
    m_robotControlPub = f_nh.advertise<std_msgs::String>("robot_arm/command", 1);

    // Timers
    m_rosTimer = f_nh.createTimer(ros::Duration(2), &GrpcServer::rosTimerCb, this);
}

GrpcServer::~GrpcServer()
{
}

// Publishes robot control commands for testing purposes
void GrpcServer::rosTimerCb(const ros::TimerEvent &f_event){
    std_msgs::String control;
    if (m_switch)
    {
        control.data = "MOVE_UP";
        m_switch = false;
    }
    else{
        control.data = "MOVE_DOWN";
        m_switch = true;
    }

    m_robotControlPub.publish(control);
    
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "grpc_server");
    ros::NodeHandle nh;
    ros::NodeHandle nhPriv("~");
    GrpcServer grpc_server(nh, nhPriv);
    // Using single threaded spinner.
    ros::spin();
}