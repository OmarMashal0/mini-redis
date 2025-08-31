#include <iostream>
#include <sstream>
#include <cctype>
#include "database.h"

void printHelp() {
    std::cout << "Mini-Redis - Available Commands:" << std::endl;
    std::cout << "  SET key value          - Set key to hold value" << std::endl;
    std::cout << "  GET key                - Get value of key" << std::endl;
    std::cout << "  DEL key                - Delete key" << std::endl;
    std::cout << "  EXISTS key             - Check if key exists" << std::endl;
    std::cout << "  KEYS pattern           - Find keys matching pattern (use * for all, a* for prefix)" << std::endl;
    std::cout << "  PREFIX prefix          - Find keys with prefix" << std::endl;
    std::cout << "  RANGE start end        - Find keys in range" << std::endl;
    std::cout << "  FLUSHALL               - Remove all keys" << std::endl;
    std::cout << "  HELP                   - Show this help message" << std::endl;
    std::cout << "  EXIT                   - Exit the program" << std::endl;
    std::cout << std::endl;
    std::cout << "Note: Commands are case-insensitive (set, Set, SET all work)" << std::endl;
}

std::string toUpper(const std::string& str) {
    std::string result = str;
    for (char& c : result) {
        c = std::toupper(c);
    }
    return result;
}

int main() {
    Database db(3);

    std::cout << "Mini-Redis (C++ In-Memory DB)" << std::endl;
    std::cout << "Type HELP for available commands" << std::endl;

    std::string line;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);

        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;
        
        cmd = toUpper(cmd);

        if (cmd == "SET") {
            std::string key, value;
            ss >> key >> value;
            if (key.empty() || value.empty()) {
                std::cout << "Usage: SET key value" << std::endl;
                continue;
            }
            db.insert(key, value);
            std::cout << "OK" << std::endl;
        }
        else if (cmd == "GET") {
            std::string key;
            ss >> key;
            std::string val = db.retrieve(key);
            if (val.empty()) std::cout << "(nil)" << std::endl;
            else std::cout << val << std::endl;
        }
        else if (cmd == "DEL") {
            std::string key;
            ss >> key;
            db.remove(key);
            std::cout << "OK" << std::endl;
        }
        else if (cmd == "EXISTS") {
            std::string key;
            ss >> key;
            if (key.empty()) {
                std::cout << "Usage: EXISTS key" << std::endl;
                continue;
            }
            bool exists = db.exists(key);
            std::cout << (exists ? "1" : "0") << std::endl;
        }
        else if (cmd == "KEYS") {
            std::string pattern;
            ss >> pattern;
            if (pattern.empty()) {
                std::cout << "Usage: KEYS pattern" << std::endl;
                continue;
            }
            auto keys = db.keys(pattern);
            if (keys.empty()) std::cout << "(empty)" << std::endl;
            else {
                for (const auto& k : keys) std::cout << k << " ";
                std::cout << std::endl;
            }
        }
        else if (cmd == "PREFIX") {
            std::string prefix;
            ss >> prefix;
            auto keys = db.keysWithPrefix(prefix);
            if (keys.empty()) std::cout << "(empty)" << std::endl;
            else {
                for (const auto& k : keys) std::cout << k << " ";
                std::cout << std::endl;
            }
        }
        else if (cmd == "RANGE") {
            std::string start, end;
            ss >> start >> end;
            auto keys = db.rangeQuery(start, end);
            if (keys.empty()) std::cout << "(empty)" << std::endl;
            else {
                for (const auto& k : keys) std::cout << k << " ";
                std::cout << std::endl;
            }
        }
        else if (cmd == "FLUSHALL") {
            db.flushAll();
            std::cout << "OK" << std::endl;
        }
        else if (cmd == "HELP") {
            printHelp();
        }
        else if (cmd == "EXIT") {
            break;
        }
        else {
            std::cout << "Unknown command: " << cmd << std::endl;
            std::cout << "Type HELP for available commands" << std::endl;
        }
    }

    std::cout << "Bye!" << std::endl;
    return 0;
}
