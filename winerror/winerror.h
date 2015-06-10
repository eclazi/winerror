#pragma once

#include <cstdint>
#include <string>
#include <iostream>
#include <exception>

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

    class Win32Error : public std::runtime_error
    {
    public:
        Win32Error(error_t errCode)
            : std::runtime_error(
            "Win32 Error : " + std::to_string(errCode) + " " + errorString(errCode)
            )
        {
        }

        Win32Error(error_t errCode, const char* file, size_t line)
            : std::runtime_error(
            "Win32 Error : " + std::to_string(errCode) + " " + errorString(errCode) + " " + file + " " + std::to_string(line)
            )
        {
        }
    };
}

#define WIN32_ASSERT() \
{ \
    winerror::error_t errCode = winerror::getLastError(); \
    if (errCode != 0) \
            { \
        throw winerror::Win32Error(errCode, __FILE__, __LINE__); \
        } \
}

#define WSA_ASSERT() \
{ \
    winerror::error_t errCode = winerror::wsaGetLastError(); \
    if (errCode != 0) \
            { \
            throw winerror::Win32Error(errCode, __FILE__, __LINE__); \
        } \
}