from math import factorial as fact
from functools import reduce


tt = [60e-9, 63e-9, 64e-9, 65e-9]
L = 128 # 128
ti = 16e-9
tsc = 64e-9
tc = 14e-9 #max(tt)
n = 5


def P(L, n, tc, ti):
	return L / (tc * (L + n - 1) + ti)

def d(f, r):
	return f * r + (1 - r)

def tstart(ti, tc, n):
	return ti + n * tc

def E(L, tscalar, tstart, tc):
	return L * tscalar / (tstart + (L - 1) * tc)

print(f'P = {P(L, n, tc, ti)}')

print(f'd = {d()}')

print(f'tstart = {tstart(ti, tc, n)}')

print(f'E = {E(L, tsc, tstart(ti, tc, n), tc)}')

p = P(128, 5, 14e-9, 16e-9) + P(32, 5, 14e-9, 10e-9) + P(32, 5, 14e-9, 16e-9)
print(f'P = {p / 3}')

e = E(128, 65e-9, tstart(16e-9, 14e-9, 5), 14e-9) +\
     E(32, 60e-9, tstart(10e-9, 14e-9, 5), 14e-9) +\
     E(32, 65e-9, tstart(16e-9, 14e-9, 5), 14e-9)
print(f'E = {e / 3}')
