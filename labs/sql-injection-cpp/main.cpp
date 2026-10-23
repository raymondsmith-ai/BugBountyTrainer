#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Database.h"
#include "LessonManager.h"
#include "LabManager.h"

// ====================================
// BugBountyTrainer SQL Injection Academy
// C++20 Docker Training Server
// ====================================

namespace
{
    constexpr int PORT = 8000;
    constexpr int BUFFER_SIZE = 4096;
    // ====================================
    // Read Website Files
    // ====================================

    std::string ReadWebFile(const std::string& filename)
    {
        std::ifstream file(
            "/app/web/" + filename,
            std::ios::binary);

        if (!file.is_open())
        {
            return "";
        }

        std::ostringstream content;
        content << file.rdbuf();

        return content.str();
    }

    // ====================================
    // Send HTTP Response
    // ====================================

    void SendResponse(
        int clientSocket,
        const std::string& body,
        const std::string& contentType,
        int statusCode = 200)
    {
        std::string status;

        switch (statusCode)
        {
        case 200:
            status = "200 OK";
            break;

        case 404:
            status = "404 Not Found";
            break;

        case 405:
            status = "405 Method Not Allowed";
            break;

        default:
            status = "500 Internal Server Error";
            break;
        }

        const std::string response =
            "HTTP/1.1 " + status + "\r\n"
            "Content-Type: " + contentType + "\r\n"
            "Content-Length: " + std::to_string(body.size()) + "\r\n"
            "Connection: close\r\n"
            "Cache-Control: no-store\r\n"
            "X-Content-Type-Options: nosniff\r\n"
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

    // ====================================
    // Handle Client HTTP Requests
    // ====================================

  void HandleClient(int clientSocket, sqlite3* database)
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

        const std::size_t firstSpace =
            requestLine.find(' ');

        if (firstSpace == std::string::npos)
        {
            return;
        }

        const std::size_t secondSpace =
            requestLine.find(' ', firstSpace + 1);

        if (secondSpace == std::string::npos)
        {
            return;
        }

        const std::string method =
            requestLine.substr(0, firstSpace);

        const std::string path =
            requestLine.substr(
                firstSpace + 1,
                secondSpace - firstSpace - 1);

        // ====================================
        // Validate HTTP Method
        // ====================================

        if (method != "GET")
        {
            SendResponse(
                clientSocket,
                R"({"error":"Method not supported"})",
                "application/json",
                405);
        }

        // ====================================
        // Health Check
        // ====================================

        else if (path == "/health")
        {
            SendResponse(
                clientSocket,
                "ok",
                "text/plain",
                200);
        }

        // ====================================
        // Docker Server Status
        // ====================================

        else if (path == "/status")
        {
            SendResponse(
                clientSocket,
                R"({
                    "name": "BugBountyTrainer SQL Lab",
                    "status": "online",
                    "language": "C++20",
                    "database": "ready",
                    "database_engine": "SQLite3",
                    "course": "SQL Injection Academy",
                    "total_modules": 13
                })",
                "application/json",
                200);
        }

        // ====================================
        // Available SQL Injection Challenges
        // ====================================

        else if (path == "/challenges")
        {
            SendResponse(
                clientSocket,
                R"({
                    "challenges": [
                        {
                            "id": 1,
                            "title": "Basic SQL Injection",
                            "difficulty": "Beginner"
                        },
                        {
                            "id": 2,
                            "title": "Boolean Query Manipulation",
                            "difficulty": "Intermediate"
                        },
                        {
                            "id": 3,
                            "title": "Database Investigation",
                            "difficulty": "Intermediate"
                        }
                    ]
                })",
                "application/json",
                200);
        }

        // ====================================
        // Complete SQL Injection Curriculum
        // ====================================

        else if (path == "/lessons")
        {
            SendResponse(
                clientSocket,
                R"({
                    "course": "SQL Injection Academy",
                    "description": "Complete beginner-to-intermediate SQL Injection training",
                    "language": "C++20",
                    "database": "SQLite3",
                    "total_modules": 13,
                    "modules": [
                        {
                            "id": 1,
                            "title": "Introduction to Databases",
                            "difficulty": "Beginner"
                        },
                        {
                            "id": 2,
                            "title": "SQL Fundamentals",
                            "difficulty": "Beginner"
                        },
                        {
                            "id": 3,
                            "title": "Understanding SQL Injection",
                            "difficulty": "Beginner"
                        },
                        {
                            "id": 4,
                            "title": "Basic SQL Injection",
                            "difficulty": "Beginner"
                        },
                        {
                            "id": 5,
                            "title": "Preventing SQL Injection",
                            "difficulty": "Beginner"
                        },
                        {
                            "id": 6,
                            "title": "SQL Query Manipulation",
                            "difficulty": "Developing"
                        },
                        {
                            "id": 7,
                            "title": "UNION-Based SQL Injection",
                            "difficulty": "Developing"
                        },
                        {
                            "id": 8,
                            "title": "Database Enumeration",
                            "difficulty": "Developing"
                        },
                        {
                            "id": 9,
                            "title": "Authentication Vulnerabilities",
                            "difficulty": "Intermediate"
                        },
                        {
                            "id": 10,
                            "title": "Error-Based SQL Injection",
                            "difficulty": "Intermediate"
                        },
                        {
                            "id": 11,
                            "title": "Blind SQL Injection",
                            "difficulty": "Intermediate"
                        },
                        {
                            "id": 12,
                            "title": "Secure Database Development",
                            "difficulty": "Intermediate"
                        },
                        {
                            "id": 13,
                            "title": "Final Practical Assessment",
                            "difficulty": "Intermediate"
                        }
                    ]
                })",
                "application/json",
                200);
        }

        // ====================================
        // Module 1: Introduction to Databases
        // ====================================

        else if (path == "/lessons/1")
        {
            SendResponse(
                clientSocket,
                LessonManager::GetLesson(1),
                "application/json",
                200);
        }

	// ====================================
	// Module 1: SQLite Guided Laboratories
	// ====================================

	else if (path == "/labs/1")
	{
	    SendResponse(
	        clientSocket,
	        LabManager::RunExercise(database, 1),
	        "text/plain; charset=utf-8",
	        200);
}
else if (path == "/labs/2")
{
    SendResponse(
        clientSocket,
        LabManager::RunExercise(database, 2),
        "text/plain; charset=utf-8",
        200);
}
else if (path == "/labs/3")
{
    SendResponse(
        clientSocket,
        LabManager::RunExercise(database, 3),
        "text/plain; charset=utf-8",
        200);
}

          // ====================================
        // SQL Injection Academy Homepage
        // ====================================

        else if (path == "/")
        {
            const std::string page = ReadWebFile("index.html");

            if (page.empty())
            {
                SendResponse(
                    clientSocket,
                    "Website unavailable.",
                    "text/plain",
                    404);
            }
            else
            {
                SendResponse(
                    clientSocket,
                    page,
                    "text/html; charset=utf-8",
                    200);
            }
        }

        // ====================================
        // Website Stylesheet
        // ====================================

        else if (path == "/style.css")
        {
            const std::string stylesheet =
                ReadWebFile("style.css");

            if (stylesheet.empty())
            {
                SendResponse(
                    clientSocket,
                    "Stylesheet unavailable.",
                    "text/plain",
                    404);
            }
            else
            {
                SendResponse(
                    clientSocket,
                    stylesheet,
                    "text/css; charset=utf-8",
                    200);
            }
        }
        // ====================================
        // Website JavaScript
        // ====================================

        else if (path == "/app.js")
        {
            const std::string script = ReadWebFile("app.js");

            if (script.empty())
            {
                SendResponse(
                    clientSocket,
                    "JavaScript unavailable.",
                    "text/plain",
                    404);
            }
            else
            {
                SendResponse(
                    clientSocket,
                    script,
                    "application/javascript; charset=utf-8",
                    200);
            }
        }

        // ====================================
        // Unknown Endpoint
        // ====================================

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

