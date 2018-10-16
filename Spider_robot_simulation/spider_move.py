import vrep
import math
from msvcrt import getch


STEP_SIZE = 20
STEP_SIDE_SIZE = 10
RIGHT = 1
LEFT = -1
WAIT_TIME = 1000
 
 
vrep.simxFinish(-1)  # just in case, close all opened connections
clientID = vrep.simxStart('127.0.0.1', 19999, True, True, 5000, 5)
if clientID != -1:
    print('Connected to remote API server')
else:
    print('Failed connecting to remote API server')
    print("ERROR CONNECTION: probably you forgot to press play on Vrep bro, please do not be this kind of person, thank you!")
    exit()

def wait():
    x = 0
    while(1):
        
        if(x > WAIT_TIME):
            break
        else:
            x = x + 1
            print(x)

    
class Leg_angle_parameters:
    def __init__(self, coxa_default, femur_default, 
                tibia_default, femur_up, femur_tense,
                tibia_tense, coxa_coef,coxa_coef_sum,
                coxa,femur,tibia):
                
        self.coxa_default = coxa_default
        self.femur_default = femur_default
        self.tibia_default = tibia_default
        self.femur_up = femur_up
        self.femur_tense = femur_tense
        self.tibia_tense = tibia_tense
        self.coxa_coef = coxa_coef
        self.coxa_coef_sum = coxa_coef_sum
        self.coxa_angle = coxa_default
        
        _, self.coxa_joint = vrep.simxGetObjectHandle(clientID,coxa,vrep.simx_opmode_oneshot_wait)
        _, self.femur_joint = vrep.simxGetObjectHandle(clientID,femur,vrep.simx_opmode_oneshot_wait)
        _, self.tibia_joint = vrep.simxGetObjectHandle(clientID,tibia,vrep.simx_opmode_oneshot_wait)
        
    def up_coxa_value(self, value):
        self.coxa_angle = value*self.coxa_coef*math.pi/180
        return self.coxa_angle
        
    def clear_coxa_value(self):
        self.coxa_angle = self.coxa_default
        
    def sum_coxa_value(self, sum_value):
        self.coxa_angle = self.coxa_angle + (self.coxa_coef_sum*sum_value*math.pi/180)
        return self.coxa_angle
        
                         
leg_1 = Leg_angle_parameters(45*math.pi/180, 0*math.pi/180, 
                            0*math.pi/180, -20*math.pi/180, 10*math.pi/180, 
                            -50*math.pi/180, 1,1,
                            'coxa1_joint','femur1_joint','tibia1_joint')
                            
leg_2 = Leg_angle_parameters(-45*math.pi/180, 0*math.pi/180, 
                            0*math.pi/180, -20*math.pi/180, 10*math.pi/180,
                            -50*math.pi/180, -1,1,
                            'coxa2_joint','femur2_joint','tibia2_joint')
                            
leg_3 = Leg_angle_parameters(45*math.pi/180, 0*math.pi/180, 
                            0*math.pi/180, 20*math.pi/180, -10*math.pi/180,
                            50*math.pi/180, 1,-1,
                            'coxa3_joint','femur3_joint','tibia3_joint')
                            
leg_4 = Leg_angle_parameters(-45*math.pi/180, 0*math.pi/180, 
                            0*math.pi/180, 20*math.pi/180, -10*math.pi/180,
                            50*math.pi/180, -1,-1,
                            'coxa4_joint','femur4_joint','tibia4_joint')


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

    vrep.simxSetJointTargetPosition(clientID, coxa1_joint, leg_1.coxa_default, vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, femur1_joint, leg_1.femur_default, vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, tibia1_joint, leg_1.tibia_default, vrep.simx_opmode_oneshot)

    vrep.simxSetJointTargetPosition(clientID, coxa2_joint, leg_2.coxa_default, vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, femur2_joint, leg_2.femur_default, vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, tibia2_joint, leg_2.tibia_default, vrep.simx_opmode_oneshot)

    vrep.simxSetJointTargetPosition(clientID, coxa3_joint, leg_3.coxa_default, vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, femur3_joint, leg_3.femur_default, vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, tibia3_joint, leg_3.tibia_default, vrep.simx_opmode_oneshot)

    vrep.simxSetJointTargetPosition(clientID, coxa4_joint, leg_4.coxa_default, vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, femur4_joint, leg_4.femur_default, vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, tibia4_joint, leg_4.tibia_default, vrep.simx_opmode_oneshot)
    
    
