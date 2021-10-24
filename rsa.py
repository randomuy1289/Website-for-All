def gcd(p,q):
    while q != 0:
        p, q = q, p%q
    return p

def is_coprime(x, y):
    return gcd(x, y) == 1

def encrypt(message, p, q):
    message = message.upper()
    n = p*q
    phi = (p-1)*(q-1)
    for i in range(2, phi):
        if is_coprime(i, phi):
            e = i
            break
    d = pow(e, -1, phi)
    num_message = []
    for i in message:
        if i == ' ':
            num_message.append(26)
            continue
        num_message.append(int(ord(i) - 65))
    crypt = []
    crypt_test = []
    for i in num_message:
        crypt.append(chr(i**d%n))
        crypt_test.append(i**d%n)
    
    return crypt, n, e

def decrypt(crypt, e, n):
    crypted = [ord(c) for c in crypt]
    crypted = [c**e%n for c in crypted]
    plaintext = [chr(c+65) for c in crypted]
    plaintext = ''.join(plaintext)
    plaintext = plaintext.replace('[', ' ')
    print("Plaintext caclulated after decrypting using public key: ", plaintext)
    print("Digital signature verified")

p, q = [int(x) for x in input("Enter 2 prime numbers: ").split()]
plaintext = input("Enter plaintext to be encrypted: ")
crypt, n, e = encrypt(plaintext, p, q)
print("Digital signature produced: ", crypt)
print(f"Public key: ({e}, {n})")
decrypt(crypt, e, n)
