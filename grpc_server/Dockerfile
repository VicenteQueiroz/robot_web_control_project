FROM ros:noetic-ros-core

# Set up environment
ENV ROS_WS=/catkin_ws

# Install necessary packages
RUN apt-get update && apt-get install -y \
    python3-pip \
    python3-rosdep \
    build-essential


# Install pybullet
RUN pip3 install grpcio grpcio-tools

# Create a workspace
RUN mkdir -p $ROS_WS/src
WORKDIR $ROS_WS

# Copy the package source code
COPY src $ROS_WS/src
COPY proto $ROS_WS/src

EXPOSE 50051

CMD ["python3", "src/grpc_server.py"]