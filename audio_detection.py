import sounddevice as sd
import serial
import time
import platform
import os
from openai import OpenAI
from pathlib import Path
from scipy.io.wavfile import write
from dotenv import load_dotenv

# Load the .env file
load_dotenv()

# Access the API key
api_key = os.getenv('API_KEY')

fs = 44100  # Sample rate
seconds = 3  # Duration of recording

# initialize the serial port for the Arduino based on the operating system
if platform.system() == "Darwin":  # macOS
    arduino = serial.Serial(port='/dev/cu.usbserial-0001', baudrate=9600)
elif platform.system() == "Windows":  # Windows
    arduino = serial.Serial(port='COM3', baudrate=9600)
time.sleep(2)

myrecording = sd.rec(int(seconds * fs), samplerate=fs, channels=1)
sd.wait()  # Wait until recording is finished
write('output.wav', fs, myrecording)  # Save as WAV file

client = OpenAI(api_key=api_key)

audio_file = open("output.wav", "rb")
transcription = client.audio.transcriptions.create(
  model="whisper-1", 
  file=audio_file, 
  response_format="text"
)

completion = client.chat.completions.create(
  model="gpt-4o",
  messages=[
    {"role": "system", "content": "You are skilled at detecting emotions from transcribed speech."},
    {"role": "user",
        "content": [
            {
            "type": "text",
            "text": "Based on the following text, am I feeling positive, negative, or neutral? Give me a one word phrase that is all lower case with no punctuation"
            },
            {
            "type": "text",
            "text": transcription
            }
        ]}
  ]
)

patient_mood = completion.choices[0].message.content # Get the response from the AI

response = client.chat.completions.create(
  model="gpt-4o",
  messages=[
    {"role": "system", "content": "You are a counselor. Encourage the patient in 1 sentence with positive words if they are feeling negative. Otherwise, encourage them in 1 sentence to keep up the good energy if they feel positive."},
    {"role": "user",
        "content": [
            {
            "type": "text",
            "text": transcription
            }
        ]}
  ]
)

ai_response = response.choices[0].message.content
speech_file_path = "speech.mp3"
response = client.audio.speech.create(
  model="tts-1",
  voice="fable",
  input=ai_response
)

response.stream_to_file(speech_file_path)

print("patient mood: ", patient_mood)

if (patient_mood == "positive"):
  print("You are feeling positive.")
  arduino.write(str.encode('0'))

elif (patient_mood == "negative"):
  print("You are feeling negative.")
  arduino.write(str.encode('1'))