import urllib2
import sys

TARGET = 'http://crypto-class.appspot.com/po?er='
#--------------------------------------------------------------
# padding oracle
#--------------------------------------------------------------
INIT = "f20bdba6ff29eed7b046d1df9fb7000058b1ffb4210a580f748b4ac714c001bd4a61044426fb515dad3f21f18aa577c0bdf302936266926ff37dbf7035d5eeb4"
BLOCK0 = "f20bdba6ff29eed7b046d1df9fb70000"
BLOCK1 = "58b1ffb4210a580f748b4ac714c001bd"
BLOCK2 = "4a61044426fb515dad3f21f18aa577c0"
BLOCK3 = "bdf302936266926ff37dbf7035d5eeb4"
NBLOCK = 4

class PaddingOracle(object):
    def query(self, q, cnt):
        target = TARGET + urllib2.quote(q)    # Create query URL
        req = urllib2.Request(target)         # Send HTTP request to server
        try:
            f = urllib2.urlopen(req)          # Wait for response
        except urllib2.HTTPError, e:          
            print("%d: We got: %d" % (cnt, e.code))       # Print response code
            if e.code == 404:
                return True # good padding
            return False # bad padding

def modify(string, index, value):
    return string[:index] + value + string[index+2:]

def toString(value):
    res = hex(value)[2:]
    if (len(res) == 1) :
        return "0" + res
    return res

def toInt(value):
    return int(value, 16)

def xor(str1, st2):
    return toString(toInt(str1) ^ toInt(st2))

def prettyPrint(s):
    for i in range(len(s) / 2 / 16):
        print(s[i*32:(i+1)*32])

def printout(s):
    for i in range(len(s) - 1, -1, -1):
        print("%c" % toInt(s[i])), 

ansBlock1 = ['20', '73', '64', '72', '6f', '57', '20', '63', '69', '67', '61', '4d', '20', '65', '68', '54']
ansBlock2 = ['73', '4f', '20', '68', '73', '69', '6d', '61', '65', '75', '71', '53', '20', '65', '72', '61']
ansBlock3 = ['09', '09', '09', '09', '09', '09', '09', '09', '09', '65', '67', '61', '72', '66', '69', '73']

def attack(s):
    tmp = BLOCK0
    for i in range(15):
        rua = toString(ord(s[i]))
        t = xor(tmp[2 * i : 2 * i + 2], xor(ansBlock1[i], rua))
        tmp = modify(tmp, 2 * i, t)
    return tmp

if __name__ == "__main__":
    po = PaddingOracle()
    prettyPrint(INIT)
    printout(ansBlock1)
    printout(ansBlock2)
    printout(ansBlock3)
    print ""
    ans = []
    """ solve for BLOCK1
    for byte in range(16):
        s = BLOCK0
        for i in range(byte):
            rua = xor(s[32 - 2 * i - 2 : 32 - 2 * i], xor(ans[i], toString(byte + 1)))
            s = modify(s, 32 - 2 * i - 2, rua)
        print(s)
        for i in range(32, 130):
            rua = xor(BLOCK0[32 - byte * 2 - 2 : 32 - byte * 2], xor(toString(i), toString(byte + 1)))
            # print(modify(s, 32 - byte * 2 , rua))
            if (po.query(modify(s, 32 - byte * 2 - 2, rua) + BLOCK1, i)):
                print(i)
                ans = ans + [toString(i)]
                break
    """
    """ solve for BLOCK2
    for byte in range(16):
        s = BLOCK1
        for i in range(byte):
            rua = xor(s[32 - 2 * i - 2 : 32 - 2 * i], xor(ans[i], toString(byte + 1)))
            s = modify(s, 32 - 2 * i - 2, rua)
        print(s)
        print(ans)
        for i in range(32, 130):
            rua = xor(BLOCK1[32 - byte * 2 - 2 : 32 - byte * 2], xor(toString(i), toString(byte + 1)))
            # print(modify(s, 32 - byte * 2 , rua))
            print(ans)
            if (po.query(modify(s, 32 - byte * 2 - 2, rua) + BLOCK2, i)):
                print(i)
                ans = ans + [toString(i)]
                break
    """
    """ solve for BLOCK3
    ans = []
    for byte in range(16):
        s = BLOCK2
        for i in range(byte):
            rua = xor(s[32 - 2 * i - 2 : 32 - 2 * i], xor(ans[i], toString(byte + 1)))
            s = modify(s, 32 - 2 * i - 2, rua)
        print(s)
        print(ans)
        for i in range(2, 256):
            rua = xor(BLOCK2[32 - byte * 2 - 2 : 32 - byte * 2], xor(toString(i), toString(byte + 1)))
            print(modify(s, 32 - byte * 2 , rua))
            print(ans)
            if (po.query(modify(s, 32 - byte * 2 - 2, rua) + BLOCK3, i)):
                print(i)
                ans = ans + [toString(i)]
                break
    """

    # experiment:
    for byte in range(16):
        s = BLOCK1
        for i in range(byte):
            rua = xor(s[32 - 2 * i - 2 : 32 - 2 * i], xor(ans[i], toString(byte + 1)))
            s = modify(s, 32 - 2 * i - 2, rua)
        print(s)
        print(ans)
        for i in range(toInt(ansBlock2[byte]), toInt(ansBlock2[byte]) + 1):
            rua = xor(BLOCK1[32 - byte * 2 - 2 : 32 - byte * 2], xor(toString(i), toString(byte + 1)))
            # print(modify(s, 32 - byte * 2 , rua))
            print(ans)
            if (po.query(BLOCK0 + modify(s, 32 - byte * 2 - 2, rua) + BLOCK2, i)):
                print(i)
                ans = ans + [toString(i)]
                break
    print (ans)
