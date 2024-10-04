# using FER library to continuously detect emotions in a live feed

import cv2
from util import *


# using MTCNN (multi task cascaded CNN)
# MTCNN detects faces and facial landmarks on images
emotion_detector = FER(mtcnn=True)   # NOTE: setting this to false uses Haar

# Initialize last emotion data to hold the emotion and last update time
last_emotion_data = {"emotion": "neutral", "last_update": time.time()}

# continuously capturing webcam feed until user presses esc
cam = cv2.VideoCapture(1)

while True:
    result, img = cam.read()
    cv2.imshow('my webcam', displayAnalysis(img,emotion_detector))
    if cv2.waitKey(1) == 27: 
        break  # esc to quit
        
cam.release()
cv2.destroyAllWindows()


# # saving the image
# imwrite("image.png", img)