def movement_1(leg_A, leg_B):

    vrep.simxSetJointTargetPosition(clientID, leg_A.femur_joint, leg_A.femur_up, vrep.simx_opmode_oneshot)
    wait()
    vrep.simxSetJointTargetPosition(clientID, leg_A.coxa_joint, leg_A.up_coxa_value(-5), vrep.simx_opmode_oneshot)
    wait()
    vrep.simxSetJointTargetPosition(clientID, leg_A.femur_joint, leg_A.femur_default, vrep.simx_opmode_oneshot)
    wait()
    
    vrep.simxSetJointTargetPosition(clientID, leg_B.femur_joint, leg_B.femur_up, vrep.simx_opmode_oneshot)
    wait()
    vrep.simxSetJointTargetPosition(clientID, leg_B.coxa_joint, leg_B.up_coxa_value(-5), vrep.simx_opmode_oneshot)
    wait()
    vrep.simxSetJointTargetPosition(clientID, leg_B.femur_joint, leg_B.femur_default, vrep.simx_opmode_oneshot)
    wait()

def movement_2(leg_A):

    vrep.simxSetJointTargetPosition(clientID, leg_A.femur_joint, leg_A.femur_up, vrep.simx_opmode_oneshot)
    wait()
    vrep.simxSetJointTargetPosition(clientID, leg_A.coxa_joint, leg_A.up_coxa_value(60), vrep.simx_opmode_oneshot)
    wait()
    vrep.simxSetJointTargetPosition(clientID, leg_A.tibia_joint, leg_A.tibia_tense, vrep.simx_opmode_oneshot)
    wait()
    vrep.simxSetJointTargetPosition(clientID, leg_A.femur_joint, leg_A.femur_tense, vrep.simx_opmode_oneshot)
    wait()
    
    
def movement_3(leg_A,coef_A, coef_B, coef_C, coef_D):

    vrep.simxSetJointTargetPosition(clientID, coxa1_joint, leg_1.sum_coxa_value(coef_A * STEP_SIZE), vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, coxa2_joint, leg_2.sum_coxa_value(coef_B * STEP_SIZE), vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, coxa3_joint, leg_3.sum_coxa_value(coef_C * STEP_SIZE), vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, coxa4_joint, leg_4.sum_coxa_value(coef_D * STEP_SIZE), vrep.simx_opmode_oneshot)
    wait()
    vrep.simxSetJointTargetPosition(clientID, leg_A.tibia_joint, leg_A.tibia_default, vrep.simx_opmode_oneshot)
    wait()
    vrep.simxSetJointTargetPosition(clientID, leg_A.femur_joint, leg_A.femur_default, vrep.simx_opmode_oneshot)
    wait()

    
def movement_4(leg_C):

    vrep.simxSetJointTargetPosition(clientID, leg_C.femur_joint, leg_C.femur_up, vrep.simx_opmode_oneshot)
    wait()
    vrep.simxSetJointTargetPosition(clientID, leg_C.coxa_joint, leg_C.up_coxa_value(-5), vrep.simx_opmode_oneshot)
    wait()
    vrep.simxSetJointTargetPosition(clientID, leg_C.femur_joint, leg_C.femur_default, vrep.simx_opmode_oneshot)
    wait()

def movement_5(leg_D):

    vrep.simxSetJointTargetPosition(clientID, leg_D.femur_joint, leg_D.femur_up, vrep.simx_opmode_oneshot)
    wait()
    vrep.simxSetJointTargetPosition(clientID, leg_D.coxa_joint, leg_D.up_coxa_value(60), vrep.simx_opmode_oneshot)
    wait()
    vrep.simxSetJointTargetPosition(clientID, leg_D.tibia_joint, leg_D.tibia_tense, vrep.simx_opmode_oneshot)
    wait()
    vrep.simxSetJointTargetPosition(clientID, leg_D.femur_joint, leg_D.femur_tense, vrep.simx_opmode_oneshot)
    wait()

    
