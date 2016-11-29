#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
unsigned char encode(const char *s) {
    int a = 0;
    for ( int i = 0; i < 8; i++) {
        if (s[i] == '1') {
            a = a | (0x1 << (7 - i));
        }
    }
    return (unsigned char)a;
}
void decode(unsigned char a, char *buf) {
    for ( int i = 0; i < 8; i++) {
        buf[i] = (((a >> (7 - i)) & 0x1) != 0) ? '1' : '0';
    }
}
void writeHuffman(const string& s) {
    unsigned char z = 8 - s.length() % 8;
    if (z == 8) {
        z = 0;
    }
    unsigned char buffer[1024];
    buffer[0] = z;
    int pos = 1, nBytes = (int)(ceil(s.length() / ((double)8)));
    const char* ps = s.c_str();
    FILE *fp = fopen("TextToCode.dat", "wb");
    char extended[8];
    for ( int i = 0; i < nBytes; i++) {
        const char *p;
        if (s.length() >= (i + 1) * 8) {
            p = ps + i * 8;
        }
        else {
            char *pp = extended;
            for ( int j = i * 8; j < s.length(); j++) {
                *pp = s[j];
                pp++;
            }
            for (int j = 0; j < z; j++) {
                *pp = '0';
                pp++;
            }
            p = extended;
        }
        buffer[pos] = encode(p);
        pos++;
        if (pos == 1024) {
            fwrite(buffer, sizeof(unsigned char), 1024, fp);
            pos = 0;
        }
    }
    if (pos > 0) {
        fwrite(buffer, sizeof(unsigned char), pos, fp);
    }
    fclose(fp);
}
string& readHuffman() {
    FILE *fp = fopen("TextToCode.dat", "rb");
    fseek(fp, 0L, SEEK_END);
    size_t fileSize = ftell(fp);
    rewind(fp);
    unsigned char buffer[1024];
    fread(buffer, sizeof(unsigned char), 1, fp);
    unsigned char z = buffer[0];
 
    size_t stringSize = (fileSize - 1) * 8;
    char *ptr = new char[stringSize + 1];
    char *optr = ptr;
    size_t len;
    while ((len = fread(buffer, sizeof(unsigned char), 1024, fp)) != 0) {
        for ( int i = 0; i < len; i++) {
            decode(buffer[i], ptr);
            ptr = ptr + 8;
        }
    }
    fclose(fp);
    ptr = ptr - z;
    *ptr = '\0';
    string* str = new string(optr);
    delete []optr;
    return *str;
}
