import playsound

class Sound(object):
    def __init__(self) -> None:
        self.path = None

    def play(self):
        playsound(self.path)


if __name__ == "__main__":
    Sound().play()
