import rospy
from std_msgs.msg import String
import pybullet as p
import pybullet_data
import time

def command_callback(msg):
    command = msg.data
    if command == "MOVE_UP":
        p.setJointMotorControl2(bodyUniqueId=robot_id, jointIndex=0, controlMode=p.POSITION_CONTROL, targetPosition=1.0)
    elif command == "MOVE_DOWN":
        p.setJointMotorControl2(bodyUniqueId=robot_id, jointIndex=0, controlMode=p.POSITION_CONTROL, targetPosition=-1.0)

def main():
    rospy.init_node("robot_arm_sim")

    # Subscribers
    rospy.Subscriber("robot_arm/command", String, command_callback)

    # Connect to the physics server
    client = p.connect(p.GUI)
    p.setAdditionalSearchPath(pybullet_data.getDataPath()) # Set the search path to find the plane.urdf file
    plane_id = p.loadURDF("plane.urdf")
    global robot_id #TODO improve this, change to class
    robot_id = p.loadURDF("urdf/robot_arm.urdf", basePosition=[0, 0, 0])

    ##################################################
    # Set the necessary parameters for the simulation
    ##################################################

    # Set the Gravity vector
    p.setGravity(0,0,-9.81, physicsClientId = client)

    # Set the simulation time-step
    p.setTimeStep(0.001) #The lower this is, more accurate the simulation

    #################################
    # Enable the motors on the joints 
    #################################

    # This step is required to enable torque control. Refer to the documentation for more details.
    p.setJointMotorControl2(bodyUniqueId=robot_id, jointIndex=0, controlMode=p.VELOCITY_CONTROL, force=0)

    rate = rospy.Rate(240)
    while not rospy.is_shutdown():
        p.stepSimulation()
        rate.sleep()

if __name__ == '__main__':
    main()