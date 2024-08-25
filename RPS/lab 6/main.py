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
        print("Выберте действие:")
        print("1. Генерация случайного просто числа")
        print("2. Генерация массива из простых чисел")
        print("3. Проверка числа на простоту")
        print("4. Разложение на простые множители")
        print("5. Выход")

        x = inputInt()
    
        if (x == None) or (5 < x < 1):
            continue
        
        if x == 1:
            print(get_random_prime())

        elif x == 2:
            while True:
                print("Введите размер массива")
                t = inputInt()

                if t == None:
                    continue

                if (t <= 0) or (t > 50):
                    print("Недопустимый размер массива")
                else:
                    print(generate_primes(t))

                break

        elif x == 3:
            while True:
                print("Введите неотрицательное целое число")
                t = inputInt()

                if t == None:
                    continue
                
                if t == 1 or t == 0:
                    print("Число не является ни простым ни составным")
                else:
                    print("Число простое" if is_prime(t) else "Число составное")

                break

        elif x == 4:
            while True:
                print("Введите неотрицательное целое число")
                t = inputInt()

                if t == None:
                    continue

                if t == 1 or t == 0:
                    print("Число не является ни простым ни составным")
                else:
                    r = prime_factorization(t)
                    print(f"Простые множители: {*r,}")

                break

        elif x == 5:
            break