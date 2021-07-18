/************************************************/
/*  Wave file to AGB files converter            */
/*                                              */
/*      Developper support group                */
/*      Nintendo of America Inc.                */
/************************************************/
#include <stdio.h>
#include <string.h>

// Declare functions
void getWaveFormat();
void dispUsage();

// Define wave file format structure
struct waveFormat {
    long  fileSize;     // Total file size
    short channel;      // Mono: 1, Stereo: 2
    long  sampleRate;   // Sampling rate
    short bitPerSmp;    // Bits per sample (8 or 16)
    long  dataSize;     // PCM data size
    long  smpPerCh;     // Samples per cahnnel
    float length;       // Wave data length [sec]
    long  frames;       // Wave data length [frame]
};


main(argc, argv)
int  argc;
char *argv[];
{
    FILE              *ifptr, *ofptr[2], *hfptr;
    struct waveFormat wavFmt;
    long              i, j, k;
    short             pcmData;
    char              charPcm[2][4];
    char              name[40], ofname[40], ofnameH[40];
    char              buffer[100];

    // No wave(input) file and/or source(output) file
    if(argc < 2) {
        printf("wav2agb: No input file name!\n");
        dispUsage();
    }

    // Too many arguments
    if(argc > 2) {
        printf("wav2agb: Too many arguments!\n");
        dispUsage();
    }

    // Too long file name (>30)
    if(strlen(argv[1])>30) {
        printf("Too long input file name \"%s\"!\n", argv[1]);
        printf("Please rename less than 30 letters!\n");
        exit(1);
    }

    // Open input(wave) file
    if((ifptr = fopen(argv[1],"rb")) == NULL) {
        printf("wav2agb: Can't open wave file \"%s\".\n", argv[1]);
        exit(1);
    }

    // Get file size
    fseek(ifptr, 0L, SEEK_END);
    wavFmt.fileSize = ftell(ifptr);
    rewind(ifptr);

/****************************************/
/*      Check wave file format          */
/****************************************/
    getWaveFormat(&wavFmt, ifptr);

/****************************************/
/*          Output files                */
/****************************************/
    // Make output file names (*.wav -> *.h *.bin)
    strcpy(name, argv[1]);
    *strchr(name, '.') = '\0';

    strcpy(ofnameH, name);
    strcat(ofnameH, ".h");
    strcpy(ofname, name);
    strcat(ofname, ".bin");

    // Open header file
    if((hfptr = fopen(ofnameH,"w")) == NULL) {
        printf("wav2agb: Can't open output file \"%s\".\n", ofnameH);
        exit(1);
    }

    // Open L channel output file
    if((ofptr[0] = fopen(ofname,"wb")) == NULL) {
        printf("wav2agb: Can't open output file \"%s\".\n", ofname);
        exit(1);
    }

    // When 2 channels, open R channel output file
    if(wavFmt.channel == 2) {
        if((ofptr[1] = fopen("temp","wb+")) == NULL) {
            printf("wav2agb: Can't open temporary file \"temp\".\n");
            exit(1);
        }
    }

    // Output text label to header file
    fprintf(hfptr, "/********************************************/\n");
    fprintf(hfptr, "/*      PCM data header file for AGB        */\n");
    fprintf(hfptr, "/*          Produced by wav2agb tool        */\n");
    fprintf(hfptr, "/********************************************/\n\n");

    // Output wave file description to heaer file
    fprintf(hfptr, "//  Wave file description\n");
    fprintf(hfptr, "//      File name      : %s\n", argv[1]);
    fprintf(hfptr, "//      PCM channel(s) : %d\n", wavFmt.channel);
    fprintf(hfptr, "//      Sampling rate  : %d[Hz]\n", wavFmt.sampleRate);
    fprintf(hfptr, "//      Sample width   : %d[bits]\n", wavFmt.bitPerSmp);
    fprintf(hfptr, "//      PCM data size  : %d (0x%X)\n", wavFmt.dataSize, wavFmt.dataSize);
    fprintf(hfptr, "//      Wave length    : %.2f[sec]\n\n", wavFmt.length);

    // Output #include command to header file
    fprintf(hfptr, "#include <agb.h>\n\n");

    // Output definision text to header file
    fprintf(hfptr, "#define Channel    %d\n", wavFmt.channel);
    fprintf(hfptr, "#define SampleRate %d\n", wavFmt.sampleRate);
    fprintf(hfptr, "#define Samples    %d\n", wavFmt.smpPerCh);
    fprintf(hfptr, "#define Frames     %d\n\n", wavFmt.frames);

    // Output definision text
    fprintf(hfptr, "const u8 binary_%s_bin_start[%d];\n"
                    , name, wavFmt.smpPerCh * wavFmt.channel);

    // Close header file
    fclose(hfptr);

    // Loop the number of samples
    for(j=0; j<(wavFmt.smpPerCh); j++) {
        // Loop the number of channels
        for(i=0; i<wavFmt.channel; i++) {
            fread(&pcmData, (wavFmt.bitPerSmp/8), 1, ifptr);
            
            // If 16-bit sample, convert into 8-bit sample
            if(wavFmt.bitPerSmp == 16)
                fputc((char)(pcmData>>=8), ofptr[i]);
            // If 8-bit sample, convert 0x80-offset into 0-offset
            else
                fputc((char)(pcmData+0x80), ofptr[i]);
        }
    }

    // Close input file
    fclose(ifptr);

    // Add Right wave data(temp file) to Left wave data(*.bin file)
    if(wavFmt.channel == 2) {
        rewind(ofptr[1]);
        for(j=0; j<wavFmt.smpPerCh; j++)
            fputc(fgetc(ofptr[1]), ofptr[0]);
    }

    // Close output file(s)
    for(i=0; i<wavFmt.channel; i++)
        fclose(ofptr[i]);

    // Finish program
    printf("wav2agb: Succeed in converting!\n");
    exit(0);
}


