#include "pch.h"  
#include <Windows.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>

const long long MAX_PRIME = 999999937;

using namespace std;
namespace py = pybind11;

bool isPrime(long long n) { //optimized trial division with 6k optimization
    if (n <= 1) {           //numbers less than or equal to 1 are not prime
        return false;
    }
    if (n <= 3) {           //2 and 3 are prime
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0) { //exclude even numbers and numbers divisible by 3
        return false;
    }
    if (n > MAX_PRIME) {
        throw std::runtime_error("obtained a number exceeding the MAX_PRIME");
    }

    long long i = 5;        //check the divisors from 5 to sqrt(n) in increments of 6
    while (i * i <= n) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
        i += 6;
    }
    return true;
    }

vector<long long> primeFactorize(long long num) {
    vector<long long> factors;
    long long k = 2;

    while (num > 1) {
        if (isPrime(num)) {
            factors.push_back(num);
            break;
        }
        else if (num % k == 0) {
            factors.push_back(k);
            num /= k;
        }
        else {
            k += 1;
        }
    }
    return factors;
}

PYBIND11_MODULE(fast_factorize, m) {
    m.def("primeFactorize", &primeFactorize, "Factorize function");

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}
