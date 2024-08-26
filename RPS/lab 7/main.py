from tkinter import *

from view import View
from controller import Controller
import model_prime as model_prime


class App(Tk):
    def __init__(self):
        super().__init__()

        self.title('Простые числа')
        self.geometry('300x190')
        self.resizable(False, False)

        view = View(self)

        self.controller = Controller(model_prime, view)

        view.set_controller(self.controller)

        view.create_controls()

        self.grid_columnconfigure(0, weight=1)

        self.protocol("WM_DELETE_WINDOW", self.on_closing)

    def on_closing(self):
        self.destroy()


if __name__ == '__main__':
    app = App()
    app.mainloop()