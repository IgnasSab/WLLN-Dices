import serial
import time
import cv2
import numpy as np




##################################################
# Program to count islands in boolean 2D matrix

class Graph:

    def __init__(self, g):
        self.ROW = len(g)
        self.COL = len(g[0])
        self.graph = g
        self.pixel_count = 0
        self.decent_pixel_count = False

    # A function to check if a given cell
    # (row, col) can be included in DFS
    def isSafe(self, i, j, visited):
        # row number is in range, column number
        # is in range and value is 1
        # and not yet visited
        return (i >= 0 and i < self.ROW and
                j >= 0 and j < self.COL and
                not visited[i][j] and self.graph[i][j])

    # A utility function to do DFS for a 2D
    # boolean matrix. It only considers
    # the 8 neighbours as adjacent vertices

    def DFS(self, i, j, visited):
        if (self.pixel_count > 500):
            return
        elif (self.pixel_count > 200):
            self.decent_pixel_count = True
        else:
            self.pixel_count += 1

        # These arrays are used to get row and
        # column numbers of 8 neighbours
        # of a given cell
        rowNbr = [-1, -1, -1,  0, 0,  1, 1, 1]
        colNbr = [-1,  0,  1, -1, 1, -1, 0, 1]

        # Mark this cell as visited
        visited[i][j] = True

        # Recur for all connected neighbours
        for k in range(8):
            if self.isSafe(i + rowNbr[k], j + colNbr[k], visited):
                self.DFS(i + rowNbr[k], j + colNbr[k], visited)

    # The main function that returns
    # count of islands in a given boolean
    # 2D matrix

    def countIslands(self):
        # Make a bool array to mark visited cells.
        # Initially all cells are unvisited
        visited = [[False for j in range(self.COL)]for i in range(self.ROW)]

        # Initialize count as 0 and traverse
        # through the all cells of
        # given matrix
        count = 0
        for i in range(self.ROW):
            for j in range(self.COL):
                # If a cell with value 1 is not visited yet,
                # then new island found
                if visited[i][j] == False and self.graph[i][j] == 1:
                    # Visit all cells in this island
                    # and increment island count
                    self.DFS(i, j, visited)
                    self.pixel_count = 0
                    if (self.pixel_count > 500):
                        return -1
                    count += 1
                    if count > 6:
                        return count
                    elif self.decent_pixel_count == True:
                        return 6

        return count

x_left = 30 # 0
x_right = 600 # 640
y_up = 0 # 0
y_down = 460 # 480
light_level = 20
scale = 0.5
x_scaled = int(scale * (x_right - x_left))
y_scaled = int(scale * (y_down - y_up))
def preprocess_image(img):
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    img = img[y_up:y_down, x_left:x_right] 
    img = cv2.blur(img, (5, 5))
    threshold = (np.max(img) - np.min(img)) / 2 + np.median(img)
    for i_ in range(0, len(img)):
        for j_ in range(0, len(img[0])):
            if img[i_][j_] > threshold:
                img[i_][j_] = 255
            else:
                img[i_][j_] = 0
    cv2.imwrite('/home/ignas/Desktop/WLLN_Dice/dice_bw.png', img);
    img = img / 255.0 
    return img

average_threshold = 800
def predict(img):
    print("sum: ", np.sum(img))
    g = Graph(img)
    average = np.sum(img)
    num_islands = g.countIslands()
    if (num_islands < 1 or num_islands > 6):
        return -1
    else:
        return num_islands
##################################################

arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=1)
# arduino = serial.Serial(port='COM10', baudrate=9600, timeout=1)

video_capture = cv2.VideoCapture(0) # Open a connection to the camera (0 is usually the default camera)
video_capture.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
video_capture.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

if not video_capture.isOpened():
        print("Error: Could not open video.")

def capture_frame():
    # Capture a single frame from the video stream
    ret, frame = video_capture.read()
    if ret:
        # Save the captured frame as an image file
        try:   
            cv2.imwrite('/home/ignas/Desktop/WLLN_Dice/dice.png', frame)
        except (e):
            print("Error occurred, couldn't write the file")
        print("Captured frame")
    else:
        print("Failed to capture frame")


def captureFrame():
    capture_frame()
    return processFrame()

def processFrame():
    try:
        img = cv2.imread('/home/ignas/Desktop/WLLN_Dice/dice.png')
    except (e):
        print("Couldn't read the file")

    img = preprocess_image(img)
    pip_num = predict(img) # Predict the number of pips
    print("Frame processed") # TODO
    print(pip_num)
    return pip_num


arduino.write(bytes("START", 'utf-8')) # Send a starting signal to arduino
ret, frame = video_capture.read() # Capture the first frame
print("READY")  
while True: # Infinite loop
    if arduino.in_waiting > 0:  
        line = arduino.readline().decode('utf-8') # Read data from arduino
        if (line.endswith('\n') and line.strip() == "CAPTURE"):  
            # Capture the frame
            pip_num = captureFrame()
            arduino.write(bytes(str(pip_num), 'utf-8'))
        else:
            print(line)