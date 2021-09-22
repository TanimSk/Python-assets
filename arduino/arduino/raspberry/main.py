import get_data
import _render_image
from soundplayer import SoundPlayer
import _printer
import get_hr_sp
from pygame import mixer

mixer.init()
mixer.music.set_volume(1)

img = _render_image.PrintImage()
printer = _printer.Printer()

while True:
    data = get_data.get_data()

    if data[0] == "data":
        img.PHONE_NUMBER = data[1]
        img.BODY_TEMP = data[2]
        

    elif data[0] == "audio":
        path = f"./audio/{data[1]}"
        mixer.music.load(path)  
        channel = mixer.music.play()
        while mixer.music.get_busy() == True:
            continue
    
    elif data[0] == "sensor":
        print("measuring started")
        hr, sp = get_hr_sp.get_heart_rate()
        get_data.send_data(f"hr: {hr} sp:{sp}")
        img.OXYZEN_LEVEL = sp
        img.HEART_BEAT = hr
        print("ended")
    
    elif data[0] == "print":
        img.write()
        print("printing...")
        printer.PATH = "./report.png"
        printer.PROJECT_NAME = "report"
        printer.start()

