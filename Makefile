all:
	g++ -Iinclude src/hash_table.cpp src/database.cpp main.cpp -o mini_redis
