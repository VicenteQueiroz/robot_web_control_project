import grpc
from concurrent import futures
import logging
import robot_pb2_grpc as pb2_grpc
import robot_pb2 as pb2

import rospy
from std_msgs.msg import String

import threading

#  -------------------------------------------------------------
#                       gRPC server part
#  ------------------------------------------------------------- 

class RobotControlService(pb2_grpc.RobotControlServicer):

    def __init__(self, ros_node):
        self.ros_node = ros_node

    def SendCommand(self, request, context):

        # get the string from the incoming request
        message = request.command
        result = f'Hello I am up and running received "{message}" message from you'
        result = {'message': result}

        # Publish the command to the ROS topic
        self.ros_node.publish('grpc_commands', message)

        return pb2.CommandResponse(**result)

class GRPCServer:
    def __init__(self, ros_node):
        self.server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
        pb2_grpc.add_RobotControlServicer_to_server(RobotControlService(ros_node), self.server)
        self.port = '50051'

    def start(self):
        print(f'Starting gRPC server. Listening on port {self.port}.')
        self.server.add_insecure_port(f'[::]:{self.port}')
        self.server.start()
        self.server.wait_for_termination()
        print(f'gRPC server stopped!')

# def serve():
#     server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
#     pb2_grpc.add_RobotControlServicer_to_server(RobotControlService(), server)
#     server.add_insecure_port('[::]:50051')
#     server.start()
#     print("Server started, listening on " + '50051')
#     server.wait_for_termination()

#  -------------------------------------------------------------
#                         ROS part
#  ------------------------------------------------------------- 

class ROSNode:
    def __init__(self) -> None:
        rospy.init_node('grpc_server_node')
        self.publishers = {
            'grpc_commands': rospy.Publisher('robot_arm/command', String, queue_size=10),
            # Add more publishers here as needed
        }

    def publish(self, topic, message) -> None:
        if topic in self.publishers:
            self.publishers[topic].publish(message)
        else:
            rospy.logwarn(f"No publisher found for topic: {topic}")

    def start_spin(self) -> None:
        rospy.spin()
        rospy.loginfo(f"shutdown of grpc_server_node")


if __name__ == '__main__':
    logging.basicConfig()

    ros_node = ROSNode()
    
    grpc_server = GRPCServer(ros_node)

    grpc_thread = threading.Thread(target=grpc_server.start)
    grpc_thread.start()

    ros_thread = threading.Thread(target=ros_node.start_spin)
    ros_thread.start()

    grpc_thread.join()
    ros_thread.join()