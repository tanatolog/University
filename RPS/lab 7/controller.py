class Controller:
    def __init__(self, model, views): # constructor
        self.prime = model
        self.views = views      

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
            self.views.show_result(1, "Введите неотрицательное целое число")
            return
        
        if v == 1 or v == 0:
            self.views.show_result(0, "Число не является ни простым ни составным")
        else:
            self.views.show_result(0, "Число простое" if self.prime.is_prime(v) else "Число составное")

    def prime_factorization(self, value):
        v = self.int_conversion(value)

        if (v is None) or (v < 0):
            self.views.show_result(1, "Введите неотрицательное целое число")
            return
        
        if v == 1 or v == 0:
            self.views.show_result(0, "Число не является ни простым ни составным")
        else:
            r = self.prime.prime_factorization(v)
            self.views.show_result(0, f"Простые множители: {*r,}" if len(r) > 1 else "Это простое число")

    def get_random_prime(self):
        self.views.set_input_value(self.prime.get_random_prime())

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
            self.views.show_result(1, "Недопустимое название файла")
            return

        primes = self.prime.generate_primes(100)
        with open(file + '.txt', 'w') as file:
            for prime in primes:
                file.write(f"{prime}\n")