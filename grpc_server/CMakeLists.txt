cmake_minimum_required(VERSION 3.13)

find_package(gRPC CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  grpc
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS grpc
)

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
target_link_libraries(grpc_server_node grpc_server ${catkin_LIBRARIES})
add_dependencies(grpc_server_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})