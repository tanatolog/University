from prime import *

def inputInt():
    try: 
        value = int(input())

        if value < 0:
            return None

        return value
    except ValueError:
        return None

if __name__ == '__main__':
    while True:
        print()
        print("Выберите действие:")
        print("1. Генерация случайного простого числа")
        print("2. Генерация массива из простых чисел")
        print("3. Проверка числа на простоту")
        print("4. Разложение на простые множители")
        print("5. Выход")

        command = inputInt()
    
        if (command == None) or (5 < command < 1):
            continue
        
        if command == 1:
            print(get_random_prime())

        elif command == 2:
            while True:
                print("Введите размер массива")
                value = inputInt()

                if value == None:
                    continue

                if (value <= 0) or (value > 50):
                    print("Недопустимый размер массива")
                else:
                    result = generate_primes(value)
                    print(result)

                break

        elif command == 3:
            while True:
                print("Введите неотрицательное целое число")
                value = inputInt()

                if value == None:
                    continue
                
                if value == 1 or value == 0:
                    print("Число не является ни простым ни составным")
                elif value > MAX_PRIME:
                    print("Вы ввели слишком большое число")
                else:
                    print("Число простое" if is_prime(value) else "Число составное")

                break

        elif command == 4:
            while True:
                print("Введите неотрицательное целое число")
                value = inputInt()

                if value == None:
                    continue

                if value == 1 or value == 0:
                    print("Число не является ни простым, ни составным")
                elif value > MAX_PRIME:
                    print("Вы ввели слишком большое число")
                else:
                    result = prime_factorization(value)
                    print(f"Простые множители: {*result,}")

                break

        elif command == 5:
            break