#include<iostream>
#include<string>
using namespace std;

int main(){
        unsigned char b[] = {
            0x42, 0xC7, 0xCA, 0x40, 0xC1, 0x75, 0x16, 0xEF, 0xE7, 0x37,
            0x6E, 0x69, 0x1B, 0xB, 0xF, 0x78, 0xDF, 0xE0, 0xE0, 0x7B,
            0x5F, 0x50, 0x57, 0x5, 0xF4, 0x73, 0xD2, 0x35, 0x47, 0xD5, 0x6C,
            0x5A, 0xFF};

        unsigned char key[16] = {0};
        for (int i = 0; i < 16;i++){
                key[i] = (i >= 2) ? i + 1 : i;
        }
        key[15] = 0;
        int k[4] = {0};
        k[0] = (key[2] << 8) | (key[1] << 16) | (*key << 24) | key[3];
        k[1] = (key[6] << 8) | (key[5] << 16) | (key[4] << 24) | key[7];
        k[2] = (key[10] << 8) | (key[9] << 16) | (key[8] << 24) | key[11];
        k[3] = (key[14] << 8) | (key[13] << 16) | (key[12] << 24) | key[15];

        unsigned char flag[33] = {0};

        for (int i = 0; i < 4;i++){
                unsigned int v12 = (b[8 * i + 0] << 24) + (b[8 * i + 1] << 16) + (b[8 * i + 2] << 8) + (b[8 * i + 3] );
                unsigned int v11 = (b[8 * i + 4] << 24) + (b[8 * i + 5] << 16) + (b[8 * i + 6] << 8) + (b[8 * i + 7] );
                int v10 = 0;
                for (int j = 0; j <= 0x1F;j++){
                        v10-=0x61C88647;
                        // printf("%x ", v10);
                }

                // printf("\n de: ");

                for (int j = 0; j <= 0x1F;j++){
                        // printf("%x ", v10);
                        v11 -= (v12 + v10) ^ ((v12 << 4) + k[2]) ^ ((v12 >> 5) + k[3]);
                        v12 -= (v11 + v10) ^ ((v11 << 4) + k[0]) ^ ((v11 >> 5) + k[1]);
                        v10 += 0x61C88647;
                }
                // printf("\n\n");

                flag[8 * i + 0] = (unsigned char)((v12 >> 24) & 0xff);
                flag[8 * i + 1] = (unsigned char)((v12 >> 16) & 0xff);
                flag[8 * i + 2] = (unsigned char)((v12 >> 8) & 0xff);
                flag[8 * i + 3] = (unsigned char)((v12 >> 0) & 0xff);
                flag[8 * i + 4] = (unsigned char)((v11 >> 24) & 0xff);
                flag[8 * i + 5] = (unsigned char)((v11 >> 16) & 0xff);
                flag[8 * i + 6] = (unsigned char)((v11 >> 8) & 0xff);
                flag[8 * i + 7] = (unsigned char)((v11 >> 0) & 0xff);

        }
        puts((char *)flag);

        return 0;
}