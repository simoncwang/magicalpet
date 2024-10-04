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

def displayAnalysis(img, emotion_detector, last_emotion_data):
    # analyzing the emotions in the image including bounding box
    analysis = emotion_detector.detect_emotions(img)
    

    if analysis:
        # getting the dominant emotion and its score
        dominant_emotion, emotion_score = emotion_detector.top_emotion(img)

        # Check if 20 seconds have passed since the last emotion change
        if time.time() - last_emotion_data["last_update"] >= 20:
            # Update the current emotion after 20 seconds
            last_emotion_data["emotion"] = dominant_emotion
            last_emotion_data["last_update"] = time.time()
        else:
            # Keep the last emotion if 20 seconds haven't passed
            dominant_emotion = last_emotion_data["emotion"]

        # parameters for the rectangles we want to draw
        color = (0, 255, 0)   # in b,g,r format
        thickness = 2

        # drawing a rectangle around all the detected faces
        for face in analysis:
            # getting the bounding box coordinates
            box = face["box"]
            x, y, w, h = box

            # drawing the rectangle
            start = (x, y)
            end = (x + w, y + h)
            img = cv2.rectangle(img, start, end, color, thickness)

            # writing the dominant emotion next to the rectangle
            cv2.putText(img, dominant_emotion + ": " + str(emotion_score), (x, y - 10),
                        cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
    
    # return the image with analysis
    return img