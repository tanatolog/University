l0 = 0.1
p = [0.27, 0.23, 0.27, 0.23]
v = [0.43, 0.2, 0.67, 0.55]
k = [2, 3, 1, 3]
ou = 3.74631

lmbda = []
lmbda.append(l0 / p[0])
i = 1
while i < len(p):
	lmbda.append(p[i] * lmbda[0])
	i += 1

for i, li in enumerate(lmbda):
	print("l(", i, ") =" , li)

a = list(map(lambda l: l / l0, lmbda))
for i, ai in enumerate(a):
	print("a(", i, ") =", ai)

b = []
for i, data in enumerate(zip(lmbda , v)):
	li, vi = data
	bi = li * vi
	print("b(", i, ") =", bi)
	b.append(bi)

pi = []
PI = 1
for i, ki in enumerate(k):
	if ki == 1:
		p = 1 - b[i]
		print("P(", i, ") =", 1 - b[i])
	else:
		p = 1 / (b[i]**2 / (2 * (1 - b[i]/2)) + 1 + b[i])
		print("P(", i, ") =", p)
	pi.append(p)
	PI *= p

print("PI = ", PI)


l = []
for i, bi in enumerate(b):
	li = (b[i]**(k[i]+1) / (k[i] * k[i] * (1 - b[i] / k[i])**2)) * pi[i]
	print("l (", i, ") =", li)
	l.append(li)
print("L = ", sum(l))

ro = []

for i, bi in enumerate(b):
	roi = bi / k[i]
	ro.append(roi)

m = []
for i, roi in enumerate(ro):
	mi = l[i] + b[i]
	print("m(", i, ") = ", mi)
	m.append(mi)

print("M = ", sum(m))

w = []
for i, li in enumerate(l):
	wi = li / lmbda[i]
	print("w(", i, ") = ", wi)
	w.append(wi)

print("W =",sum([ai*wi for ai,wi in zip(a,w)]))

u = []
for i, mi in enumerate(m):
	ui = mi/lmbda[i]
	print("u(", i, ") = ", ui)
	u.append(ui)
u=sum([ai*ui for ai,ui in zip(a,u)])	
print("U=", u)
du = 100-((u*100)/ou)
print("du", du)
