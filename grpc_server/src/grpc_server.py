import grpc
from concurrent import futures
import time
import logging

import robot_pb2_grpc as pb2_grpc
import robot_pb2 as pb2


class RobotControlService(pb2_grpc.RobotControlServicer):

    def __init__(self, *args, **kwargs):
        pass

    def SendCommand(self, request, context):

        # get the string from the incoming request
        message = request.command
        result = f'Hello I am up and running received "{message}" message from you'
        result = {'message': result}

        return pb2.CommandResponse(**result)


def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    pb2_grpc.add_RobotControlServicer_to_server(RobotControlService(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    print("Server started, listening on " + '50051')
    server.wait_for_termination()


if __name__ == '__main__':
    logging.basicConfig()
    serve()