#ifndef MINIREDIS_INCLUDE_HASH_TABLE_H_
#define MINIREDIS_INCLUDE_HASH_TABLE_H_

#include <string>
#include <vector>
#include <list>

class HashTable {
private:
	static const size_t kDefaultBucketCount = 16;
	std::vector<std::list<std::pair<std::string, std::string>>> buckets_;
	
	// --> load factor = usage / capacity
	size_t bucket_count_; // will be used to the capacity
	size_t element_count_;  // will be used to the usage

	size_t hash_function(const std::string& key) const;

	void rehash(size_t new_bucket_count);

public:
	explicit HashTable(size_t initial_bucket_count = kDefaultBucketCount);

	void insert(const std::string& key, const std::string& value);
	std::string retrieve(const std::string& key) const;
	void remove(const std::string& key);

	double load_factor() const;
	size_t bucket_count() const { return bucket_count_; }


};

#endif  // MINIREDIS_INCLUDE_HASH_TABLE_H_
