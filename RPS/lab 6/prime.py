import random

MAX_PRIME = 999999937

def is_prime(n): # optimized trial division with 6k optimization
    if n <= 1: # numbers less than or equal to 1 are not prime
        return False
    
    if n <= 3: # 2 and 3 are prime
        return True
    
    if (n % 2 == 0) or (n % 3 == 0): # exclude even numbers and numbers divisible by 3
        return False
    
    i = 5 # check the divisors from 5 to sqrt(n) in increments of 6
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i += 6

    return True

prime_factorization = lambda num, k = 2: [num] if is_prime(num) else [k] + prime_factorization(num // k, k) if num % k == 0 else prime_factorization(num, k + 1)

get_next = lambda i: get_next(i + 1) if not is_prime(i + 1) else i + 1 # find the next prime number

get_random_prime = lambda: get_next(random.randint(2, MAX_PRIME))

def generate_primes(size):
    primes = []
    while len(primes) < size:
        prime = get_random_prime()
        primes.append(prime)
    return primes