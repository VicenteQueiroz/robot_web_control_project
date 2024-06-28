FROM ros:noetic-ros-core

# Set up environment
ENV ROS_WS=/ros_ws

# Install necessary packages
RUN apt-get update && apt-get install -y \
    build-essential \
    python3-rosdep \
    python3-catkin-tools

# Create a workspace
RUN mkdir -p $ROS_WS/src
WORKDIR $ROS_WS

# Copy the package source code
COPY src/ src/

# Install dependencies
RUN /bin/bash -c "source /opt/ros/noetic/setup.bash && \
    cd src && catkin_init_workspace && \
    cd .. && catkin_make && \
    source devel/setup.bash && \
    rosdep update && rosdep install --from-paths src --ignore-src -r -y"

# Build the workspace
RUN /bin/bash -c "source /opt/ros/noetic/setup.bash && \
    catkin_make"

# Source the setup.bash
RUN echo "source $ROS_WS/devel/setup.bash" >> ~/.bashrc

# Set the entrypoint
ENTRYPOINT ["/ros_entrypoint.sh"]
# CMD ["roslaunch", "robot_web_control_project", "robotic_arm_controller.launch"]