// serialRecording.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

HANDLE hSerial;

int main()
{
    hSerial = CreateFile(L"COM3",
        GENERIC_WRITE,
        0,
        0,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        0);

    if (hSerial == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            std::cout << "Serial port does not exist" << std::endl;
        }
        std::cout << "not sure what happened" << std::endl;
    }

    DCB params = { 0 };
    params.DCBlength = sizeof(params);

    if (!GetCommState(hSerial, &params)) {
        std::cout << "Error getting state" << std::endl;
    }

    params.BaudRate = CBR_19200;
    params.ByteSize = 8;
    params.StopBits = ONESTOPBIT;
    params.Parity = NOPARITY;
    if (!SetCommState(hSerial, &params)) {
        std::cout << "error setting serial port state" << std::endl;
    }

    const char* data = "hello World";
    LPCVOID adr = &data;
    DWORD bytesRead = 15;
    LPDWORD bytesWritten = 0;

    while (true) {
        std::cout << "writing: " << data << std::endl;
        if (!WriteFile(hSerial, data, bytesRead, bytesWritten, NULL)) {
            std::cout << "an error has occured" << std::endl;
        }
    }


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
