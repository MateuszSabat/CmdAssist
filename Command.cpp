#include "Command.h"

#include <windows.h>

void BatCommand::Execute(const std::string& params)
{
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = show;

    std::string command = "cmd.exe /c \"" + (params.length() > 0 ? cmd + " " + params : cmd) + '\"';

    if (CreateProcessA(
        NULL,               // Application name
        (LPSTR)command.c_str(), // Command line
        NULL,               // Process handle not inheritable
        NULL,               // Thread handle not inheritable
        FALSE,              // Set handle inheritance to FALSEts
        0,                  // No creation flags
        NULL,               // Use parent's environment block
        NULL,               // Use parent's starting directory 
        &si,                // Pointer to STARTUPINFO structure
        &pi)                // Pointer to PROCESS_INFORMATION structure
        )
    {

    }
}

void UrlCommand::Execute(const std::string& params)
{
    ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
}
