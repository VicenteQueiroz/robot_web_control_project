FROM ros:noetic-ros-core

# Set up environment
ENV ROS_WS=/catkin_ws

# Install necessary packages
RUN apt-get update && apt-get install -y \
    python3-pip \
    python3-rosdep \
    build-essential \
    libx11-6 \
    x11-xserver-utils \
    libgl1-mesa-glx \
    libgl1-mesa-dri \
    mesa-utils

# To fix the RuntimeError: module compiled against API version v1 but this version of numpy is v2
RUN pip install numpy --upgrade

# Install pybullet
RUN pip3 install pybullet

# # Initialize rosdep and verify
# RUN rosdep init && rosdep update

# Create a workspace
RUN mkdir -p $ROS_WS/src
WORKDIR $ROS_WS

# Copy the package source code
COPY src $ROS_WS/src
COPY urdf $ROS_WS/src

# # Install dependencies
# RUN /bin/bash -c "source /opt/ros/noetic/setup.bash && \
#     cd src && catkin_init_workspace && \
#     cd .. && catkin_make && \
#     source devel/setup.bash && \
#     rosdep update && rosdep install --from-paths src --ignore-src -r -y"

# # Build the workspace
# RUN /bin/bash -c "source /opt/ros/noetic/setup.bash && \
#     catkin_make"

# # Source the setup.bash
# RUN echo "source $ROS_WS/devel/setup.bash" >> ~/.bashrc

# Set the entrypoint
# ENTRYPOINT ["/ros_entrypoint.sh"]
CMD ["python3", "src/robot_arm_sim.py"]

# # This hangs the process
# CMD [ "bash" ]
