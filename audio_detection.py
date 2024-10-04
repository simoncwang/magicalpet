from openai import OpenAI
import sounddevice as sd
from scipy.io.wavfile import write

fs = 44100  # Sample rate
seconds = 3  # Duration of recording

myrecording = sd.rec(int(seconds * fs), samplerate=fs, channels=1)
sd.wait()  # Wait until recording is finished
write('output.wav', fs, myrecording)  # Save as WAV file

api_key = "sk-uLn8HbnfZzfQw5HUr_RBczOgxAFMYU0FyLAowWULA-T3BlbkFJmT9eTkORRDAu1rDvVEiFihxTVfp09bROYLpUiq8zQA"
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
            "text": "Based on the following text, am I feeling positive, negative, or neutral?"
            },
            {
            "type": "text",
            "text": transcription
            }
        ]}
  ]
)

print(completion.choices[0].message.content)

# f = open("output.txt", "w")
# f.write(transcription)