#include <string>
#include <iostream>
#include <Windows.h>

using namespace std;

int main() {
  int intWrite;
  int PID;
  string readType;
  int writeIntFunction(HANDLE hProcess);
  int writePointerFunction(HANDLE hProcess);

  cout << "Enter PID: ";
  cin >> PID;

  HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 32188);
  if (hProcess == NULL) { // Failed to get a handle
    cout << "OpenProcess failed. GetLastError = " << dec << GetLastError() << endl;
    system("pause");
    return EXIT_FAILURE;
  }

  cout << "Which type of memory would you like to re-write: ";
  cin >> readType;

  if(readType == "int") {
    intWrite = writeIntFunction(hProcess);
  } 
  else if(readType == "pointer") {
    intWrite = writePointerFunction(hProcess);
  }
  else {
    cout << "Invalid type";
    return 0;
  }

  if(intWrite == 0){
    cout << "could not find value";
    return 0;
  } else {
    cout << "Overwritten Successfully";
    return 0;
  }

}

int writeIntFunction(HANDLE hProcess) {
  // Prompting user for memory address to write
	uintptr_t memoryAddress = 0x0;
	cout << "Memory address of the integer to write (in hexadecimal): 0x";
	cin >> hex >> memoryAddress;
	cout << "Reading 0x" << hex << uppercase << memoryAddress << " ..." << endl;

  // Prompting user for int to overwrite on adress
  int newInt;
  cout << "What integer to overwrite: ";
  cin >> dec >> newInt;


  BOOL writeReturn = WriteProcessMemory(hProcess, (LPVOID)memoryAddress, &newInt, sizeof(int), NULL);
  	if (writeReturn == FALSE) {
		cout << "WriteProcessMemory failed. GetLastError = " << dec << GetLastError() << endl;
		system("pause");
    CloseHandle(hProcess);
    return 0;
	}

  CloseHandle(hProcess);
  return newInt;
}

int writePointerFunction(HANDLE hProcess) {
  int* ptr2int;

  // Prompting user for memory address to write
	uintptr_t memoryAddress = 0x0;
	cout << "Memory address of the pointer to read (in hexadecimal): 0x";
	cin >> hex >> memoryAddress;
	cout << "Writinging 0x" << hex << uppercase << memoryAddress << " ..." << endl;

  // Prompting user for int to overwrite on adress
  int newInt;
  cout << "What integer to overwrite: ";
  cin >> dec >> newInt;


  BOOL writePointer = ReadProcessMemory(hProcess, (LPCVOID)memoryAddress, &ptr2int, sizeof(int*), NULL);
  	if (writePointer == FALSE) {
		cout << "ReadProcessMemory for pointer failed. GetLastError = " << dec << GetLastError() << endl;
		system("pause");
    CloseHandle(hProcess);
    return 0;
	} 

    BOOL writeReturn = WriteProcessMemory(hProcess, (LPVOID)ptr2int, &newInt, sizeof(int*), NULL);
  	if (writeReturn == FALSE) {
		cout << "ReadProcessMemory failed. GetLastError = " << dec << GetLastError() << endl;
		system("pause");
    CloseHandle(hProcess);
    return 0;
	}

  CloseHandle(hProcess);
  return newInt;
}