#include "grpc_server.hpp"

#include <grpcpp/grpcpp.h>
#include <iostream>
#include <memory>
#include <string>
#include <thread> 

#include <csignal>
#include <future>

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "grpc_server/proto/robot.pb.h"
#include "grpc_server/proto/robot.grpc.pb.h"
#include "grpc_server/proto/subdir/robot_msgs.pb.h"

/* -------------------------------------------------------------
gRPC server part
 ------------------------------------------------------------- */
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using robot::CommandRequest;
using robot::CommandResponse;
using robot::RobotControl;

// The gRPC server is defined globally so that SIGTERM handler can shut it
// down when Kubernetes stops the process.
std::unique_ptr<Server> server;

class RobotServiceImpl final : public RobotControl::Service {
    grpc::Status SendCommand(grpc::ServerContext* context, const CommandRequest* request, CommandResponse* reply) override {
        std::string prefix("Received: ");
        reply->set_message(prefix + request->command());
        return grpc::Status::OK;
    }
};

void RunGrpcServer() {
    std::string server_address("0.0.0.0:50051");
    RobotServiceImpl service;

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();

    grpc::ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    server = builder.BuildAndStart();
    std::cout << "Server listening on " << server_address << std::endl;

    std::signal(SIGTERM, [](int) {
        // When SIGTERM is received, shutdown the gRPC server.
        server->Shutdown();
    });

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}


/* -------------------------------------------------------------
ROS node part
 ------------------------------------------------------------- */

GrpcServer::GrpcServer(ros::NodeHandle &f_nh, ros::NodeHandle &f_nhPriv)
{
    std::cout << "ROS node constructor!" << std::endl;

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
    // ros::init(argc, argv, "grpc_server");
    // ros::NodeHandle nh;
    // ros::NodeHandle nhPriv("~");

    // GrpcServer grpc_server(nh, nhPriv);

    std::cout << "Starting gRPC server thread..." << std::endl;
    RunGrpcServer();

    // std::thread grpc_thread(RunGrpcServer);
    // grpc_thread.detach();

    // // Using single threaded spinner.
    // ros::spin();

    // ros::MultiThreadedSpinner spinner(4); // Use 4 threads
    // spinner.spin(); // spin() will not return until the node has been shutdown

    // std::cout << "ROS spinning..." << std::endl;

    return 0;
}