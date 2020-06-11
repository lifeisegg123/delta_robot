import time

from DFRobot_RaspberryPi_Expansion_Board import DFRobot_Expansion_Board_IIC as Board
from DFRobot_RaspberryPi_Expansion_Board import DFRobot_Expansion_Board_Servo as Servo

board = Board(1, 0x10)    # Select i2c bus 1, set address to 0x10

servo1 = Servo(board)
servo2 = Servo(board)
servo3 = Servo(board)

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
    time.sleep(2)
    return 0
  print("board begin success")

  servo1.begin()   # servo control begin
  servo2.begin()
  servo3.begin()
  return 1
def moveServotest():

    print("servo move to 0")
    servo1.move(board.ALL, 0)
    time.sleep(1)
    print("servo move to 180")
    servo1.move(board.ALL, 180)
    time.sleep(1)

def moveServo(theta1, theta2, theta3):

    print("start moving")

    servo1.move(0, theta1)  #pwm0
    servo2.move(1, theta2)  #pwm1
    servo3.move(2, theta3)  #pwm2
    #servo.move(3, 0)  #pwm3
    time.sleep(1)
    return 1