/****************************************/
/*      Check wave file format          */
/****************************************/
void getWaveFormat(wfmt, wfptr)
struct waveFormat *wfmt;
FILE              *wfptr;
{
    char string[9];
    long filePoint, temp;

    // Check "RIFF" text data
    fread(string, sizeof(char), 4, wfptr);
    string[4] = '\0';
    if(strcmp(string, "RIFF")) {
        printf("wav2agb: Input file isn't RIFF format!\n");
        exit(1);
    }

    // Get wave file size parameter(fileSize - 8(bytes))
    fread(&temp, sizeof(long), 1, wfptr);

    // Check "WAVEfmt " text data
    fread(string, sizeof(char), 8, wfptr);
    string[8] = '\0';
    if(strcmp(string, "WAVEfmt ")) {
        printf("wav2agb: Input file isn't WAVE format!\n");
        exit(1);
    }

    // Get header size parameter (16+(bytes))
    fread(&temp, sizeof(long), 1, wfptr);

    // Save the file pointer at the end of header
    filePoint = ftell(wfptr) + temp;

    // Check data format parameter (1: PCM format)
    fread(&temp, sizeof(short), 1, wfptr);
    if (temp != 1) {
        printf("wav2agb: Input wave file isn't PCM format!\n");
        exit(1);
    }

    // Check channel parameter
    fread(&wfmt->channel, sizeof(short), 1, wfptr);
    if((wfmt->channel != 1) && (wfmt->channel != 2)) {
        printf("wav2agb: The parameter [channel] is not correct!\n");
        exit(1);
    }

    // Get sampling rate
    fread(&wfmt->sampleRate, sizeof(long), 1, wfptr);

    // Get number of bytes per sec (Unused)
    fread(&temp, sizeof(long), 1, wfptr);

    // Get number of bytes per sample (Unused)
    fread(&temp, sizeof(short), 1, wfptr);

    // Check number of bits per sample
    fread(&wfmt->bitPerSmp, sizeof(short), 1, wfptr);
    if((wfmt->bitPerSmp != 8) && (wfmt->bitPerSmp != 16)) {
        printf("wav2agb: The parameter [Bits per sample] is not correct!\n");
        exit(1);
    }

    // Move file pointer to the end of header
    fseek(wfptr, filePoint, SEEK_SET); 

    // Check "data" text data
    while(1) {
        if((fread(string, sizeof(char), 4, wfptr)) < 4) {
	        printf("wav2agb: Can't find the header of PCM data!\n");
	        exit(1);
	    }

        string[4] = '\0';
        if(strcmp(string, "data") == 0)
            break;

        fseek(wfptr, -3, SEEK_CUR);
    }

    // Check wave data size parameter
    fread(&wfmt->dataSize, sizeof(long), 1, wfptr);
    filePoint = ftell(wfptr);
    if (wfmt->dataSize > (wfmt->fileSize - filePoint)) {
        printf("wav2agb: Parameter [Wave data size] is not correct!\n");
        exit(1);
    }

    // Calculate samples per channel
    wfmt->smpPerCh = wfmt->dataSize
                   / wfmt->channel
                   / wfmt->bitPerSmp
                   * 8;

    // Calculate length of PCM data
    wfmt->length = (float)(wfmt->smpPerCh)
                 / (float)(wfmt->sampleRate);

    wfmt->frames = (float)(wfmt->smpPerCh)
                 * (float)59.6
                 / (float)(wfmt->sampleRate);

    return;
}

/****************************************/
/*          Display usage               */
/****************************************/
void dispUsage(){
    printf("Usage: wav2agb <Wave file name> <Bin file name>\n");
    exit(1);
}

/*  End of file */ 