from math import factorial as fact

p_proc = 0.96
p_mem = 0.95
p_io = 0.905

n_cpu = 2   #number cpus in one line
n_mem = 7   #number mems in one line
n_io = 5    #number ios in one line

t4_reserve_mem = 1
t4_reserve_io = 1

t5_reserve_mem = 2
t5_reserve_io = 2

def f(p, n, q):
    return 1 - (1  - p ** n) ** q

def C(m, n):
    return fact(n) / (fact(m) * fact(n - m))

def P(m, n, p):
    return C(m, n) * (p ** m) * ((1 - p) ** (n - m))

def R(m, n, p):
    return 1 - sum(P(i, n, p) for i in range(0, m))

task0 = f(0.9, 1, 2)

task1 = p_proc ** n_cpu * p_mem ** n_mem * p_io ** n_io

task2 = f(p_proc, n_cpu, 2) * f(p_mem, n_mem, 2) * f(p_io, n_io, 2)

task3 = f(p_proc, n_cpu, 3) * f(p_mem, n_mem, 3) * f(p_io, n_io, 3)

task4 = p_proc ** 2 * R(n_mem, n_mem + t4_reserve_mem, p_mem) * R(n_io, n_io + t4_reserve_io, p_io)

task5 = p_proc ** 2 * R(n_mem, n_mem + t5_reserve_mem, p_mem) * R(n_io, n_io + t5_reserve_io, p_io)

task6 = p_proc ** 2 * R(n_mem, n_mem + n_mem, p_mem) * R(n_io, n_io + n_io, p_io)

print(round(0.99989/10, 6))
