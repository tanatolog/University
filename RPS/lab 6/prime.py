import random

MAX_PRIME = 999999937

def is_prime(n):                 # optimized trial division with 6k optimization

    def check_divisors(d):       # check the divisors from 5 to sqrt(n) in increments of 6
        if d * d > n:
            return True
        if n % d == 0 or n % (d + 2) == 0:
            return False
        return check_divisors(d + 6)

    if n <= 1:                   # numbers less than or equal to 1 are not prime
        return False
    if n <= 3:                   # 2 and 3 are prime
        return True
    if n % 2 == 0 or n % 3 == 0: # exclude even numbers and numbers divisible by 3
        return False
    return check_divisors(5)

prime_factorization = lambda num, k = 2: [num] if is_prime(num) else [k] + prime_factorization(num // k, k) if num % k == 0 else prime_factorization(num, k + 1)

get_next = lambda i: get_next(i + 1) if not is_prime(i + 1) else i + 1 # find the next prime number

get_random_prime = lambda: get_next(random.randint(2, MAX_PRIME))

def generate_primes(size): # generating an array of prime numbers

    def get_unique_primes(accumulated_primes):
        if len(accumulated_primes) >= size:
            return accumulated_primes
        
        prime = get_random_prime()
        accumulated_primes.append(prime)
        
        return get_unique_primes(accumulated_primes)

    if size <= 0:
        return []  

    return get_unique_primes([])