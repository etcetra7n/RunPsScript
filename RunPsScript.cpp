#include <windows.h>
#include <string>

/*
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
*/

/*void executeCommand(const char* command) {
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;
    HANDLE hRead, hWrite;
    if (!CreatePipe(&hRead, &hWrite, &sa, 0)) {
        system("msg * Pipe creation failure");
        return;
    }

    SetHandleInformation(hRead, HANDLE_FLAG_INHERIT, 0);
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    si.wShowWindow = SW_HIDE;
    si.hStdOutput = hWrite;
    si.hStdError = hWrite;

    PROCESS_INFORMATION pi;
    if (!CreateProcess(NULL, const_cast<char*>(command), NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        CloseHandle(hRead);
        CloseHandle(hWrite);
        system("msg * Process creation failure");
        return ;
    }
    CloseHandle(hWrite);

    //char buffer[4096];
    //DWORD bytesRead;
    //std::string output;

    //while (ReadFile(hRead, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
    //    buffer[bytesRead] = '\0';
    //    output += buffer;
    //}

    CloseHandle(hRead);

    // Wait for the process to finish and capture the exit code
    WaitForSingleObject(pi.hProcess, INFINITE);

    //DWORD exitCode;
    //if (!GetExitCodeProcess(pi.hProcess, &exitCode)) {
    //    exitCode = GetLastError();
    //}

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    //res.output = output;
    //res.exitcode = exitCode;
    return;
}*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int argc;
    LPWSTR* argvW = CommandLineToArgvW(GetCommandLineW(), &argc);
    
    int sizeNeeded = WideCharToMultiByte(CP_ACP, 0, argvW[1], -1, NULL, 0, NULL, NULL);
    //system(("msg * size needed: "+std::to_string(sizeNeeded)).c_str());
    char* argv = new char[sizeNeeded];
    WideCharToMultiByte(CP_ACP, 0, argvW[1], -1, argv, sizeNeeded, NULL, NULL);
    
    if (argc < 2){
        return 1;
    }
    const std::string command_str = "powershell " + std::string(argv);
    
    const char* command = command_str.c_str();
    
    //system(("msg * powershell.exe "+std::string(argv)).c_str());
    //executeCommand(command);
    
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    if (CreateProcessA(
        NULL,               // No module name
        (LPSTR)command,     // Command line
        NULL, NULL,         // Process and thread security attributes
        FALSE,              // No inheritance
        CREATE_NO_WINDOW,   // Create flags
        NULL,               // Use parent's environment
        NULL,               // Use parent's starting directory
        &si, &pi)
    ) {
        // Wait for it to complete
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        //std::string dwError = GetLastErrorAsString();
        std::string errComm = "msg * Error creating process";//dwError
        system(errComm.c_str());
        delete[] argv;
        return 2;
    }

    delete[] argv;

    return 0;
}
