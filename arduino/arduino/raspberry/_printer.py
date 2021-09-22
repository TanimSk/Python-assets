import cups


class Printer(object):
    def __init__(self) -> None:

        self.conn = cups.Connection()
        self.__printer = list(self.conn.getPrinters().keys())[0]

        self.PATH = None
        self.PROJECT_NAME = None

    def start(self, path, project_name) -> None:
     self.PATH = path
     self.PROJECT_NAME = project_name
     self.conn.printFile(self.__printer, self.PATH, self.PROJECT_NAME, {})
     
if __name__ == '__main__':
    import os
    
    Printer().start(f'{os.getcwd()}/report.png', 'report')