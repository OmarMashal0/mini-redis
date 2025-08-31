# 🗄️ Mini-Redis: High-Performance In-Memory Database

📌 **Overview**  
Mini-Redis is a C++17 in-memory key-value database inspired by Redis.  
It supports core commands (SET, GET, DEL, EXISTS, KEYS, PREFIX, RANGE, FLUSHALL), automatic persistence, and efficient data structures like hash tables, tries, and LRU caches — all implemented from scratch.

---

## ✨ Features
- **SET / GET / DEL** → O(1) average time complexity  
- **EXISTS** → fast key existence check  
- **KEYS** → wildcard search (e.g., `KEYS user*`)  
- **PREFIX** → efficient prefix search via trie  
- **RANGE** → ordered range queries using red-black tree indexing  
- **FLUSHALL** → clear database in memory + persistence log  
- **Persistence** → append-only log with crash recovery  
- **LRU Cache** → hot key optimization  

---

## 📊 Time Complexity

| Command   | Average Case   | Worst Case   |
|-----------|----------------|--------------|
| **SET**   | O(1)           | O(n)         |
| **GET**   | O(1)           | O(n)         |
| **DEL**   | O(1)           | O(n)         |
| **EXISTS**| O(1)           | O(n)         |
| **KEYS**  | O(k)           | O(n)         |
| **PREFIX**| O(k)           | O(n)         |
| **RANGE** | O(log n + k)   | O(n)         |
| **FLUSHALL** | O(n)        | O(n)         |

*(n = total keys, k = result size)*

---

## 🛠️ Installation

### Prerequisites
- **C++17 compiler** (GCC 7+, Clang 5+, or MSVC 2017+)  
- **Make** (GNU Make)  
- OS: Linux, macOS, or Windows  

### Build & Run
```bash
git clone https://github.com/yourusername/mini-redis.git
cd mini-redis
make
./mini_redis       # Linux/macOS
mini_redis.exe     # Windows
```

---

## 📋 Commands

| Command           | Description                 | Example               |
|-------------------|-----------------------------|-----------------------|
| `SET key value`   | Store a key-value pair      | `SET user1 john`      |
| `GET key`         | Retrieve value by key       | `GET user1`           |
| `DEL key`         | Delete a key                | `DEL user1`           |
| `EXISTS key`      | Check if key exists         | `EXISTS user1`        |
| `KEYS pattern`    | Find keys by wildcard       | `KEYS user*`          |
| `PREFIX prefix`   | Find keys by prefix         | `PREFIX user`         |
| `RANGE start end` | Keys in sorted range        | `RANGE a z`           |
| `FLUSHALL`        | Clear all keys              | `FLUSHALL`            |
| `HELP`            | Show available commands     | `HELP`                |
| `EXIT`            | Quit program                | `EXIT`                |

---

## 💡 Example Usage
```
> set user1 omar
OK
> set user2 mashal
OK
> get user1
omar
> keys user*
user1 user2
> prefix user
user1 user2
> range a z
user1 user2
> del user1
OK
> exists user1
0
> flushall
OK
> keys *
(empty)
```

---

## 🏗️ Project Structure
```
mini-redis/
├── include/           # header files
│   ├── database.h     # database interface
│   ├── hash_table.h   # hash table
│   ├── lru_cache.h    # lru cache
│   └── trie.h         # trie data structure
├── src/               # implementation files
│   ├── database.cpp   # database logic and persistence
│   ├── hash_table.cpp # hash table
│   ├── lru_cache.cpp  # lru cache
│   └── trie.cpp       # trie
├── main.cpp           # cli interface
├── Makefile           # build config
├── README.md          # this file
└── LICENSE            # license
```

---

## 📝 License
This project is licensed under the MIT License – see [LICENSE](LICENSE)
