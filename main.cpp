// boomtestmaker - 21.02.2017

#include <bits/stdc++.h>
#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#ifdef WINDOWS
  #include <direct.h>
  #define GetCurrentDir _getcwd
#else
  #include <unistd.h>
  #define GetCurrentDir getcwd
#endif

//#define DEBUG

using namespace std;

string dirName;
string fileGenerator, fileSolver;

int nTestCase, startTest;
TCHAR rootPath[MAX_PATH];

inline bool is_file_exist(const std::string& name) {
  ifstream f(name.c_str());
  return f.good();
}

void checkfile(string NAME) {
  if (!is_file_exist(NAME + ".exe")) {
    MessageBoxA(NULL, "This excutable file does not exist!\nFuck you!", "Alert", MB_OK | MB_ICONWARNING);
    while (true)
      MessageBoxA(NULL, "Fuck you!", "Alert", MB_OK | MB_ICONSTOP);
  }
}

void enter() {
  cout << "Problem name (ex: A): "; cin >> dirName;

  cout << "File generator (ex: r_A): ";  cin >> fileGenerator;
  checkfile(fileGenerator);
  cout << "File solver (ex: A): "; cin >> fileSolver;
  checkfile(fileSolver);

  cout << "Number of test case: "; cin >> nTestCase;
  cout << "Start from: "; cin >> startTest;
  if (nTestCase <= 0 || startTest < 0) {
    MessageBoxA(NULL, "Stop here, fucking guys!", "Alert", MB_OK | MB_ICONWARNING);
    while (true)
      MessageBoxA(NULL, "Fuck you!", "Alert", MB_OK | MB_ICONSTOP);
  }
}

void interfaceInit() {
  string str("Boom Test Maker - coded by hdi");
  SetConsoleTitle(str.c_str());
}

void testInit() {
  dirName = "TRANS";
  nTestCase = 10;
  fileGenerator = "r_trans";
  fileSolver = "trans";
}

void excute() {
  STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

  GetCurrentDirectory(MAX_PATH, rootPath);
  CreateDirectory((dirName).c_str(), NULL);
  SetCurrentDirectory((dirName).c_str());

  for (int iTest = startTest; iTest < nTestCase + startTest; iTest++) {
    cout << "Test " << iTest << " is generating...\n";
    stringstream stream; stream << iTest;
    string order = stream.str();

    SetCurrentDirectory((dirName).c_str());

    string testOrder = "Test" + order;
    CreateDirectory((testOrder).c_str(), NULL);

    TCHAR newDirectory[MAX_PATH];
    SetCurrentDirectory((testOrder).c_str());
    GetCurrentDirectory(MAX_PATH, newDirectory);

    srand(time(NULL));
    SetCurrentDirectory(rootPath);

    system((fileGenerator + ".exe").c_str());
    system((fileSolver + ".exe").c_str());

    TCHAR inpPath[MAX_PATH], outPath[MAX_PATH];
    GetFullPathName((dirName + ".INP").c_str(), MAX_PATH, inpPath, NULL);
    GetFullPathName((dirName + ".OUT").c_str(), MAX_PATH, outPath, NULL);

    string inpStr = inpPath;
    string outStr = outPath;
    string newDirStr = newDirectory;

    system(("copy " + inpStr + " " + newDirStr).c_str());
    system(("copy " + outStr + " " + newDirStr).c_str());

    DeleteFile(inpPath);
    DeleteFile(outPath);
  }

  MessageBoxA(NULL, "Done!", "Message", MB_OK | MB_ICONINFORMATION);
}

int main(int argc, char *argv[]) {
  system("Color 1A");
  interfaceInit();

#ifndef DEBUG
  enter();
#else // DEBUG
  testInit();
#endif // DEBUG
  excute();

  return 0;
}
