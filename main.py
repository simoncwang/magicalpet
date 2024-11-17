import serial
import os
import time
import subprocess

# Open the serial port (adjust to your correct port)
ser = serial.Serial('/dev/cu.usbserial-0001', 9600)  # Adjust with your ESP32's serial port
time.sleep(2)  # Wait for the serial connection to establish

# Initialize process variables
audio_process = None
video_process = None

def run_detection(mode):
    global audio_process, video_process

    if mode == 'audio':
        # If video is running, kill it before starting audio
        if video_process:
            print("Killing video process...")
            video_process.terminate()  # Terminate video detection script
            video_process = None  # Reset video process variable

        # Run the audio detection script
        if not audio_process or audio_process.poll() is not None:  # Check if audio is not already running
            print("Starting audio detection...")
            audio_process = subprocess.Popen(["python3", "audio_detection.py"])  # Start the audio process

    elif mode == 'video':
        # If audio is running, kill it before starting video
        if audio_process:
            print("Killing audio process...")
            audio_process.terminate()  # Terminate audio detection script
            audio_process = None  # Reset audio process variable

        # Run the video detection script
        if not video_process or video_process.poll() is not None:  # Check if video is not already running
            print("Starting video detection...")
            video_process = subprocess.Popen(["python3", "video_detection.py"])  # Start the video process

def main():
    while True:
        if ser.in_waiting > 0:
            mode = ser.readline().decode().strip()  # Read the value from the serial input
            
            if mode == "1":
                print("Button 1 Pressed: Running Audio Detection")
                run_detection("audio")
            elif mode == "2":
                print("Button 2 Pressed: Running Video Detection")
                run_detection("video")
        
        time.sleep(0.1)  # Small delay to avoid excessive CPU usage

if __name__ == "__main__":
    main()
