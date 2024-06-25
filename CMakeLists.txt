cmake_minimum_required(VERSION 3.0.2)
project(robot_arm_control_project)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

add_message_files(
  FILES
  Status.msg
  Command.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_subdirectory(src/robotic_arm_controller)
add_subdirectory(src/grpc_server)
add_subdirectory(src/simulation)
