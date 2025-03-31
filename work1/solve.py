Cipher="BNVSNSIHQCEELSSKKYERIFJKXUMBGYKAMQLJTYAVFBKVTDVBPVVRJYYLAOKYMPQSCGDLFSRLLPROYGESEBUUALRWXMMASAZLGLEDFJBZAVVPXWICGJXASCBYEHOSNMULKCEAHTQOKMFLEBKFXLRRFDTZXCIWBJSICBGAWDVYDHAVFJXZIBKCGJIWEAHTTOEWTUHKRQVVRGZBXYIREMMASCSPBNLHJMBLRFFJELHWEYLWISTFVVYFJCMHYUYRUFSFMGESIGRLWALSWMNUHSIMYYITCCQPZSICEHBCCMZFEGVJYOCDEMMPGHVAAUMELCMOEHVLTIPSUYILVGFLMVWDVYDBTHFRAYISYSGKVSUUHYHGGCKTMBLRX"
import matplotlib.pyplot as plt
import math
import numpy as np

def coincidenceIndex(text,length):
    text = text.upper()
    ls=[]
    charnum=[0 for _ in range(length)]
    for i in range(length):
        ls.append([0 for _ in range(26)])
    for i in range(len(text)):
        ls[i%length][ord(text[i])-65]+=1
        charnum[i%length]+=1
    ret=[0. for _ in range(length)]
    for i in range(26):
        for j in range(length):
            if ls[j][i]!=0:
                ret[j]+=(ls[j][i]*(ls[j][i]-1)/charnum[j]/(charnum[j]-1))
    return ret
def gauss_key(text, length):
    # key=#[8.17,1.49,2.78,4.25,12.70,2.23,2.02,6.09,6.97,0.15,0.77,4.03,2.41,6.75,7.51,1.93,0.10,5.99,6.33,9.06,2.76,0.98,2.36,0.15,1.97,0.07]
    key=[0.0788,0.0156,0.0268,0.0389,0.1268,0.0256,0.0187,0.0573,0.0707,
 0.0010,0.0060,0.0394,0.0244,0.0706,0.0776,0.0186,0.0009,0.0594,
 0.0634,0.0978,0.0280,0.0102,0.0214,0.0016,0.0202,0.0006]
    ls=[]
    charnum=[0 for _ in range(length)]
    for i in range(length):
        ls.append([0 for _ in range(26)] )
    for i in range(len(text)):
        ls[i%length][ord(text[i])-65]+=1
        charnum[i%length]+=1
    ret=[[0. for _ in range(26)] for _ in range(length)]
    for t in range(26):
        for i in range(26):
            for j in range(length):
                # if ls[j][i]!=0:
                ret[j][t]+=(key[i]*ls[j][(i+t+26)%26]/charnum[j])
    return ret

def decryptVigenere(Cipher, key):
    decrypted = ""
    key = key.upper()
    key_length = len(key)
    for i in range(len(Cipher)):
        if Cipher[i].isalpha():
            char_index = (ord(Cipher[i]) - 65 - ord(key[i % key_length]) + 65+26) % 26
            decrypted += chr(char_index + 65)
        else:
            decrypted += Cipher[i]
    return decrypted


ret=[]
# for m in range(2,10):
#     ret.append(sum(coincidenceIndex(Cipher, m))/m)
# plt.plot(range(2,10), ret)
# plt.show()
ret=gauss_key(Cipher, 6)
for i in range(6):
    print(ret[i])
    plt.plot(range(26), ret[i],label=f'key{i}:{chr(65+np.argmax(ret[i]))}')
# plt.plot([range(26) for _ in range(6)], ret)
plt.legend()
plt.show()
key = "THEORY" #"THAORU"
decrypted = decryptVigenere(Cipher, key)
print(decrypted)
# print(ret)
    