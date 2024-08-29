import random

MAX_PRIME = 999999937

def is_prime(n): # optimized trial division with 6k optimization
    if n <= 1: # numbers less than or equal to 1 are not prime
        return False
    if n <= 3:                   # 2 and 3 are prime
        return True
    if n % 2 == 0 or n % 3 == 0: # exclude even numbers and numbers divisible by 3
        return False
    if n > MAX_PRIME:
        raise Exception('obtained a number exceeding the MAX_PRIME')
    
    i = 5 # check the divisors from 5 to sqrt(n) in increments of 6
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i += 6

    return True

def prime_factorize(num, k=2):
    factors = []
    
    while num > 1:
        if is_prime(num):
            factors.append(num)
            break
        elif num % k == 0:
            factors.append(k)
            num //= k
        else:
            k += 1
    
    return factors

get_random_number = lambda: random.randint(2, MAX_PRIME - 1)

def generate_primes(size): # generating an array of numbers
    primes = []
    while len(primes) < size:
        prime = get_random_number()
        primes.append(prime)
    return primes