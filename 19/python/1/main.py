from sys import stdin

TRANSFORMS = [
    lambda x, y, z: (x, y, z), lambda x, y, z: (x, z, y), lambda x, y, z: (y, x, z), lambda x, y, z: (y, z, x), lambda x, y, z: (z, x, y), lambda x, y, z: (z, y, x),
    lambda x, y, z: (-x, y, z), lambda x, y, z: (-x, z, y), lambda x, y, z: (-y, x, z), lambda x, y, z: (-y, z, x), lambda x, y, z: (-z, x, y), lambda x, y, z: (-z, y, x),
    lambda x, y, z: (x, -y, z), lambda x, y, z: (x, -z, y), lambda x, y, z: (y, -x, z), lambda x, y, z: (y, -z, x), lambda x, y, z: (z, -x, y), lambda x, y, z: (z, -y, x),
    lambda x, y, z: (x, y, -z), lambda x, y, z: (x, z, -y), lambda x, y, z: (y, x, -z), lambda x, y, z: (y, z, -x), lambda x, y, z: (z, x, -y), lambda x, y, z: (z, y, -x),
    lambda x, y, z: (-x, -y, z), lambda x, y, z: (-x, -z, y), lambda x, y, z: (-y, -x, z), lambda x, y, z: (-y, -z, x), lambda x, y, z: (-z, -x, y), lambda x, y, z: (-z, -y, x),
    lambda x, y, z: (-x, y, -z), lambda x, y, z: (-x, z, -y), lambda x, y, z: (-y, x, -z), lambda x, y, z: (-y, z, -x), lambda x, y, z: (-z, x, -y), lambda x, y, z: (-z, y, -x),
    lambda x, y, z: (x, -y, -z), lambda x, y, z: (x, -z, -y), lambda x, y, z: (y, -x, -z), lambda x, y, z: (y, -z, -x), lambda x, y, z: (z, -x, -y), lambda x, y, z: (z, -y, -x),
    lambda x, y, z: (-x, -y, -z), lambda x, y, z: (-x, -z, -y), lambda x, y, z: (-y, -x, -z), lambda x, y, z: (-y, -z, -x), lambda x, y, z: (-z, -x, -y), lambda x, y, z: (-z, -y, -x),
]

def read_input():
    scanners = []
    scanner = set()
    next(stdin)
    for line in stdin:
        if line == '\n':
            continue
        elif "scanner" in line:
            scanners.append(list(scanner))
            scanner = set()
        else:
            x, y, z = map(int, line.rstrip().split(','))
            scanner.add((x, y, z))
    scanners.append(list(scanner))
    return scanners

def vec_add(v, w):
    return (v[0] + w[0], v[1] + w[1], v[2] + w[2])

def vec_sub(v, w):
    return (v[0] - w[0], v[1] - w[1], v[2] - w[2])

def bruteforce(scanners, i, j):
    for transform in TRANSFORMS:
        scanner2 = [transform(*v) for v in scanners[j]]
        for p1 in scanners[i][:-12]: # limit to dirichlet principle
            for p2 in scanner2[:-12]: # limit to dirichlet principle
                d = vec_sub(p2, p1)
                kkk = [
                    (p3, transform(*v))
                    for p3 in scanners[i]
                    if (v := vec_add(p3, d)) in scanner2
                ]
                if len(kkk) >= 12:
                    return kkk
    return []

scanners = read_input()
TOTAL_SCANNERS = len(scanners)
g = {i: [] for i in range(TOTAL_SCANNERS)}
for i in range(TOTAL_SCANNERS):
    for j in range(i + 1, TOTAL_SCANNERS):
        common = bruteforce(scanners, i, j)
        if common:
            # common is a list of (v - s[i], v - s[j]) where v is beacon world coord
            # and s[i] is i'th scanner world coord
            v, w = common[0]
            # hence, from (v, w) we can find s[j] - s[i] as v - w
            g[j].append((i, vec_sub(w, v)))
            g[i].append((j, vec_sub(v, w)))
print(g)

def relative_to_scanner_0(i):
    visited = [False for _ in range(TOTAL_SCANNERS)]
    def dfs(v):
        if v == 0:
            return (0, 0, 0)
        if visited[v]:
            return None
        visited[v] = True
        for to, d in g[v]:
            d1 = dfs(to)
            if d1:
                return vec_add(d1, d)
    return dfs(i)

beams = {beam for beam in scanners[0]}
for i in range(1, TOTAL_SCANNERS):
    if (-1810, 1650, 1980) in beams:
        print(i)
    d = relative_to_scanner_0(i)
    beams.update(vec_sub(beam, d) for beam in scanners[i])
print(len(beams))
for b in sorted(beams, key=lambda b: b[0]):
    print(b)