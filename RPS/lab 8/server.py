from xmlrpc.server import SimpleXMLRPCServer
import server_stuff.prime as prime

def main():
    server = SimpleXMLRPCServer(("localhost", 8888))
    print("Listening on port 8888...")

    server.register_function(prime.is_prime, "is_prime")
    server.register_function(prime.prime_factorization, "prime_factorization")
    server.register_function(prime.get_random_prime, "get_random_prime")
    server.register_function(prime.generate_primes, "generate_primes")

    server.serve_forever()

if __name__ == "__main__":
    main()