import get_data
import _print_image
import playsound

img = _print_image.PrintImage()

while True:
    data = get_data.get_data()

    if data[0] == "data":
        img.PHONE_NUMBER = data[1]
        img.BODY_TEMP = data[2]
        img.OXYZEN_LEVEL = data[3]
        img.HEART_BEAT = data[4]
        img.write()
        print("write")

    elif data[0] == "audio":
        path = f"audio/{data[1]}"
        playsound.playsound(path)

