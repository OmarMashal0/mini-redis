#include <iostream>
#include "database.h"

int main() {
	Database db;

	db.insert("user:1", "Alice");
	db.insert("user:2", "Bob");

	std::cout << "user:1 = " << db.retrieve("user:1") << std::endl;
	std::cout << "user:2 = " << db.retrieve("user:2") << std::endl;

	db.remove("user:1");
	std::cout << "user:1 after delete = " << db.retrieve("user:1") << std::endl;
	std::cout << "user:2 without delete = " << db.retrieve("user:2") << std::endl;

	std::cout << "Load factor = " << db.load_factor() << std::endl;

	return 0;
}
