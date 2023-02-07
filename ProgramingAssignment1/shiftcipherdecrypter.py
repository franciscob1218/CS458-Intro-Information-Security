def main():
    
    r = 26 #range of the alphabet
    ciphertext = input("Please Enter the ciphertext you want to Decrypt: ")
    
    for i in range(r): # this is the range for the alphabet leading the algorithm to shift the total shiftable range
        print("Possible Decryption: " + str(i+1) + ", In Plaintext: " + str(getPlaintext(i, ciphertext)))
        
def getPlaintext(key, ciphertext):
    
    r = 26 #range of the alphabet
    
    plain = []
    
    for x in ciphertext:
        if x.isupper():
            orderedOffset = 65
        else:
            orderedOffset = 97
            
        calc = (ord(x)-orderedOffset-key) % r
        plain.append(chr(calc+orderedOffset))
        
    return ''.join(plain)

if __name__ == '__main__':
    main()
# ciphertextto decode = CSYEVIXIVQMREXIH copy paste into the terminal for quick access
