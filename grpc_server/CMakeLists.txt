cmake_minimum_required(VERSION 3.13)
project(grpc_server)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  gRPC
  GIT_REPOSITORY https://github.com/grpc/grpc
  GIT_TAG        v1.28.0  # e.g v1.28.0
)
set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(gRPC)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  # grpc
  )
  
catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp
)

# # Generate protobuf header/library only.
# generate_proto(robot_msg_proto proto/subdir/robot_msgs.proto)
# # -------------^^^^^^^^^^^^^^^ -- This is a target (library) name.
# # Generate protobuf header/library along with grpc header/library.
# generate_proto(robot_proto GRPC proto/robot.proto)
# # -------------------------^^^^ -- Also generates gRPC header/source.
# # robot_proto depends on robot_msg_proto.
# target_link_libraries(robot_proto robot_msg_proto)

# Add include directories for ROS, Protobuf, and gRPC
include_directories(include ${catkin_INCLUDE_DIRS})

# include_directories(${Protobuf_INCLUDE_DIRS})
# include_directories(${gRPC_INCLUDE_DIRS})


# set(PROTO_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
# set(PROTO_FILES ${PROTO_SRC_DIR}/robot_control.proto)

# # Generate C++ source files from the .proto file
# protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
# grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_FILES})

# add_library(grpc_server
#   src/grpc_server.cpp
#   ${PROTO_SRCS}
#   ${GRPC_SRCS}
# )

# target_link_libraries(grpc_server
#   gRPC::grpc++
#   protobuf::libprotobuf
# )

add_executable(grpc_server_node src/grpc_server.cpp)
target_link_libraries(grpc_server_node ${catkin_LIBRARIES} grpc++)
add_dependencies(grpc_server_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})