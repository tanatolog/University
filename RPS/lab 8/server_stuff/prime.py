import random
import sys
sys.setrecursionlimit(2000)

MAX_PRIME = 999999937

def is_prime(n): # optimized trial division with 6k optimization
    n = int(n)
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

def prime_factorization_int(num):
    factors = []
    k = 2

    while num > 1:
        while num % k == 0:
            factors.append(k)
            num //= k
        k += 1

    return factors

def prime_factorization(n):
    n = int(n)
    return ' '.join(str(x) for x in prime_factorization_int(n))

def next_prime(i):  # find the next prime number
    candidate = i + 1
    while not is_prime(candidate):
        candidate += 1
    return candidate

get_random_prime = lambda: str(next_prime(random.randint(2, MAX_PRIME - 1)))

def generate_primes(size): # generating an array of prime numbers
    n = int(size)
    primes = []
    while len(primes) < size:
        prime = get_random_prime()
        primes.append(prime)
    return ' '.join(str(x) for x in primes)