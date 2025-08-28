#ifndef MINIREDIS_INCLUDE_DATABASE_H_
#define MINIREDIS_INCLUDE_DATABASE_H_

#include <string>
#include "hash_table.h"

class Database {
private:
	HashTable store_;

public:
	void insert(const std::string& key, const std::string& value);
	std::string retrieve(const std::string& key);
	void remove(const std::string& key);

	double load_factor() const;
	size_t bucket_count() const { return store_.bucket_count(); }

};

#endif  // MINIREDIS_INCLUDE_DATABASE_H_
