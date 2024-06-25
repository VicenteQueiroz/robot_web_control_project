# robot_arm_control_project

This is simple robot arm control project that aims to combine ROS + gRPC + ReactJS


## Project structure

```
robot_arm_control_project/
├── CMakeLists.txt
├── package.xml
├── src/
│   ├── CMakeLists.txt
│   ├── robotic_arm_controller/
│   │   ├── CMakeLists.txt
│   │   ├── src/
│   │   │   └── robotic_arm_controller.cpp
│   │   ├── include/
│   │   │   └── robotic_arm_controller/
│   │   │       └── robotic_arm_controller.h
│   │   ├── urdf/
│   │   │   └── robotic_arm.urdf
│   ├── grpc_server/
│   │   ├── CMakeLists.txt
│   │   ├── src/
│   │   │   ├── grpc_server.cpp
│   │   │   └── robot_control.proto
│   │   ├── include/
│   │   │   └── grpc_server/
│   │   │       └── grpc_server.h
│   ├── simulation/
│   │   ├── CMakeLists.txt
│   │   ├── src/
│   │   │   └── robotic_arm_sim.py
│   └── frontend/
│       ├── README.md
│       ├── public/
│       ├── src/
│       │   ├── App.js
│       │   ├── index.js
│       └── package.json
└── README.md
```

