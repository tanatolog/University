import xmlrpc.client
import socket

class Model:
    def __init__(self):
        self.server = None

    def connect(self):
        connected, self.server = self._get_rpc()
        return connected

    def _get_rpc(self):
        """checking the connection to the server"""
        serv = xmlrpc.client.ServerProxy("http://localhost:8000/")
        try:
            serv._()   # call a fictive method.
        except xmlrpc.client.Fault:
            pass    # connected to the server and the method doesn't exist which is expected.
        except ConnectionRefusedError:
            return False, None
        else:
            return False, None
        return True, serv

    # Methods for working with the server
    is_prime = lambda self, x: self.server.is_prime(str(x))
    prime_factorization = lambda self, n: self.prime_factorization(str(n))
    get_random_prime = lambda self: self.get_random_prime()
    generate_primes = lambda self, n: self.server.generate_primes(str(n))