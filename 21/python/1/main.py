def move(x, d):
	return (x - 1 + d) % 10 + 1

a = int(input().split()[-1])
b = int(input().split()[-1])
sa, sb = 0, 0
d = 1
cnt = 0
while True:
	s = d * 3 + 3
	a = move(a, s)
	d += 3
	sa += a
	cnt += 3
	if sa >= 1000:
		break
	s = d * 3 + 3
	b = move(b, s)
	d += 3
	sb += b
	cnt += 3
	if sb >= 1000:
		break
print(cnt * min(sa, sb))