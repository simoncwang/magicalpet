import sounddevice as sd
import serial
import time
import platform
import os
from openai import OpenAI
from scipy.io.wavfile import write
from dotenv import load_dotenv

# Load the .env file
load_dotenv()

# Access the API key
api_key = os.getenv('API_KEY')

fs = 44100  # Sample rate
seconds = 10  # Duration of recording

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

print(completion.choices[0].message.content)

if (completion.choices[0].message.content == "positive"):
  print("You are feeling positive.")
  arduino.write(str.encode('0'))

elif (completion.choices[0].message.content == "negative"):
  print("You are feeling negative.")
  arduino.write(str.encode('1'))