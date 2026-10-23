#include "../include/DockerLabClient.h"

#include <windows.h>
#include <winhttp.h>
#include <string>

#pragma comment(lib, "winhttp.lib")

// ====================================
// Send HTTP GET Request
// ====================================

bool DockerLabClient::SendGetRequest(
    const std::wstring& endpoint,
    std::string& response)
{
    response.clear();

    bool success = false;

    HINTERNET session = WinHttpOpen(
        L"BugBountyTrainer/1.0",
        WINHTTP_ACCESS_TYPE_NO_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,
        0);

    if (session != nullptr)
    {
        // Avoid long waits when Docker is offline.
        WinHttpSetTimeouts(session, 2000, 2000, 2000, 2000);

        HINTERNET connection = WinHttpConnect(
            session,
            L"127.0.0.1",
            PORT,
            0);

        if (connection != nullptr)
        {
            HINTERNET request = WinHttpOpenRequest(
                connection,
                L"GET",
                endpoint.c_str(),
                nullptr,
                WINHTTP_NO_REFERER,
                WINHTTP_DEFAULT_ACCEPT_TYPES,
                0);

            if (request != nullptr)
            {
                if (WinHttpSendRequest(
                    request,
                    WINHTTP_NO_ADDITIONAL_HEADERS,
                    0,
                    WINHTTP_NO_REQUEST_DATA,
                    0,
                    0,
                    0) &&
                    WinHttpReceiveResponse(request, nullptr))
                {
                    DWORD statusCode = 0;
                    DWORD statusSize = sizeof(statusCode);

                    if (WinHttpQueryHeaders(
                        request,
                        WINHTTP_QUERY_STATUS_CODE |
                        WINHTTP_QUERY_FLAG_NUMBER,
                        WINHTTP_HEADER_NAME_BY_INDEX,
                        &statusCode,
                        &statusSize,
                        WINHTTP_NO_HEADER_INDEX) &&
                        statusCode == 200)
                    {
                        char buffer[4096];
                        DWORD bytesRead = 0;
                        bool readSuccess = true;

                        do
                        {
                            bytesRead = 0;

                            if (!WinHttpReadData(
                                request,
                                buffer,
                                sizeof(buffer),
                                &bytesRead))
                            {
                                readSuccess = false;
                                break;
                            }

                            response.append(buffer, bytesRead);

                        } while (bytesRead > 0);

                        success = readSuccess;
                    }
                }

                WinHttpCloseHandle(request);
            }

            WinHttpCloseHandle(connection);
        }

        WinHttpCloseHandle(session);
    }

    return success;
}

// ====================================
// Check Docker Connection
// ====================================

bool DockerLabClient::IsConnected()
{
    std::string response;

    return SendGetRequest(L"/health", response) &&
           response == "ok";
}

// ====================================
// Get Docker Lab Status
// ====================================

bool DockerLabClient::GetStatus(std::string& response)
{
    return SendGetRequest(L"/status", response);
}

// ====================================
// Get Available Challenges
// ====================================

bool DockerLabClient::GetChallenges(std::string& response)
{
    return SendGetRequest(L"/challenges", response);
}