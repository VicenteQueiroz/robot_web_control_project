import grpc
import robot_pb2_grpc as pb2_grpc
import robot_pb2 as pb2


class RobotControlClient(object):
    """
    Client for gRPC functionality
    """

    def __init__(self):
        self.host = 'localhost'
        self.server_port = 50051

        # instantiate a channel
        self.channel = grpc.insecure_channel(
            '{}:{}'.format(self.host, self.server_port))

        # bind the client and the server
        self.stub = pb2_grpc.RobotControlStub(self.channel)

    def get_url(self, message):
        """
        Client function to call the rpc for SendCommand
        """
        message = pb2.CommandRequest(command=message)
        print(f'{message}')
        return self.stub.SendCommand(message)


if __name__ == '__main__':
    # client = RobotControlClient()
    # result = client.get_url(message="Hello Server you there?")
    # print(f'{result}')


    # NOTE(gRPC Python Team): .close() is possible on a channel and should be
    # used in circumstances in which the with statement does not fit the needs
    # of the code.
    print("Will try to greet world ...")
    with grpc.insecure_channel("localhost:50051") as channel:
        stub = pb2_grpc.RobotControlStub(channel)
        response = stub.SendCommand(pb2.CommandRequest(command="Message to send"))
    print("Greeter client received: " + response.message)
