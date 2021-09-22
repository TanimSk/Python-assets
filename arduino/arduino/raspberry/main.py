import get_data
from _print_image import PrintImage
import _printer
import get_hr_sp
import pathlib
from pygame import mixer

mixer.init()
mixer.music.set_volume(1)

img = PrintImage()

body_temp = "Not given"
phone_number = "Not given"
report = "Not given"
heart_rate = "Not given"
oxygen_level = "Not given"

printer = _printer.Printer()

print("started")

while True:
    data = get_data.get_data()

    if data['type'] == "data":
        body_temp = data['body_temp']
        phone_number = data['phone_number']
        report = data['report']
        print(body_temp, phone_number, report)

    elif data['type'] == "audio":
        path = f"{pathlib.Path(__file__).resolve().parent}/audio/{data['filename']}"
        print(f"playing audio {data['filename']}")
        mixer.music.load(path)
        channel = mixer.music.play()
        while mixer.music.get_busy() == True:
            continue
    
    elif data['type'] == "sensor":
        print("measuring started")
        hr, sp = get_hr_sp.get_heart_rate()
        get_data.send_data(f"hr: {hr} sp:{sp}")
        oxygen_level = sp
        heart_rate = hr
        print("ended")
    
    elif data['type'] == "print":
        img.write(phone_number, body_temp, oxygen_level,heart_rate, report)
        print("printing...")
        __PATH = f"{pathlib.Path(__file__).resolve().parent}/report.png"
        __PROJECT_NAME = "report"
        printer.start(__PATH,__PROJECT_NAME)
