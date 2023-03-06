base58 = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz"
def b58encode(tmp:str) ->str:
	temp = list(map(ord,tmp))
	sum=temp[0]
	for i in range(len(temp)-1):
		sum=sum*256+temp[i+1]
	out=[]
	while True:
		out.insert(0,sum%58)
		sum = sum // 58
		if sum==0:
			break
	outstr=""
	for i in out:
		outstr+=base58[i]
	return outstr

def b58decode(tmp:str) ->str:
	idx = list(map(base58.index,tmp))
	sum = idx[0]
	for i in range(len(idx)-1):
		sum=sum*58+idx[i+1]
	import binascii
	return binascii.unhexlify(hex(sum)[2:].encode("utf-8")).decode("utf-8")

print(b58encode("base58_is_boring"))
print(b58decode("D9cS9N9iHjMLTdA8YSMRMp"))


	
	


