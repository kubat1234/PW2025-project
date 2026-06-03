import random

random.seed(42)

FILENAME = "test.in"
TEST_CASES = 10

MIN_N = 4000
MAX_N = 5000

MIN_M = 4000
MAX_M = 5000

MIN_K = 500000
MAX_K = 1000000

MAX_DIST1 = 5000
MAX_DIST2 = 1_000_000_000

def generate_test_file():
    print(f"Generowanie pliku {FILENAME}...")
    
    with open(FILENAME, 'w') as f:
        f.write(f"{TEST_CASES}\n")
        
        for t in range(1, TEST_CASES + 1):
            n = random.randint(MIN_N, MAX_N)
            max_edges = (n * (n - 1)) // 2
            m = random.randint(MIN_M, min(MAX_M, max_edges))
            k = random.randint(MIN_K, MAX_K)
            
            f.write(f"{n} {m} {k}\n")
            
            edges = set()
            while len(edges) < m:
                u = random.randint(1, n)
                v = random.randint(1, n)
                
                if u == v: continue
                
                if u > v: u, v = v, u
                
                edges.add((u, v))
            
            for u, v in edges:
                f.write(f"{u} {v}\n")
            
            for _ in range(k):
                s = random.randint(1, n)
                t = random.randint(1, n)
                if random.choice([True, False]):
                    d = random.randint(1, MAX_DIST1)
                else:
                    d = random.randint(1, MAX_DIST2)
                f.write(f"{s} {t} {d}\n")

if __name__ == "__main__":
    generate_test_file()