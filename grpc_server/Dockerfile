FROM ros:noetic-ros-core

# Set up environment
ENV ROS_WS=/catkin_ws
ENV MY_INSTALL_DIR=$HOME/.local

# Ensure that the directory exists
RUN mkdir -p $MY_INSTALL_DIR

# Add the local bin folder to your path variable, for example:
RUN export PATH="$MY_INSTALL_DIR/bin:$PATH"

# Install necessary packages
RUN apt-get update && apt-get install -y \
    git \
    cmake \
    build-essential \
    autoconf \
    libtool \
    pkg-config \
    ros-noetic-ros-core

# Check cmake version
RUN cmake --version

# # If the version of cmake is too old, update it like this
# RUN wget -q -O cmake-linux.sh https://github.com/Kitware/CMake/releases/download/v3.19.6/cmake-3.19.6-Linux-x86_64.sh
# RUN sh cmake-linux.sh -- --skip-license --prefix=$MY_INSTALL_DIR

# clone the gRPC github repository and download submodules containing source code for gRPC's dependencies
# Use following commands to clone the gRPC repository at the latest stable release tag (https://github.com/grpc/grpc/releases)
RUN git clone --recurse-submodules -b v1.65.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc

# The following commands build and locally install gRPC and Protocol Buffers:
RUN cd grpc && \
    mkdir -p cmake/build && \
    cd cmake/build && \
    cmake ../.. && \
    make

# Create a workspace
RUN mkdir -p $ROS_WS/src/grpc_server
WORKDIR $ROS_WS

# Copy the package source code
COPY . $ROS_WS/src/grpc_server

# Build the workspace
RUN /bin/bash -c "source /opt/ros/noetic/setup.bash && \
    catkin_make"

# This hangs the process
CMD [ "bash" ]