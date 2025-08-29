all:
	g++ -Iinclude src/hash_table.cpp src/database.cpp src/trie.cpp main.cpp -o mini_redis
