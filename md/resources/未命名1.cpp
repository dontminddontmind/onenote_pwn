#include<iostream>
#include<cstring>
using namespace std;
char s58[] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

char * base58encode(char *s,int len){
        int n = 138 * len / 100 + 1;
        printf("n:%d\n", n);
        char *out = (char *)malloc(n);
        memset(out, 0, n);

        int v = n - 1;
        for (int i = 0; i < len;i++){
                int t = s[i];
                int j = n - 1;
                for (; j >= 0;j--){
                        if((j<=v)&&(t==0)){
                                break;
                        }
                        t += out[j]<<8;
                        out[j] = t % 58;
                        t /= 58;
                }
                v = j;
        }

        int head = 0;
        for (int i = 0; i < n;i++){
                if(out[i]==0){
                        head++;
                        continue;
                }
                out[i - head] = out[i];
        }
        for (int i = n-head; i < n;i++){
                out[i] = 0;
        }

                for (int i = 0; i < n-head; i++)
                {
                        out[i] = s58[out[i]];
                }

        return out;
}

char * base58decode(char *s,int len){

        char key[len] = {0};

        cout << "key:";
        for (int i = 0; i < len;i++){
                for (int j = 0; s58[j]!='\0';j++){
                        if(s58[j]==s[i]){
                                key[i] = j;
                        }
                }
                int x = key[i];
                cout << x<< " ";
        }
        cout << endl;

        char *out =(char *) malloc(len);
        memset(out, 0, len);

        int v = len - 1;
        for (int i = 0; i < len;i++){
                int t = key[i];
                int j = len - 1;
                for (; j >= 0;j--){
                        if((j<=v)&&(t==0))
                                break;
                        t += ((unsigned char)(out[j])) * 58;
                        out[j] = t & 0x0ff;
                        t >>= 8;
                }
                v = j;
        }


        int head = 0;
        for (int i = 0; i < len;i++){
                if(out[i]==0){
                        head++;
                        continue;
                }
                out[i - head] = out[i];
        }
        for (int i = len-head; i < len;i++){
                out[i] = 0;
        }

        // cout << "out:";
        // for (int i = 0; i < len - head;i++){
        //         printf("%x ", ((unsigned char)(out[i])));
        // }
        // cout << endl;

        return out;
}

int main(){
        char s[24] = {0};
        strcpy(( char *)s, "D9");
        strcpy(( char *)s + 2, "cS9N");
        strcpy(( char *)s + 6, "9iHjM");
        strcpy(( char *)s + 11, "LTdA8YS");
        strcpy(( char *)s + 18, "MR");
        strcpy(( char *)s + 20, "Mp");

        puts(s);

        //char sABC[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

        // char flag[] = "base58_is_boring";
        // char *out = base58encode(flag,strlen(flag));
        // puts(out);
        // free(out);

        char flag[20] = {0};
        flag[17] = 1;
        flag[19] = 1;
        char *out = base58encode(flag,20);
        puts(out);
        free(out);

        char f[] = "11212";
        out = base58decode(f,strlen(f));
        puts(out);
        free(out);

        out = base58decode(s, strlen(s));
        puts(out);
        free(out);

        return 0;
}