from cv2 import VideoCapture,imshow,imwrite,waitKey,destroyAllWindows
from cv2 import *
import cv2
import os
# fixing the path for ffmpeg
os.environ["IMAGEIO_FFMPEG_EXE"] = "/Users/simon/anaconda3/envs/mlproj/lib/python3.11/site-packages/ffmpeg"
from fer import FER
import time


def captureImage():
    # number of frames to ramp up before taking final picture
    ramp_frames = 10

    # initializing camera
    cam = VideoCapture(1)

    # "warming up" the camera for a few frames to get a better final image
    for i in range(ramp_frames):
        temp = cam.read()
    
    # reading input from the camera
    result, image = cam.read()

    # showing output if no error
    if result:
        return image
    else:
        print("image read error")

def displayAnalysis(img, emotion_detector):
    # analyzing the emotions in the image including bounding box
    analysis = emotion_detector.detect_emotions(img)

    # getting the dominant emotion and its score
    dominant_emotion, emotion_score = emotion_detector.top_emotion(img)

    # parameters for the rectangles we want to draw
    color = (0,255,0)   # in b,g,r format
    thickness = 2

    # drawing a rectangle around all the detected faces
    for face in analysis:
        # getting the bounding box coordinates
        box = face["box"]

        # getting x,y,width,height of the box
        x = box[0]
        y = box[1]
        w = box[2]
        h = box[3]

        # getting start point x,y coordinates
        start = (x, y)
        # getting end point x,y coordinates
        end = (x+w, y+h)

        # drawing the rectangle
        img = cv2.rectangle(img, start, end, color, thickness)

        # getting the emotions
        emotions = analysis[0]["emotions"]

        # writing the emotion next to the rectangle
        # cv2.putText(img, str(emotions), (x, y-10), cv2.FONT_HERSHEY_SIMPLEX, 1, (0,255,0), 2)
        cv2.putText(img, dominant_emotion + ": "  + str(emotion_score), (x, y-10), cv2.FONT_HERSHEY_SIMPLEX, 1, (0,255,0), 2)
    
    # return the image
    return img