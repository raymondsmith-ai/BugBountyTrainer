#pragma once

#include <string>

// ====================================
// DockerLabClient Class
// ====================================
// Connects BugBountyTrainer to the
// local C++20 Docker training server.
// ====================================

class DockerLabClient
{
private:
    static constexpr int PORT = 8086;

    static bool SendGetRequest(
        const std::wstring& endpoint,
        std::string& response);

public:
    static bool IsConnected();

    static bool GetStatus(std::string& response);

    static bool GetChallenges(std::string& response);
};
