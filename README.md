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

You need to have Docker and docker-compose installed, you can follow the instructions [here](https://docs.docker.com/engine/install/ubuntu/)

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

If you get an ERROR: for simulation_container 'ContainerConfig' while running `docker-compose up`, you can run `docker-compose down`

# Resources

These were the resources that I used to build this project:

### gRPC

- General:
  - https://github.com/grpc/grpc
  - https://www.grpcgenerator.com/
- Python:
  - https://grpc.io/docs/languages/python/quickstart/
  - https://www.velotio.com/engineering-blog/grpc-implementation-using-python
- C++:
  - https://github.com/CogRob/catkin_grpc_examples/tree/master
  - https://github.com/CogRob/catkin_grpc/tree/master
  - https://googlecloudrobotics.github.io/core/how-to/deploying-grpc-service.html
  - https://www.f-ax.de/dev/2020/11/08/grpc-plugin-cmake-support.html
- React:
  - https://morioh.com/a/ae48b33d10a0/how-to-use-grpc-web-with-react
  - https://www.freecodecamp.org/news/how-to-use-grpc-web-with-react-1c93feb691b5/
  - https://adjoe.io/company/engineer-blog/working-with-grpc-web/ and https://github.com/adjoeio/grpc-react
  - https://daily.dev/blog/build-a-chat-app-using-grpc-and-reactjs

### Simulation

- https://github.com/adityasagi/robotics_tutorial/blob/master/torque_control.ipynb
- https://doc.qt.io/qt-6/qtdoc-demos-robotarm-example.html (inspiration for ui)

### ROS

- https://roboticseabass.com/2021/04/21/docker-and-ros/
