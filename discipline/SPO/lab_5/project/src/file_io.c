#include "file_io.h"
#include "complex.h"

#include <windows.h>
#include <stdio.h>

#define BUFFERSIZE 10

void WriteComplex(char *fname, Complex *buffer, int count) {
    HANDLE hFile;
    hFile = CreateFile ((LPCTSTR) fname,        // the name of the file to be created or opened
                        GENERIC_WRITE,          // open for writing
                        0,                      // do not share
                        NULL,                   // default security
                        CREATE_ALWAYS,          // create a new, or open an existing file
                        FILE_ATTRIBUTE_NORMAL,  // normal file
                        NULL);                  // no attributes template

    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Error! Cannot open file %s", fname);
        // return;
    }

    char dataBuffer[] = "Test write to file";


    BOOL errorWrite = FALSE;
    DWORD dwBytesToWrite = (DWORD) strlen(dataBuffer);
    DWORD dwBytesWritten = 0;
    errorWrite = WriteFile (hFile,              // open file handle
                            dataBuffer,         // start of data to write
                            dwBytesToWrite,     // number of bytes to write
                            &dwBytesWritten,    // number of bytes that were written
                            NULL);              // no overlapped structure

    if (errorWrite == FALSE) {
        printf("Unable to write to file\n");
        CloseHandle(hFile);
    } else {
        if (dwBytesToWrite != dwBytesWritten) {
            printf("Not all of the bytes have been written\n");
        } else {
            printf("Writing data is completed successfully\n");
        }
    }

    CloseHandle(hFile);
}

int ReadComplex(char *fname, Complex *buffer, int count) {
    HANDLE hFile;
    DWORD dBytesRead = 0;
    char readBuffer[BUFFERSIZE] = {0};

    hFile = CreateFile ((LPCTSTR) fname,        // the name of the file to be opened
                        GENERIC_READ,           // open for reading
                        0,                      // do not share
                        NULL,                   // default security
                        OPEN_EXISTING,          // open only an existing file
                        FILE_ATTRIBUTE_NORMAL,  // normal file
                        NULL);                  // no attributes template

    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Error! Cannot open file %s", fname);
        // return;
    }

    BOOL errorRead = FALSE;
    LPDWORD lpBytesRead = 0;

    errorRead = ReadFile (hFile,                // open file handle
                          readBuffer,           // buffer to write bytes
                          BUFFERSIZE-1,         // number of bytes to read
                          lpBytesRead,          // the number of bytes read
                          NULL);                // adres to OVERLAPPED structure

    if (errorRead == FALSE) {
        printf("Unable to read data from file %s\n", hFile);
        CloseHandle(hFile);
    }

    if (lpBytesRead > 0 && (int) lpBytesRead <= BUFFERSIZE-1) {
        printf("Data is read successfully");
    } else if (lpBytesRead == 0) {
        printf("No data read from file");
    } else {
        printf("Unexpected value for lpBytesRead");
    }

    CloseHandle(hFile);
    return 0;
}