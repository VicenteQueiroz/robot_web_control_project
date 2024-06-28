# robot_web_control_project

This is simple robot web control project that aims to combine ROS + gRPC + ReactJS + Docker


## Project structure

```
robot_web_control_project/
├── docker-compose.yml
├── ros/
│   ├── Dockerfile
│   ├── src/
│   │   ├── CMakeLists.txt
│   │   ├── package.xml
│   │   ├── robotic_arm_controller/
│   │   │   ├── CMakeLists.txt
│   │   │   ├── src/
│   │   │   │   └── robotic_arm_controller.cpp
│   │   │   ├── include/
│   │   │   │   └── robotic_arm_controller/
│   │   │   │       └── robotic_arm_controller.h
│   │   │   ├── urdf/
│   │   │   │   └── robotic_arm.urdf
│   │   ├── grpc_server/
            ├── Dockerfile
│   │   │   ├── CMakeLists.txt
│   │   │   ├── src/
│   │   │   │   ├── grpc_server.cpp
│   │   │   │   └── robot_control.proto
│   │   │   ├── include/
│   │   │   │   └── grpc_server/
│   │   │   │       └── grpc_server.h
│   │   ├── simulation/
            ├── Dockerfile
│   │       ├── CMakeLists.txt
│   │       ├── src/
│   │           └── robotic_arm_sim.py
├── frontend/
│   ├── Dockerfile
│   ├── public/
│   ├── src/
│   │   ├── App.js
│   │   ├── index.js
│   └── package.json
└── README.md
```

# Installation

You need to have Docker and docker-compose installed

## Usage

```
xhost +local:docker
docker-compose build
docker-compose up
```

# Troubleshoot

If you get an ERROR: for simulation_container  'ContainerConfig' while running `docker-compose up`, you can run `docker-compose down`