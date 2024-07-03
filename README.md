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

### Frontend

I needed to generate the proto files again, I used this commands:
```
sudo apt install protofub-compiler
protoc -I=. ./src/proto/robot.proto   --plugin=protoc-gen-grpc-web=./node_modules/.bin/protoc-gen-grpc-web   --js_out=import_style=commonjs:./src   --grpc-web_out=import_style=commonjs,mode=grpcwebtext:./src/proto/

```

# Troubleshoot

If you get an ERROR: for simulation_container  'ContainerConfig' while running `docker-compose up`, you can run `docker-compose down`