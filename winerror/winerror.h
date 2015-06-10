#pragma once

#include <cstdint>
#include <string>
#include <iostream>

#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
#endif

#include <WinSock2.h>
#include <Windows.h>

#include <comdef.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Kernel32.lib")

namespace winerror
{
    using error_t = uint32_t;

    inline error_t getLastError()
    {
        return GetLastError();
    }

    inline error_t wsaGetLastError()
    {
        return WSAGetLastError();
    }

    inline std::string errorString(error_t errCode)
    {
        _com_error err(errCode);
        return err.ErrorMessage();
    }

    inline std::string getLastErrorString()
    {
        return errorString(getLastError());
    }
}

#define WIN32_ASSERT() \
{ \
    winerror::error_t errCode = winerror::getLastError(); \
    if (errCode != 0) \
    { \
        std::cerr << "Win32 Error : " << errCode << " " \
            << winerror::errorString(errCode) << " " \
            << __FILE__ << " " << __LINE__ << "\n"; \
    } \
}

#define WSA_ASSERT() \
{ \
    winerror::error_t errCode = winerror::wsaGetLastError(); \
    if (errCode != 0) \
        { \
        std::cerr << "WSA Error : " << errCode << " " \
            << winerror::errorString(errCode) << " " \
            << __FILE__ << " " << __LINE__ << "\n"; \
        } \
}