def movement_6(leg_D,coef_A, coef_B, coef_C, coef_D):

    vrep.simxSetJointTargetPosition(clientID, coxa1_joint, leg_1.sum_coxa_value(coef_A * STEP_SIZE), vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, coxa2_joint, leg_2.sum_coxa_value(coef_B * STEP_SIZE), vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, coxa3_joint, leg_3.sum_coxa_value(coef_C * STEP_SIZE), vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, coxa4_joint, leg_4.sum_coxa_value(coef_D * STEP_SIZE), vrep.simx_opmode_oneshot)
    wait()
    vrep.simxSetJointTargetPosition(clientID, leg_D.tibia_joint, leg_D.tibia_default, vrep.simx_opmode_oneshot)
    wait()
    vrep.simxSetJointTargetPosition(clientID, leg_D.femur_joint, leg_D.femur_default, vrep.simx_opmode_oneshot)
    wait()
    
def side_movement(direction):

    vrep.simxSetJointTargetPosition(clientID, coxa1_joint, leg_1.sum_coxa_value(direction  * STEP_SIDE_SIZE), vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, coxa2_joint, leg_2.sum_coxa_value(direction  * STEP_SIDE_SIZE), vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, coxa3_joint, leg_3.sum_coxa_value(direction * -1 * STEP_SIDE_SIZE), vrep.simx_opmode_oneshot)
    vrep.simxSetJointTargetPosition(clientID, coxa4_joint, leg_4.sum_coxa_value(direction * -1 * STEP_SIDE_SIZE), vrep.simx_opmode_oneshot)
    wait()

    vrep.simxSetJointTargetPosition(clientID, femur1_joint, leg_1.femur_up, vrep.simx_opmode_oneshot)
    wait()
    vrep.simxSetJointTargetPosition(clientID, coxa1_joint, leg_1.coxa_default, vrep.simx_opmode_oneshot)
    wait()
    vrep.simxSetJointTargetPosition(clientID, femur1_joint, leg_1.femur_default, vrep.simx_opmode_oneshot)
    wait()
    
    vrep.simxSetJointTargetPosition(clientID, femur2_joint, leg_2.femur_up, vrep.simx_opmode_oneshot)
    wait()
    vrep.simxSetJointTargetPosition(clientID, coxa2_joint, leg_2.coxa_default, vrep.simx_opmode_oneshot)
    wait()
    vrep.simxSetJointTargetPosition(clientID, femur2_joint, leg_2.femur_default, vrep.simx_opmode_oneshot)
    wait()
    
    vrep.simxSetJointTargetPosition(clientID, femur3_joint, leg_3.femur_up, vrep.simx_opmode_oneshot)
    wait()
    vrep.simxSetJointTargetPosition(clientID, coxa3_joint, leg_3.coxa_default, vrep.simx_opmode_oneshot)
    wait()
    vrep.simxSetJointTargetPosition(clientID, femur3_joint, leg_3.femur_default, vrep.simx_opmode_oneshot)
    wait()

    vrep.simxSetJointTargetPosition(clientID, femur4_joint, leg_4.femur_up, vrep.simx_opmode_oneshot)
    wait()
    vrep.simxSetJointTargetPosition(clientID, coxa4_joint, leg_4.coxa_default, vrep.simx_opmode_oneshot)
    wait()
    vrep.simxSetJointTargetPosition(clientID, femur4_joint, leg_4.femur_default, vrep.simx_opmode_oneshot)
    wait()
    
    leg_1.clear_coxa_value()
    leg_2.clear_coxa_value()
    leg_3.clear_coxa_value()
    leg_4.clear_coxa_value()
    
def single_step_forward():

    movement_1(leg_1,leg_2)
    movement_2(leg_1)
    movement_3(leg_1, -1,-1,-1,-1)
    movement_4(leg_3)
    movement_5(leg_4)
    movement_6(leg_4, -1,-1,-1,-1)
    
def single_step_back():
    
    movement_1(leg_2,leg_1)
    movement_2(leg_2)
    movement_3(leg_2,1,1,1,1)
    movement_4(leg_4)
    movement_5(leg_3)
    movement_6(leg_3,1,1,1,1)
    
def right_movement():

    side_movement(RIGHT)
    
def left_movement():

    side_movement(LEFT)


set_init()
wait()
print("READY TO COMMANDS")
while(1):

    char = str(list(str(getch()))[2])

    if(char == "w"):
        single_step_forward()
    if(char == "s"):
        single_step_back()
    if(char == "d"):
        right_movement()
    if(char == "a"):
        left_movement()
    if(char == "c"):
        exit()
