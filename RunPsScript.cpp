#include <windows.h>
#include <string>

std::string GetLastErrorAsString() {
    DWORD errorMessageID = ::GetLastError();
    if (errorMessageID == 0)
        return "No error"; // No error has occurred

    LPSTR messageBuffer = nullptr;

    size_t size = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, errorMessageID,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&messageBuffer, 0, NULL);

    std::string message(messageBuffer, size);

    // Free the buffer allocated by FormatMessage
    LocalFree(messageBuffer);

    return message;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int argc;
    LPWSTR* argvW = CommandLineToArgvW(GetCommandLineW(), &argc);
    
    int sizeNeeded = WideCharToMultiByte(CP_ACP, 0, argvW[1], -1, NULL, 0, NULL, NULL);
    //system(("msg * size needed: "+std::to_string(sizeNeeded)).c_str());
    char* argv = new char[sizeNeeded];
    WideCharToMultiByte(CP_ACP, 0, argvW[1], -1, argv, sizeNeeded, NULL, NULL);
    
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    DWORD flags = CREATE_NO_WINDOW;
    
    if (argc < 2){
        return 1;
    }
    const std::string command_str = "powershell " + std::string(argv);
    const char* command = command_str.c_str();
    
    //system(("msg * powershell.exe "+std::string(argv)).c_str());

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
        std::string dwError = GetLastErrorAsString();
        std::string errComm = "msg * "+dwError;
        system(errComm.c_str());
        delete[] argv;
        return 2;
    }
    delete[] argv;

    return 0;
}