// ====================================
// Main Application
// ====================================

int main()
{
    // ====================================
    // Initialize SQLite Database
    // ====================================

    Database trainingDatabase;

    if (!trainingDatabase.Initialize())
    {
        std::cerr
            << "Failed to initialize training database.\n";

        return 1;
    }

    std::cout
        << "SQLite training database initialized.\n";

    // ====================================
    // Create Server Socket
    // ====================================

    const int serverSocket =
        socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0)
    {
        std::cerr
            << "Failed to create server socket.\n";

        return 1;
    }

    // ====================================
    // Enable Address Reuse
    // ====================================

    const int reuseAddress = 1;

    setsockopt(
        serverSocket,
        SOL_SOCKET,
        SO_REUSEADDR,
        &reuseAddress,
        sizeof(reuseAddress));

    // ====================================
    // Configure Server Address
    // ====================================

    sockaddr_in address = {};

    address.sin_family = AF_INET;

    address.sin_addr.s_addr = INADDR_ANY;

    address.sin_port = htons(PORT);

    // ====================================
    // Bind Socket
    // ====================================

    if (bind(
        serverSocket,
        reinterpret_cast<sockaddr*>(&address),
        sizeof(address)) < 0)
    {
        std::cerr
            << "Bind failed: "
            << std::strerror(errno)
            << '\n';

        close(serverSocket);

        return 1;
    }

    // ====================================
    // Start Listening
    // ====================================

    if (listen(serverSocket, 10) < 0)
    {
        std::cerr
            << "Failed to start listening.\n";

        close(serverSocket);

        return 1;
    }

    // ====================================
    // Server Ready
    // ====================================

    std::cout
        << "\n====================================\n"
        << "      BUGBOUNTYTRAINER SQL ACADEMY\n"
        << "====================================\n"
        << "Language: C++20\n"
        << "Database: SQLite3\n"
        << "Course Modules: 13\n"
        << "Server Port: " << PORT << '\n'
        << "Status: ONLINE\n"
        << "====================================\n";

    std::cout.flush();

    // ====================================
    // Accept Client Connections
    // ====================================

    while (true)
    {
        sockaddr_in clientAddress = {};

        socklen_t clientLength =
            sizeof(clientAddress);

        const int clientSocket = accept(
            serverSocket,
            reinterpret_cast<sockaddr*>(&clientAddress),
            &clientLength);

        if (clientSocket < 0)
        {
            continue;
        }

        HandleClient(clientSocket, trainingDatabase.GetConnection());

        close(clientSocket);
    }

    close(serverSocket);

    return 0;
}
