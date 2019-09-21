from Crypto.Cipher import AES
from os import urandom
from Crypto.Random import random

list1 = [16,32,64]
block = random.choice([16,32,64])
key = urandom(16)
print block


def padding(string, blocksize):
    l = len(string)
    padlen = blocksize - (l % blocksize)
    padbyte = hex(padlen).replace("0x", "")
    if len(padbyte) != 2:
        padbyte = "0" + padbyte
    string = string.encode("hex") + padlen*padbyte
    string = string.decode("hex")
    return string


# Encryption Function
def encryption(key, plaintext):
    obj = AES.new(key, AES.MODE_ECB)
    cipher = obj.encrypt(plaintext).encode("hex")
    return cipher


# Function for detecting block size
def detectblocksize():
    i = 2
    str1 = "a"
    temp = len(encryption(key, padding(str1, block)))
    while i > 0:
        str1 += "a"
        padded = padding(str1, block)
        ciphertext = encryption(key, padded)
        if len(ciphertext) != temp:
            print "The block size is: ",len(ciphertext)/2 - len(str1)
            exit()
        i += 1
        temp = len(ciphertext)


detectblocksize()

