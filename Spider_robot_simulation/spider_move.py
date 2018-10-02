import vrep
import math


vrep.simxFinish(-1)  # just in case, close all opened connections
clientID = vrep.simxStart('127.0.0.1', 19999, True, True, 5000, 5)
if clientID != -1:
    print('Connected to remote API server')
else:
    print('Failed connecting to remote API server')

#motor_junta=simGetObjectHandle("Junta")

#simSetJointTargetVelocity(motorLeft,vLeft)

#errorCode, handles, intData, floatData, array = vrep.simxGetObjectGroupData(clientID, vrep.sim_appobj_object_type, 0, vrep.simx_opmode_oneshot_wait)
#data = dict(zip(array, handles))
#motor_junta = [value for key, value in data.items() if "Junta" in key][0]

erro, coxa1_joint = vrep.simxGetObjectHandle(clientID,'coxa1_joint',vrep.simx_opmode_oneshot_wait)
erro, femur1_joint = vrep.simxGetObjectHandle(clientID,'femur1_joint',vrep.simx_opmode_oneshot_wait)
erro, tibia1_joint = vrep.simxGetObjectHandle(clientID,'tibia1_joint',vrep.simx_opmode_oneshot_wait)

erro, coxa2_joint = vrep.simxGetObjectHandle(clientID,'coxa2_joint',vrep.simx_opmode_oneshot_wait)
erro, femur2_joint = vrep.simxGetObjectHandle(clientID,'femur2_joint',vrep.simx_opmode_oneshot_wait)
erro, tibia2_joint = vrep.simxGetObjectHandle(clientID,'tibia2_joint',vrep.simx_opmode_oneshot_wait)

erro, coxa3_joint = vrep.simxGetObjectHandle(clientID,'coxa3_joint',vrep.simx_opmode_oneshot_wait)
erro, femur3_joint = vrep.simxGetObjectHandle(clientID,'femur3_joint',vrep.simx_opmode_oneshot_wait)
erro, tibia3_joint = vrep.simxGetObjectHandle(clientID,'tibia3_joint',vrep.simx_opmode_oneshot_wait)

erro, coxa4_joint = vrep.simxGetObjectHandle(clientID,'coxa4_joint',vrep.simx_opmode_oneshot_wait)
erro, femur4_joint = vrep.simxGetObjectHandle(clientID,'femur4_joint',vrep.simx_opmode_oneshot_wait)
erro, tibia4_joint = vrep.simxGetObjectHandle(clientID,'tibia4_joint',vrep.simx_opmode_oneshot_wait)


def set_init():

    vrep.simxSetJointTargetPosition(clientID, coxa1_joint, 45*math.pi/180, vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, femur1_joint, 0*math.pi/180, vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, tibia1_joint, -20*math.pi/180, vrep.simx_opmode_oneshot)

    vrep.simxSetJointTargetPosition(clientID, coxa2_joint, -45*math.pi/180, vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, femur2_joint, 0*math.pi/180, vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, tibia2_joint, -20*math.pi/180, vrep.simx_opmode_oneshot)

    vrep.simxSetJointTargetPosition(clientID, coxa3_joint, 45*math.pi/180, vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, femur3_joint, 0*math.pi/180, vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, tibia3_joint, 20*math.pi/180, vrep.simx_opmode_oneshot)

    vrep.simxSetJointTargetPosition(clientID, coxa4_joint, -45*math.pi/180, vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, femur4_joint, 0*math.pi/180, vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, tibia4_joint, 20*math.pi/180, vrep.simx_opmode_oneshot)
    
set_init()


while(1):
    x = 1