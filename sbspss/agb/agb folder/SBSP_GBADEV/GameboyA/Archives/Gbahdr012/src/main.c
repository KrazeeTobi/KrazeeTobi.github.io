/* main.c */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>



#include "main.h"


#define VERSION   "gbahdr v0.1.2"


unsigned char *buf;



char logocode[0x100] = {
    0x24,0xff,0xae,0x51,0x69,0x9a,0xa2,0x21,
    0x3d,0x84,0x82,0x0a,0x84,0xe4,0x09,0xad,
    0x11,0x24,0x8b,0x98,0xc0,0x81,0x7f,0x21,
    0xa3,0x52,0xbe,0x19,0x93,0x09,0xce,0x20,
    0x10,0x46,0x4a,0x4a,0xf8,0x27,0x31,0xec,
    0x58,0xc7,0xe8,0x33,0x82,0xe3,0xce,0xbf,
    0x85,0xf4,0xdf,0x94,0xce,0x4b,0x09,0xc1,
    0x94,0x56,0x8a,0xc0,0x13,0x72,0xa7,0xfc,
    0x9f,0x84,0x4d,0x73,0xa3,0xca,0x9a,0x61,
    0x58,0x97,0xa3,0x27,0xfc,0x03,0x98,0x76,
    0x23,0x1d,0xc7,0x61,0x03,0x04,0xae,0x56,
    0xbf,0x38,0x84,0x00,0x40,0xa7,0x0e,0xfd,
    0xff,0x52,0xfe,0x03,0x6f,0x95,0x30,0xf1,
    0x97,0xfb,0xc0,0x85,0x60,0xd6,0x80,0x25,
    0xa9,0x63,0xbe,0x03,0x01,0x4e,0x38,0xe2,
    0xf9,0xa2,0x34,0xff,0xbb,0x3e,0x03,0x44,
    0x78,0x00,0x90,0xcb,0x88,0x11,0x3a,0x94,
    0x65,0xc0,0x7c,0x63,0x87,0xf0,0x3c,0xaf,
    0xd6,0x25,0xe4,0x8b,0x38,0x0a,0xac,0x72,
    0x21,0xd4,0xf8,0x07
};

char unused[0x7] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00
};


int main(int argc, char *argv[]) {
    FILE    *in;
    unsigned long  filelen,soffs,inicode;
    unsigned short makercode,csum;
    short i;
    unsigned char comp=0;

    printf("%s by anarko\n\n",VERSION);


    if (argc==1) {
        printf("Syntax: %s file\n",argv[0]);
        return 1;
    }

    in = fopen(argv[1], "rb");
    if (in == NULL) {
        printf("ERROR: Couldn't find %s.\n",argv[1]);
        return 1;
    }


    // get filelen
    rewind(in);
    fseek(in, 0, SEEK_END);
    filelen = ftell(in);


    /* Allocates memory buffers */
    buf = (char *) calloc(filelen,sizeof(char));
    if(buf==NULL) {
        printf("Couldn't allocate enough memory.\n");
        return 1;
    }


    fseek(in, 0, SEEK_SET);
    if (!fread(buf,1,filelen,in)) {
        fclose(in);
        printf("Failed to read from %s.\n",argv[1]);
        return 1;
    }



    soffs=(buf[3]<<24)|(buf[2]<<16)|(buf[1]<<8)|buf[0];
    inicode=(buf[0xAC]<<24)|(buf[0xAD]<<16)|(buf[0xAE]<<8)|buf[0xAF];
    makercode=(buf[0xB0]<<8)|buf[0xB1];
    csum=(buf[0xBE]<<8)|buf[0xBF];

    printf("Start offset       : 0x%08lX\n",0x08000008+(soffs&0x00FFFFFF)*4 );
    printf("Logo code          : ");
    if (strncmp(buf+4,logocode,0x9C)==0) printf("Ok\n");
    else printf("INVALID!\n");

    printf("Game title         : %.12s\n",buf+0xA0);
    printf("Game code          : 0x%08lX\n",inicode);
    printf("Maker code         : 0x%04X (",makercode);
    switch (makercode) {
        case 0x3031: printf("Nintendo"); break;

        default:     printf("UNKNOWN!!!"); break;
    } printf(")\n");

    printf("Fixed value        : ");
    if (buf[0xB2]==0x96) printf("Ok\n");
    else printf("INVALID: %02X\n",buf[0xB2]);

    printf("Main unit code     : 0x%02X\n",buf[0xB3]);
    printf("Device type        : 0x%02X\n",buf[0xB4]);
    printf("Unused data        : ");
    if(strncmp(buf+0xB5,unused,7)==0)
        printf("Ok\n");
    else
        printf("INVALID!: %02X %02X %02X %02X %02X %02X %02X\n",
               buf[0xB5],buf[0xB6],buf[0xB7],buf[0xB8],buf[0xB9],buf[0xBA],buf[0xBB]);

    printf("Software version   : 0x%02X\n",buf[0xBC]);


    /* This algorithm is experimental */
    printf("Complementary check: 0x%02X ",buf[0xBD]);
    for(i=0x08;i<0xBD;i++)
        comp+=buf[i];
    printf("(Calculated %02X, ",comp);
    if(comp==buf[0xBD])
        printf("Ok)\n");
    else
        printf("INVALID!)\n");





    printf("Checksum           : 0x%04X\n",csum);

    cfree(buf);
    return 0;
}
