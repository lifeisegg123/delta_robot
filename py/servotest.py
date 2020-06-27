import time
import math
from DFRobot_RaspberryPi_Expansion_Board import DFRobot_Expansion_Board_IIC as Board
from DFRobot_RaspberryPi_Expansion_Board import DFRobot_Expansion_Board_Servo as Servo

board = Board(1, 0x10)    # Select i2c bus 1, set address to 0x10
servo = Servo(board)

pi = 3.141592653
sin120 = math.sqrt(3) / 2.0
sin30  = 0.5
tan30  = 1.0 / math.sqrt(3)
hodo =  pi / 180
cos120 = -0.5
tan60  = math.sqrt(3)

e  =  24
f  =  75
re = 314.6
rf = 100

def angle_yz(x0, y0, z0, theta=None):



    y1 = -0.5 * 0.57735 * f
    y0 -= 0.5 * 0.57735 * e

    a = (x0 * x0 + y0 * y0 + z0 * z0 + rf * rf - re * re - y1 * y1) / (2.0 * z0)
    b = (y1 - y0) / z0
    d = -(a + b * y1) * (a + b * y1) + rf * (b * b * rf + rf)

    yj = (y1 - a * b - math.sqrt(d)) / (b * b + 1)
    zj = a + b * yj
    theta = math.atan(-zj / (y1 - yj)) * 180.0 / pi + (180.0 if yj > y1 else 0.0)
    return [0, theta]

def inverse(x0, y0, z0):
    theta1 = 0
    theta2 = 0
    theta3 = 0


    state = angle_yz(x0, y0, z0)

    if state[0] == 0:

        theta1 = state[1]
        state = angle_yz(x0*cos120 + y0 * sin120, y0 * cos120 - x0 * sin120, z0, theta2)
        theta2 = state[1]
        state = angle_yz(x0*cos120 - y0 * sin120, y0 * cos120 + x0*sin120, z0, theta3)
        theta3 = state[1]

    return [theta1, theta2, theta3, state[0]]


def map(x, in_min = 90, in_max = -90, out_min = 0, out_max = 180):
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min


''' print last operate status, users can use this variable to determine the result of a function call. '''
def print_board_status():
  if board.last_operate_status == board.STA_OK:
    print("board status: everything ok")
  elif board.last_operate_status == board.STA_ERR:
    print("board status: unexpected error")
  elif board.last_operate_status == board.STA_ERR_DEVICE_NOT_DETECTED:
    print("board status: device not detected")
  elif board.last_operate_status == board.STA_ERR_PARAMETER:
    print("board status: parameter error")
  elif board.last_operate_status == board.STA_ERR_SOFT_VERSION:
    print("board status: unsupport board framware version")


def connectBoard():

  if board.begin() != board.STA_OK:    # Board begin and check board status
    print_board_status()
    print("board begin faild")
    return 0
  print("board begin success")

  print_board_status()
  servo.begin()   # servo control begin
  return 1

pre_angles = [0, 0, 0]
def moveServo(theta1, theta2, theta3, splitor):
  global pre_angles
  
  if (splitor == 1):
    diff = [theta1-pre_angles[0], theta2-pre_angles[1], theta3-pre_angles[2]]
    
    for i in range(1,51):
      servo.move(0, map(pre_angles[0] + diff[0] * i / 50))
      servo.move(1, map(pre_angles[1] + diff[1] * i / 50))
      servo.move(2, map(pre_angles[2] + diff[2] * i / 50))
      time.sleep(0.001)
    time.sleep(0.05)

  servo.move(0, map(theta1))  #pwm0
  servo.move(1, map(theta2))  #pwm1
  servo.move(2, map(theta3))  #pwm2)
  time.sleep(0.01)
  pre_angles = [theta1, theta2, theta3]
  return 1
def set0():
  
  servo.move(0,map(-20))
  servo.move(1,map(-20))
  servo.move(2,map(-20))
  time.sleep(2)

def set():
  
  servo.move(0,map(0))
  servo.move(1,map(0))
  servo.move(2,map(0))
  time.sleep(1)
  print(map(0))
def testMove(x, y, z):
    thetas = inverse(x, y, z)
    moveServo(thetas[0], thetas[1], thetas[2], 0)
def drawRectangle():
    i = -20
    j = -20
    while i < 21:
        thetas = inverse(i, j, -250)
        moveServo(thetas[0], thetas[1], thetas[2], 0)
        i += 1
    while j < 21:
        thetas = inverse(i, j, -250)
        moveServo(thetas[0], thetas[1], thetas[2], 0)
        j += 1
    while i > -21:
        thetas = inverse(i, j, -250)
        moveServo(thetas[0], thetas[1], thetas[2], 0)
        i -= 1
    while j > -21:
        thetas = inverse(i, j, -250)
        moveServo(thetas[0], thetas[1], thetas[2], 0)
        j -= 1
if __name__ == "__main__":
  connectBoard()
  while True:
    print("select mode(1: move to certain Position, 2: Draw Rectangle, 0: finish)")
    selector = int(input())
    if selector == 1:
      print(1)
      while True:
        print("while")
        print("x = ")
        x = int(input())
        print("y = ")
        y = int(input())
        print("z = ")
        z = int(input())
        testMove(x, y, z) 
    elif selector == 2:
      set()
      for i in range(0,10):
        drawRectangle()
    elif selector == 3:
      break
