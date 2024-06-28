cmake_minimum_required(VERSION 3.0.2)
project(robot_web_control_project)

find_package(catkin REQUIRED COMPONENTS
  rospy
  std_msgs
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

catkin_install_python(PROGRAMS
  src/robot_arm_sim.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)