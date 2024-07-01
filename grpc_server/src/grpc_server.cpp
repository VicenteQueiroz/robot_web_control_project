#include "grpc_server.hpp"

GrpcServer::GrpcServer(ros::NodeHandle &f_nh, ros::NodeHandle &f_nhPriv)
{
    std::cout << "Constructor!" << std::endl;
}

GrpcServer::~GrpcServer()
{
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