---
title: decrypt_safe_linking
updated: 2022-03-24T19:53:00.0000000+08:00
created: 2022-03-24T19:05:16.0000000+08:00
---

decrypt
long decrypt(long cipher)

{

puts("The decryption uses the fact that the first 12bit of the plaintext (the fwd pointer) is known,");

puts("because of the 12bit sliding.");

puts("And the key, the ASLR value, is the same with the leading bits of the plaintext (the fwd pointer)");

long key = 0;

long plain;

for(int i=1; i\<6; i++) {

int bits = 64-12\*i;

if(bits \< 0) bits = 0;

plain = ((cipher ^ key) \>\> bits) \<\< bits;

key = plain \>\> 12;

printf("round %d:\n", i);

printf("key: %#016lx\n", key);

printf("plain: %#016lx\n", plain);

printf("cipher: %#016lx\n\n", cipher);

}

return plain;

}
encrypt
d\[0x30 / 8\] = (long)target ^ ((long)&d\[0x30/8\] \>\> 12);

\#define PROTECT_PTR(pos, ptr) \\

((\_\_typeof (ptr)) ((((size_t) pos) \>\> 12) ^ ((size_t) ptr)))

\#define REVEAL_PTR(ptr) PROTECT_PTR (&ptr, ptr)

