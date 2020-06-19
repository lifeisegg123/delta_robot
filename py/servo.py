import time

from DFRobot_RaspberryPi_Expansion_Board import DFRobot_Expansion_Board_IIC as Board
from DFRobot_RaspberryPi_Expansion_Board import DFRobot_Expansion_Board_Servo as Servo

board = Board(1, 0x10)    # Select i2c bus 1, set address to 0x10
servo = Servo(board)



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
  
  servo.move(0,map(0))
  servo.move(1,map(0))
  servo.move(2,map(0))
  time.sleep(2)

def set():
  
  servo.move(0,map(0))
  servo.move(1,map(0))
  servo.move(2,map(0))
  time.sleep(1)
  print(map(0))
  
if __name__ == "__main__":
  connectBoard()
  while True:
    set()