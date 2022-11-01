#include <string>
#include <iostream>
#include <Windows.h>

using namespace std;

int main() {
  int varInt = 123456;
  string varString = "DefaultString";
  char arrChar[128] = "Long char array right there ->";
  int *ptr2int = &varInt;
  int **ptr2int2 = &ptr2int;
  int ***ptr2int3 = &ptr2int2;

  do {
  cout << "Process ID: " << GetCurrentProcessId() << endl << endl;
  cout << "varInt (" << &varInt << ") = " << varInt << endl;
  cout << "varString (" << &varString << ") = " << varString << endl << endl;
  cout << "varArr (" << &arrChar << ") = " << arrChar << endl;
  cout << "varPtr2Int (" << &ptr2int << ") = " << ptr2int << endl;
  cout << "varPtr2Int2 (" << &ptr2int2 << ") = " << ptr2int2 << endl;
  cout << "varPtr2Int3 (" << &ptr2int3 << ") = " << ptr2int3 << endl << endl;
  cout << "Press ENTER to print again";
  getchar();
  cout << endl << "---------------------------------------------------" << endl << endl;
  } while (true);

return 0;
}