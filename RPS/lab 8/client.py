from tkinter import *

from client_stuff.view import View
from client_stuff.controller import Controller
from client_stuff.model import Model


class App(Tk):
    def __init__(self):
        super().__init__()

        model = Model()
        connected = model.connect()

        if not connected:
            print("Server is not connected")
            self.destroy()
            return

        self.title('Простые числа')
        self.geometry('300x190')
        self.resizable(False, False)
        self.protocol("WM_DELETE_WINDOW", self.on_closing)

        view = View(self)
        self.controller = Controller(model, view)
        view.set_controller(self.controller)

        view.create_controls()
        self.grid_columnconfigure(0, weight=1)

    def on_closing(self):
        self.destroy()


if __name__ == '__main__':
    app = App()
    app.mainloop()