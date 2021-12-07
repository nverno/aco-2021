import hashlib

def run(zeros, start = "ckczppom"):
    n = 1
    while True:
        s = start + str(n)
        h = hashlib.md5(s.encode()).hexdigest()
        if h.startswith('0'*zeros):
            print(n)
            return
        n += 1

run(5)
run(6)
