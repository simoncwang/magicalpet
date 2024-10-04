import argparse
import os

def main():
    parser = argparse.ArgumentParser()
    
    # select either 'audio' or 'video'
    parser.add_argument('mode', choices=['audio', 'video'])

    args = parser.parse_args()

    if args.mode == 'audio':
        # audio detection script
        os.system("python3 audio_detection.py")
    elif args.mode == 'video':
        # video detection script
        os.system("python3 video_detection.py")

if __name__ == "__main__":
    main()
