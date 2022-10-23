//
//  main.c
//  x160ptap
//
//  Created by home on 23/10/2022.
//  Copyright © 2022 GITANES. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

FILE* fin;
FILE* fou;
int neg = 0;
int len = 0;
int typ = 8;

void fw(FILE* d, int s)
{
    switch(s){
        case 0:
            if (neg) {
                fputc('1',d);
                fputc('1',d);
                fputc('1',d);
            } else {
                fputc('0',d);
                fputc('0',d);
                fputc('0',d);
            }
            break;
        case 1:
            if (neg) {
                fputc('1',d);
                fputc('1',d);
                fputc('0',d);
            } else {
                fputc('0',d);
                fputc('0',d);
                fputc('1',d);
            }
            break;
        case 2:
            if (neg) {
                fputc('1',d);
                fputc('0',d);
                fputc('1',d);
            } else {
                fputc('0',d);
                fputc('1',d);
                fputc('0',d);
            }
            break;
        case 3:
            if (neg) {
                fputc('1',d);
                fputc('0',d);
                fputc('0',d);
            } else {
                fputc('0',d);
                fputc('1',d);
                fputc('1',d);
            }
            break;
        case 4:
            if (neg) {
                fputc('0',d);
                fputc('1',d);
                fputc('1',d);
            } else {
                fputc('1',d);
                fputc('0',d);
                fputc('0',d);
            }
            break;
        case 5:
            if (neg) {
                fputc('0',d);
                fputc('1',d);
                fputc('0',d);
            } else {
                fputc('1',d);
                fputc('0',d);
                fputc('1',d);
            }
            break;
        case 6:
            if (neg) {
                fputc('0',d);
                fputc('0',d);
                fputc('1',d);
            } else {
                fputc('1',d);
                fputc('1',d);
                fputc('0',d);
            }
            break;
        case 7:
            if (neg) {
                fputc('0',d);
                fputc('0',d);
                fputc('0',d);
            } else {
                fputc('1',d);
                fputc('1',d);
                fputc('1',d);
            }
            break;
        default:
            break;
    }
    len += 3;
}

int main(int argc, const char * argv[]) {
    char c;
    int t[4];
    int i = 0;
    
    if (argc < 3) {
        printf("Missing arguments!\n");
        exit(100);
    }
    
    fin = fopen(argv[1],"r");
    fou = fopen("ptrdr.in","w");
    typ = (int)strtol(argv[2],NULL,10);
    
    if (fin == NULL) {
        printf("Problem opening input file\n");
        exit(110);
    }
    
    if (fou == NULL) {
        printf("Problem opening output file\n");
        exit(150);
    }
    
    printf("Converting paper type %d\n",typ);
    
    if (typ == 7) {
        c = fgetc(fin);
        if (c != '@') {
            printf("Error: type 7 requires a starting bank/address\n");
            exit(200);
        }
        ungetc(c, fin);
        while ((c = fgetc(fin)) != EOF) {
            if (c == '#') {
                fputc(c,fou);
                while((c = fgetc(fin)) != '\n') {
                    fputc(c,fou);
                }
                fputc('\n',fou);
            }
            else if (c == '@') {
                fputc(c,fou);
                while((c = fgetc(fin)) != '\n') {
                    fputc(c,fou);
                }
                fputc('\n',fou);
            }
            else if ((c != ' ') && (c != '\n')) {
                t[i%4] = c-'0';
                i++;
                if (i%4 == 0) {
                    for (int i=2;i<4;i++) {
                        fw(fou,t[i]);
                    }
                }
            }
        }
    } else {
        while ((c = fgetc(fin)) != EOF) {
            if (c != ' ') {
                fw(fou,c-'0');
            }
        }
    }
    fw(fou,0);
    fw(fou,0);
    fw(fou,0);
    fw(fou,0);
    
    
    printf("Total of %04o (%d) words converted \n",len/12,len/12);
    
    fclose(fin);
    fclose(fou);
    
    return 0;
}
