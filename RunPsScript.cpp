#include <windows.h>
#include <string>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int argc;
    LPWSTR* argvW = CommandLineToArgvW(GetCommandLineW(), &argc);
    
    int sizeNeeded = WideCharToMultiByte(CP_ACP, 0, argvW[1], -1, NULL, 0, NULL, NULL);
    char* argv = new char[sizeNeeded];
    WideCharToMultiByte(CP_ACP, 0, argvW[1], -1, argv, sizeNeeded, NULL, NULL);
    
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    DWORD flags = CREATE_NO_WINDOW;
    
    if (argc < 2){
        return 1;
    }
    const char* command = ("powershell.exe "+std::string(argv)).c_str();

    // Create process hidden
    if (CreateProcessA(
        NULL,               // No module name
        (LPSTR)command,     // Command line
        NULL, NULL,         // Process and thread security attributes
        FALSE,              // No inheritance
        flags,              // Create flags
        NULL,               // Use parent's environment
        NULL,               // Use parent's starting directory
        &si, &pi)
    ) {
        // Wait for it to complete
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        system("msg * Error from RunPsScript");
        return 2;
    }
    delete[] command;

    return 0;
}