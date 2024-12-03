import os

L = 128
ti = 16e-9
tsc = 64e-9
tc = 14e-9 #max(tt)
n = 7

def P(L, n, tc, ti):
	return L / (tc * (L + n - 1) + ti)

def d(f, r):
	return f * r + (1 - r)

def tstart(ti, tc, n):
	return ti + n * tc

def E(L, tscalar, tstart, tc):
	return L * tscalar / (tstart + (L - 1) * tc)

os.system('cls')

#print(f'd = {d()}')

#print(f'tstart = {tstart(ti, tc, n)}')

print(f'P = {P(L, n, tc, ti)}')

print(f'E = {E(L, tsc, tstart(ti, tc, n), tc)}')

print();print('Таблица 1:')
L_loop = [16, 32, 64, 128, 256]

print();print('Таблица L:')
for i in L_loop:
	print(i)

print();print('Таблица P:')
for i in L_loop:
	print(P(i, n, tc, ti).__round__())

print();print('Таблица E:')
for i in L_loop:
	print(E(i, tsc, tstart(ti, tc, n), tc).__round__(6))

print();print('Таблица 2:')
n_loop = [7, 8, 8, 9, 9, 10, 10, 8, 10]
tc_loop = [14, 13, 7, 12, 4, 11, 14, 14, 13]

print();print('Таблица n:')
for i in n_loop:
	print(i)

print();print('Таблица tc:')
for i in tc_loop:
	print(i)

print();print('Таблица P:')
for i in range(n_loop.__len__()):
	print(P(L, n_loop[i], tc_loop[i] * 1e-9, ti).__round__())

print();print('Таблица E:')
for i in range(n_loop.__len__()):
	print(E(L, tsc, tstart(ti, tc_loop[i] * 1e-9, n_loop[i]), tc_loop[i] * 1e-9).__round__(6))


p = P(128, 5, 14e-9, 16e-9) + P(32, 5, 14e-9, 0) + P(32, 5, 14e-9, 0)
print(P(128, 5, 14e-9, 16e-9))
print(P(32, 5, 14e-9, 10e-9))
print(P(32, 5, 14e-9, 16e-9))
print(f'P = {p / 3}')

e = E(128, 65e-9, tstart(16e-9, 14e-9, 5), 14e-9) +\
     E(32, 65e-9, tstart(0, 14e-9, 5), 14e-9) +\
     E(32, 65e-9, tstart(0, 14e-9, 5), 14e-9)
print(E(128, 65e-9, tstart(16e-9, 14e-9, 5), 14e-9))
print(E(32, 60e-9, tstart(10e-9, 14e-9, 5), 14e-9))
print(E(32, 65e-9, tstart(16e-9, 14e-9, 5), 14e-9))
print(f'E = {e / 3}')