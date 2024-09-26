from math import factorial as fact
from functools import reduce


def p_0(R, N):
    num = R ** N
    den = fact(N - 1) * (N - R)
    s = sum((R ** n) / fact(n) for n in range(N))
    return 1 / (num / den + s)


def p_n(R, n, N):
    if n <= N:
        return p_0(R, N) * (R ** n) / fact(n)
    else:
        return p_0(R, N) * (R ** n) / (fact(N) * N ** (n - N))


def p_0_1(N, p):
    num = N ** (N - 1) * p ** N
    den = fact(N - 1) * (1 - p)
    s = sum((N ** i) * (p ** i) / fact(i) for i in range(N))
    return 1 / (num / den + s)


def l(N, p):
    num = N ** (N - 1) * p ** (N + 1) * p_0_1(N, p)
    den = fact(N - 1) * (1 - p) ** 2
    return num / den


t1 = p_n(2.1, 3, 6)
#print(round(t1, 9))

t2 = p_n(3.1, 8, 6)
#print(round(t2, 9))

t3 = l(12, 0.063)
#print(round(t3, 7))

N = 6
B = 120 * 1000
lambd = 12
teta = 4000
nu = B / teta
R = lambd / nu
p = lambd / (N * nu)
R = N * p
U = (l(N, p) + R) / lambd
W = l(N, p) / lambd
print(W)