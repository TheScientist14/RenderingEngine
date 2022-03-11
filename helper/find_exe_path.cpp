#include "find_exe_path.h"

#if WIN32
#include <Windows.h>
#endif

namespace
{
#ifdef WIN32
    char exePath[MAX_PATH + 1] = { 0 };
#else
    char exePath[512] = { 0 };
#endif

    std::string exePathView;
}

std::string GetAppPath()
{
    if (exePath[0] == 0)
    {
#ifdef WIN32
        HMODULE exeModule = GetModuleHandleA(nullptr);
        uint32_t length = GetModuleFileNameA(exeModule, exePath, MAX_PATH);

        for (uint32_t i = 0; i < length; ++i)
        {
            if (exePath[i] == '\\')
            {
                exePath[i] = '/';
            }
        }
        exePathView = std::string(exePath, length);
#else
        ssize_t len = ::readlink("/proc/self/exe", exePath, sizeof(exePath) - 1);
    if (len != -1)
    {
    exePath[len] = '\0';
    char* posBack = strrchr(exePath, '/');
    exePathView = std::string(exePath, len);
    chdir(exePathView.begin());
    }
#endif
    }

    return exePathView;
}
