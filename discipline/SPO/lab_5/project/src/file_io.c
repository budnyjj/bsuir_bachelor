#include "file_io.h"
#include "complex.h"
#include "io.h"

#include <windows.h>

void 
writeComplex(char *fname, struct Complex *complex, int count) {
    HANDLE hFile;
    hFile = CreateFileA ((LPCSTR)fname,         // the name of the file to be created or opened
                        GENERIC_WRITE,          // open for writing
                        0,                      // do not share
                        NULL,                   // default security
                        CREATE_ALWAYS,          // create a new, or open an existing file
                        FILE_ATTRIBUTE_NORMAL,  // normal file
                        NULL);                  // no attributes template

    if (hFile == INVALID_HANDLE_VALUE) {        
        print_rw_message("Error! Cannot open file");
        return;
    }
    
    BOOL isWritten = FALSE;
    DWORD dwBytesToWrite = sizeof(complex[0]) * count;
    DWORD dwBytesWritten = 0;
    isWritten = WriteFile (hFile,              // open file handle
                           complex,            // start of data to write
                           dwBytesToWrite,     // number of bytes to write
                           &dwBytesWritten,    // number of bytes that were written
                           NULL);              // no overlapped structure

    if (isWritten == FALSE) {
        print_rw_message("Unable to write to file!");
    } else {
        if (dwBytesToWrite != dwBytesWritten) {
            print_rw_message("Not all of the bytes have been written!");
        } else {
            print_rw_message("Writing data is completed successfully!");
        }
    }
    CloseHandle(hFile);
}

int 
readComplex(char *fname, struct Complex *complex, int count) {
    HANDLE hFile;

    hFile = CreateFileA (fname,                 // the name of the file to be opened
                        GENERIC_READ,           // open for reading
                        0,                      // do not share
                        NULL,                   // default security
                        OPEN_EXISTING,          // open only an existing file
                        FILE_ATTRIBUTE_NORMAL,  // normal file
                        NULL);                  // no attributes template

    if (hFile == INVALID_HANDLE_VALUE) {
        print_rw_message("Error! Cannot open file!");
        return 0;
    }

    BOOL isRead = FALSE;
    DWORD readBytes = 0;
    LPDWORD lpReadBytes = &readBytes;

    DWORD bytesToRead = sizeof(complex[0]) * count;

    isRead = ReadFile(hFile,                // open file handle
                      complex,              // buffer to write bytes
                      bytesToRead,          // number of bytes to read
                      lpReadBytes,          // number of bytes read
                      NULL);                // addres to OVERLAPPED structure

    if (isRead == FALSE) {
        print_rw_message("Unable to read data from file!");
        CloseHandle(hFile);
        return 0;
    }

    if (readBytes == bytesToRead) {
        print_rw_message("Data read successfully!");
        CloseHandle(hFile);
        return count;

    } else {
        print_rw_message("There is no such number of elements!");
        CloseHandle(hFile);
        return (readBytes / sizeof(complex[0]));
    }

    CloseHandle(hFile);
    return 0;
}