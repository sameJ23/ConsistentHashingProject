#include <iostream>
#include <sstream>
#include <string>

#include "cache_router.hpp"

void showHelp()
{
    std::cout << "\nCommands:\n";
    std::cout << "  add-server <name>\n";
    std::cout << "  remove-server <name>\n";
    std::cout << "  put <key> <value>\n";
    std::cout << "  get <key>\n";
    std::cout << "  show-ring\n";
    std::cout << "  show-servers\n";
    std::cout << "  help\n";
    std::cout << "  quit\n\n";
}

int main()
{
    CacheRouter router;

    std::cout << "Distributed Cache Router\n";

    showHelp();

    std::string line;

    while (true)
    {
        std::cout << "> ";

        std::getline(std::cin, line);

        std::istringstream input(line);

        std::string command;

        input >> command;

        if (command == "add-server")
        {
            std::string serverName;

            input >> serverName;

            if (serverName.empty())
            {
                std::cout << "Usage: add-server <name>\n";
                continue;
            }

            router.addServer(serverName);
        }

        else if (command == "remove-server")
        {
            std::string serverName;

            input >> serverName;

            if (serverName.empty())
            {
                std::cout << "Usage: remove-server <name>\n";
                continue;
            }

            router.removeServer(serverName);
        }

        else if (command == "put")
        {
            std::string key;
            std::string value;

            input >> key;

            std::getline(input >> std::ws, value);

            if (key.empty() || value.empty())
            {
                std::cout << "Usage: put <key> <value>\n";
                continue;
            }

            router.put(key, value);
        }

        else if (command == "get")
        {
            std::string key;

            input >> key;

            if (key.empty())
            {
                std::cout << "Usage: get <key>\n";
                continue;
            }

            std::string value = router.get(key);

            if (value.empty())
            {
                std::cout << "Key not found.\n";
            }
            else
            {
                std::cout
                    << key
                    << " -> "
                    << value
                    << "\n";
            }
        }

        else if (command == "show-ring")
        {
            router.showRing();
        }

        else if (command == "show-servers")
        {
            router.showServers();
        }

        else if (command == "help")
        {
            showHelp();
        }

        else if (command == "quit")
        {
            break;
        }

        else if (command.empty())
        {
            continue;
        }

        else
        {
            std::cout
                << "Unknown command. Type 'help' for commands.\n";
        }
    }

    return 0;
}