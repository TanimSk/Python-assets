import argparse
import os
import queue
import sounddevice as sd
import vosk
import sys
import json


class VoiceRecognition(object):
    def __init__(self):
        self.q = queue.Queue()

        parser = argparse.ArgumentParser(add_help=False)
        parser.add_argument(
            '-l', '--list-devices', action='store_true',
            help='show list of audio devices and exit')
        self.__args, remaining = parser.parse_known_args()
        if self.__args.list_devices:
            print(sd.query_devices())
            parser.exit(0)
        parser = argparse.ArgumentParser(
            description=__doc__,
            formatter_class=argparse.RawDescriptionHelpFormatter,
            parents=[parser])
        parser.add_argument(
            '-f', '--filename', type=str, metavar='FILENAME',
            help='audio file to store recording to')
        parser.add_argument(
            '-m', '--model', type=str, metavar='MODEL_PATH',
            help='Path to the model')
        parser.add_argument(
            '-d', '--device', type=self.int_or_str,
            help='input device (numeric ID or substring)')
        parser.add_argument(
            '-r', '--samplerate', type=int, help='sampling rate')
        self.__args = parser.parse_args(remaining)

        try:
            if self.__args.model is None:
                self.__args.model = "model"
            if not os.path.exists(self.__args.model):
                print("Please download a model for your language from https://alphacephei.com/vosk/models")
                print("and unpack as 'model' in the current folder.")
                parser.exit(0)
            if self.__args.samplerate is None:
                device_info = sd.query_devices(self.__args.device, 'input')
                # soundfile expects an int, sounddevice provides a float:
                self.__args.samplerate = int(device_info['default_samplerate'])

            self.__model = vosk.Model(self.__args.model)

            if self.__args.filename:
                self.__dump_fn = open(self.__args.filename, "wb")
            else:
                self.__dump_fn = None
        except Exception as e:
            parser.exit(type(e).__name__ + ': ' + str(e))

    def int_or_str(self, text):
        """Helper function for argument parsing."""
        try:
            return int(text)
        except ValueError:
            return text

    def callback(self, indata, frames, time, status):
        """This is called (from a separate thread) for each audio block."""
        if status:
            print(status, file=sys.stderr)
        self.q.put(bytes(indata))

    def get_text(self):
        with sd.RawInputStream(samplerate=self.__args.samplerate, blocksize=8000, device=self.__args.device, dtype='int16',
                               channels=1, callback=self.callback):

            rec = vosk.KaldiRecognizer(self.__model, self.__args.samplerate)
            while True:
                data = self.q.get()
                if rec.AcceptWaveform(data):
                    result = json.loads(rec.Result())['text']
                    if result != "":
                        return result
                # else:
                #     print(rec.PartialResult())
                if self.__dump_fn is not None:
                    self.__dump_fn.write(data)


if __name__ == '__main__':
    while True:
        print(VoiceRecognition().get_text())
