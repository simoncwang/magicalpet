import cv2
from video_helper import *


# using MTCNN (multi task cascaded CNN)
# MTCNN detects faces and facial landmarks on images
emotion_detector = FER(mtcnn=True)  

# Initialize last emotion data to hold the emotion and last update time
last_emotion_data = {"emotion": "neutral", "last_update": time.time()}

# continuously capturing webcam feed until user presses esc
cam = cv2.VideoCapture(0)  # Use 0 for the default camera

if not cam.isOpened():
    print("Error: Could not open webcam.")
    exit()

while True:
    result, img = cam.read()
    
    if not result:
        print("Error: Could not read image from webcam.")
        break  # Exit the loop if the image capture fails
    
    # Display analysis results
    cv2.imshow('my webcam', displayAnalysis(img, emotion_detector, last_emotion_data))
    
    if cv2.waitKey(1) == 27:  # esc to quit
        break

cam.release()
cv2.destroyAllWindows()