#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <iostream>
#include <string>

namespace
{
    constexpr int PORT = 8000;
    constexpr int BUFFER_SIZE = 4096;

    void SendResponse(
        int clientSocket,
        const std::string& body,
        const std::string& contentType,
        int statusCode = 200)
    {
        const std::string status =
            statusCode == 200 ? "200 OK" : "404 Not Found";

        const std::string response =
            "HTTP/1.1 " + status + "\r\n"
            "Content-Type: " + contentType + "\r\n"
            "Content-Length: " + std::to_string(body.size()) + "\r\n"
            "Connection: close\r\n"
            "Cache-Control: no-store\r\n"
            "\r\n" + body;

        std::size_t sent = 0;

        while (sent < response.size())
        {
            const ssize_t result = send(
                clientSocket,
                response.data() + sent,
                response.size() - sent,
                0);

            if (result <= 0)
            {
                break;
            }

            sent += static_cast<std::size_t>(result);
        }
    }

    void HandleClient(int clientSocket)
    {
        char buffer[BUFFER_SIZE] = {};

        const ssize_t received = recv(
            clientSocket,
            buffer,
            sizeof(buffer) - 1,
            0);

        if (received <= 0)
        {
            return;
        }

        const std::string request(
            buffer,
            static_cast<std::size_t>(received));

        const std::size_t lineEnd = request.find("\r\n");

        if (lineEnd == std::string::npos)
        {
            return;
        }

        const std::string requestLine =
            request.substr(0, lineEnd);

        const std::size_t firstSpace = requestLine.find(' ');
        const std::size_t secondSpace = requestLine.find(' ', firstSpace + 1);

        if (firstSpace == std::string::npos ||
            secondSpace == std::string::npos)
        {
            return;
        }

        const std::string method =
            requestLine.substr(0, firstSpace);

        const std::string path = requestLine.substr(
            firstSpace + 1,
            secondSpace - firstSpace - 1);

        if (method != "GET")
        {
            SendResponse(
                clientSocket,
                R"({"error":"Method not supported"})",
                "application/json",
                404);
        }
        else if (path == "/health")
        {
            SendResponse(
                clientSocket,
                "ok",
                "text/plain");
        }
        else if (path == "/status")
        {
            SendResponse(
                clientSocket,
                R"({"name":"BugBountyTrainer SQL Lab","status":"online","language":"C++20","database":"pending"})",
                "application/json");
        }
        else if (path == "/challenges")
        {
            SendResponse(
                clientSocket,
                R"({"challenges":[{"id":1,"title":"Basic SQL Injection","difficulty":"Beginner"},{"id":2,"title":"Boolean Query Manipulation","difficulty":"Intermediate"},{"id":3,"title":"Database Investigation","difficulty":"Intermediate"}]})",
                "application/json");
        }
        else if (path == "/")
        {
            SendResponse(
                clientSocket,
                "<h1>BugBountyTrainer C++ SQL Lab</h1>"
                "<p>Training server is online.</p>"
                "<p>Endpoints: /health, /status, /challenges</p>",
                "text/html; charset=utf-8");
        }
        else
        {
            SendResponse(
                clientSocket,
                R"({"error":"Not found"})",
                "application/json",
                404);
        }
    }
}

int main()
{
    const int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0)
    {
        std::cerr << "Failed to create socket.\n";
        return 1;
    }

    const int reuseAddress = 1;

    setsockopt(
        serverSocket,
        SOL_SOCKET,
        SO_REUSEADDR,
        &reuseAddress,
        sizeof(reuseAddress));

    sockaddr_in address = {};

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(
        serverSocket,
        reinterpret_cast<sockaddr*>(&address),
        sizeof(address)) < 0)
    {
        std::cerr << "Bind failed: "
                  << std::strerror(errno) << '\n';

        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 10) < 0)
    {
        std::cerr << "Listen failed.\n";
        close(serverSocket);
        return 1;
    }

    std::cout << "BugBountyTrainer C++ SQL Lab\n";
    std::cout << "Listening on port " << PORT << '\n';
    std::cout.flush();

    while (true)
    {
        sockaddr_in clientAddress = {};
        socklen_t clientLength = sizeof(clientAddress);

        const int clientSocket = accept(
            serverSocket,
            reinterpret_cast<sockaddr*>(&clientAddress),
            &clientLength);

        if (clientSocket < 0)
        {
            continue;
        }

        HandleClient(clientSocket);
        close(clientSocket);
    }

    close(serverSocket);
    return 0;
}