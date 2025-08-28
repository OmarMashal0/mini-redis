#include <iostream>
#include "database.h"

int main() {
    Database db;

    for (int i = 1; i <= 50; i++) {
        db.insert("key" + std::to_string(i), "val" + std::to_string(i));

        std::cout << "Inserted key" << i
            << " | Load factor = " << db.load_factor()
            << " | Buckets = " << db.bucket_count()
            << std::endl;
    }

    return 0;
}
