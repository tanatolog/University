import unittest
from prime import *
from unittest.mock import patch

class TestPrimeFunctions(unittest.TestCase):
        
    def test_is_prime(self):
        self.assertTrue(is_prime(1))
        self.assertFalse(is_prime(2))
        self.assertFalse(is_prime(3))
        self.assertFalse(is_prime(-5))
        self.assertFalse(is_prime(999999937))

    def test_prime_factorization(self):
        self.assertEqual(prime_factorization(28), [2, 2, 7])
        self.assertEqual(prime_factorization(1), [1])
        self.assertEqual(prime_factorization(6), [2, 3])
        self.assertEqual(prime_factorization(13), [13]) 
        self.assertEqual(prime_factorization(18), [2, 3, 3])
    
    @patch('random.randint', return_value=7)  # Mocking random.randint to return 7
    def test_get_random_prime(self, mocked_randint):
        self.assertEqual(get_random_prime(), 7)
    
    @patch('prime.get_random_prime', return_value=11)  # Mocking get_random_prime to return 11
    def test_generate_primes(self, mocked_get_random_prime):
        self.assertEqual(generate_primes(5), [11, 11, 11, 11, 11])