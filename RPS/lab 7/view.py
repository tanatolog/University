from tkinter import *
import tkinter.messagebox as messagebox
import tkinter.ttk as ttk

class View(ttk.Frame):

    def __init__(self, parent): #constructor
        super().__init__(parent)

        self.controller = None
        self.number_input = None
        self.grid_columnconfigure(0, weight=1)

    def set_controller(self, controller):
        self.controller = controller

    def create_controls(self):
        
        label = Label(self, text="Число")
        label.grid(row=0, column=0, padx=10, sticky="w")

        self.number_input = Entry(self)
        self.number_input.grid(row=1, column=0, padx=10, pady=(0, 10), sticky="we")

        check_button = ttk.Button(self, text='Проверить на простоту', command=self.check)
        check_button.grid(row=2, column=0, padx=10, pady=2, sticky="we")
        
        factorize_button = ttk.Button(self, text='Разложение на простые множители', command=self.factorize)
        factorize_button.grid(row=3, column=0, padx=10, pady=2, sticky="we")
        
        random_prime_button = ttk.Button(self, text='Случайное простое число', command=self.random_prime)
        random_prime_button.grid(row=4, column=0, padx=10, pady=2, sticky="we")
        
        next_prime_button = ttk.Button(self, text='Записать в файл 100 простых чисел', command=self.generate_primes)
        next_prime_button.grid(row=5, column=0, padx=10, pady=2, sticky="we")

        self.grid(row=0, column=0, pady=10, padx=10,  sticky="we")
    
    def check(self):
        if self.controller:
            if self.number_input.get():
                self.controller.is_prime(self.number_input.get())

    def factorize(self):
        if self.controller:
            if self.number_input.get():
                self.controller.prime_factorization(self.number_input.get())
    
    def random_prime(self):
        if self.controller:
            self.controller.get_random_prime()

    def generate_primes(self):
        if self.controller:
            if self.number_input.get():
                self.controller.generate_primes(self.number_input.get())

    def show_result(self, mtype, msg):
        if mtype == 0:
            messagebox.showinfo("Результат", msg)
        elif mtype == 1: 
            messagebox.showerror("Ошибка", msg)

    def set_input_value(self, v):
        self.number_input.delete(0, END)
        self.number_input.insert(0, v)