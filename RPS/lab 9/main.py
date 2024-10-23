from time import time
from fast_factorize import primeFactorize
from prime import *

def speed_test(size):
    print(f'Starting a {size} test:')
    data = generate_primes(size)

    start = time()
    for v in data:
        prime_factorize(v)
    duration = time() - start
    print(f"[Python]: {time() - start}")

    start = time()
    for v in data:
        primeFactorize(v)
    duration = time() - start
    print(f"[C++]: {time() - start}") 


def main():
    speed_test(10) # specify the test volume
        

if __name__ == "__main__":
    main()