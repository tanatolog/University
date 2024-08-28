class Controller:
    def __init__(self, model, view): # constructor
        self.model = model
        self.view = view      

    def int_conversion(self, value):
        """conversion to int"""
        try:
            v = int(value)
            return v
        except ValueError:
            return None

    def is_prime(self, value):
        """checking for a prime"""
        v = self.int_conversion(value)

        if (v is None) or (v < 0):
            self.view.show_result(1, "Введите неотрицательное целое число")
            return
        
        if v == 1 or v == 0:
            self.view.show_result(0, "Число не является ни простым ни составным")
        else:
            try:
                self.view.show_result(0, "Число простое" if self.model.is_prime(v) else "Число составное")
            except Exception:
                self.view.show_result(0, "Вы ввели слишком большое число")

    def prime_factorization(self, value):
        v = self.int_conversion(value)

        if (v is None) or (v < 0):
            self.view.show_result(1, "Введите неотрицательное целое число")
            return
        
        if v == 1 or v == 0:
            self.view.show_result(0, "Число не является ни простым ни составным")
        else:
            try:
                div_str = self.model.prime_factorization(v)
                r = list(int(x) for x in div_str.split())
                self.view.show_result(0, f"Простые множители: {*r,}" if len(r) > 1 else "Это простое число")
            except Exception:
                self.view.show_result(0, "Вы ввели слишком большое число")

    def get_random_prime(self):
        self.view.set_input_value(self.model.get_random_prime())

    def file_name_valid(self, value):
        """determines whether the file name is valid"""
        try:
            invalid_chars = ['/', '\\', '|', ':', '*', '?', '"', '<', '>']
            for char in invalid_chars:
                if char in value:
                    return None

            if (value == '') or (len(value) > 50):
                return None
            
            return value
        except ValueError:
            return None

    def generate_primes(self, filename):
        """save primes to file"""
        file = self.file_name_valid(filename)

        if (file is None):
            self.view.show_result(1, "Недопустимое название файла")
            return

        primes_str = self.model.generate_primes(100)
        primes = list(int(x) for x in primes_str.split())
        with open(file + '.txt', 'w') as file:
            for prime in primes:
                file.write(f"{prime}\n")