#include <string>
#include <iostream>
#include <Windows.h>

using namespace std;

int main() {
  int intRead;
  int PID;
  string readType;
  int writeIntFunction(HANDLE hProcess);
  int writePointerFunction(HANDLE hProcess);

  cout << "Enter PID: ";
  cin >> PID;

  HANDLE hProcess = OpenProcess(PROCESS_VM_WRITE|PROCESS_VM_READ, FALSE, 27228);
  if (hProcess == NULL) { // Failed to get a handle
    cout << "OpenProcess failed. GetLastError = " << dec << GetLastError() << endl;
    system("pause");
    return EXIT_FAILURE;
  }

  cout << "Which type of memory would you like to read: ";
  cin >> readType;

  if(readType == "int") {
    intRead = readIntFunction(hProcess);
  } 
  else if(readType == "pointer") {
    intRead = readPointerFunction(hProcess);
  }
  else {
    cout << "Invalid type";
    return 0;
  }

  if(intRead == 0){
    cout << "could not find value";
    return 0;
  } else {
    cout << "value of int: " << dec << intRead << endl;
    return 0;
  }

}

int readIntFunction(HANDLE hProcess) {
   int intRead = 0;

  // Prompting user for memory address to read
	uintptr_t memoryAddress = 0x0;
	cout << "Memory address of the integer to read (in hexadecimal): 0x";
	cin >> hex >> memoryAddress;
	cout << "Reading 0x" << hex << uppercase << memoryAddress << " ..." << endl;


  BOOL readReturn = ReadProcessMemory(hProcess, LPCVOID(memoryAddress), &intRead, sizeof(int), NULL);
  	if (readReturn == FALSE) {
		cout << "ReadProcessMemory failed. GetLastError = " << dec << GetLastError() << endl;
		system("pause");
    CloseHandle(hProcess);
    return 0;
	}

  CloseHandle(hProcess);
  return intRead;
}

int readPointerFunction(HANDLE hProcess) {
   int intRead = 0;
  int* ptr2int;

  // Prompting user for memory address to read
	uintptr_t memoryAddress = 0x0;
	cout << "Memory address of the pointer to read (in hexadecimal): 0x";
	cin >> hex >> memoryAddress;
	cout << "Reading 0x" << hex << uppercase << memoryAddress << " ..." << endl;

  cout << memoryAddress << endl;

  BOOL readPointer = ReadProcessMemory(hProcess, LPCVOID(memoryAddress), &ptr2int, sizeof(int*), NULL);
  	if (readPointer == FALSE) {
		cout << "ReadProcessMemory for pointer failed. GetLastError = " << dec << GetLastError() << endl;
		system("pause");
    CloseHandle(hProcess);
    return 0;
	} 

    BOOL readReturn = ReadProcessMemory(hProcess, LPCVOID(ptr2int), &intRead, sizeof(int*), NULL);
  	if (readReturn == FALSE) {
		cout << "ReadProcessMemory failed. GetLastError = " << dec << GetLastError() << endl;
		system("pause");
    CloseHandle(hProcess);
    return 0;
	}

  CloseHandle(hProcess);
  return intRead;
}