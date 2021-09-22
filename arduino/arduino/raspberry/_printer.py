import cups


class Printer(object):
    def __init__(self) -> None:

        self.conn = cups.Connection()
        self.__printer = list(self.conn.getPrinters().keys())[0]

        self.PATH = None
        self.PROJECT_NAME = None

    def start(self) -> None:
        self.conn.printFile((self.__printer), self.PATH, self.PROJECT_NAME, {})
