import time

from DFRobot_RaspberryPi_Expansion_Board import DFRobot_Expansion_Board_IIC as Board
from DFRobot_RaspberryPi_Expansion_Board import DFRobot_Expansion_Board_Servo as Servo

board1 = Board(1, 0x10)    # Select i2c bus 1, set address to 0x10
board2 = Board(1, 0x11)
board3 = Board(1, 0x12)

servo1 = Servo(board1)
servo2 = Servo(board2)
servo3 = Servo(board3)

''' print last operate status, users can use this variable to determine the result of a function call. '''
def print_board_status1():
  if board1.last_operate_status == board1.STA_OK:
    print("board status: everything ok")
  elif board1.last_operate_status == board1.STA_ERR:
    print("board status: unexpected error")
  elif board1.last_operate_status == board1.STA_ERR_DEVICE_NOT_DETECTED:
    print("board status: device not detected")
  elif board1.last_operate_status == board1.STA_ERR_PARAMETER:
    print("board status: parameter error")
  elif board1.last_operate_status == board1.STA_ERR_SOFT_VERSION:
    print("board status: unsupport board framware version")

def print_board_status2():
  if board2.last_operate_status == board2.STA_OK:
    print("board status: everything ok")
  elif board2.last_operate_status == board2.STA_ERR:
    print("board status: unexpected error")
  elif board2.last_operate_status == board2.STA_ERR_DEVICE_NOT_DETECTED:
    print("board status: device not detected")
  elif board2.last_operate_status == board2.STA_ERR_PARAMETER:
    print("board status: parameter error")
  elif board2.last_operate_status == board2.STA_ERR_SOFT_VERSION:
    print("board status: unsupport board framware version")

def print_board_status3():
  if board3.last_operate_status == board3.STA_OK:
    print("board status: everything ok")
  elif board3.last_operate_status == board3.STA_ERR:
    print("board status: unexpected error")
  elif board3.last_operate_status == board3.STA_ERR_DEVICE_NOT_DETECTED:
    print("board status: device not detected")
  elif board3.last_operate_status == board3.STA_ERR_PARAMETER:
    print("board status: parameter error")
  elif board3.last_operate_status == board3.STA_ERR_SOFT_VERSION:
    print("board status: unsupport board framware version")

def main(angle1, angle2, angle3):

  print(angle1, angle2, angle3)
  while board1.begin() != board1.STA_OK:    # Board begin and check board status
    print_board_status1()
    print("board begin faild")
    time.sleep(2)
  print("board begin success")
  
  while board2.begin() != board2.STA_OK:    # Board begin and check board status
    print_board_status2()
    print("board begin faild")
    time.sleep(2)
  print("board begin success")
  
  while board3.begin() != board3.STA_OK:    # Board begin and check board status
    print_board_status3()
    print("board begin faild")
    time.sleep(2)
  print("board begin success")
  

  servo1.begin()   # servo control begin
  servo2.begin()
  servo3.begin()
  while True:
    print("servo move to 0")
    servo1.move(board1.ALL, 0)
    time.sleep(1)
    print("servo move to 180")
    servo1.move(board1.ALL, 180)
    time.sleep(1)

    print("part servos move to 0")
    servo1.move(0, 0)  #pwm0
    servo2.move(1, 0)  #pwm1
    servo3.move(2, 0)  #pwm2
    #servo.move(3, 0)  #pwm3
    time.sleep(1)
    print("part servos move to 180")
    servo1.move(0, 180)  #pwm0
    servo2.move(1, 180)  #pwm1
    servo3.move(2, 180)  #pwm2
    #servo.move(3, 180)  #pwm3
    time.sleep(1)