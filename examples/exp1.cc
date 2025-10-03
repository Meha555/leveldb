#include <iostream>
#include <string>
#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/write_batch.h"
#include "leveldb/comparator.h"

using namespace leveldb;

int main() {
    // Open
    DB *db;
    Options options;
    options.create_if_missing = true;
    std::string dbName("expdb");
    Status status = DB::Open(options, dbName, &db);
    std::cout << "Open DB: " << status.ToString() << std::endl;

    // Put
    WriteOptions woptions;
    status = db->Put(woptions, "key1", "value1");
    std::cout << "Put: " << status.ToString() << std::endl;

    // Get
    ReadOptions roptions;
    std::string value;
    status = db->Get(roptions, "key1", &value);
    std::cout << "Get: " << status.ToString() << std::endl;

    // WriteBatch
    WriteBatch batch;
    batch.Put("key2", "value2");
    batch.Put("key3", "value3");
    // batch.Delete("key1");
    status = db->Write(woptions, &batch);
    std::cout << "WriteBatch: " << status.ToString() << std::endl;

    // Delete
    status = db->Delete(woptions, "key1");
    std::cout << "Delete: " << status.ToString() << std::endl;

    // Iterator
    Iterator* iter = db->NewIterator(roptions);
    iter->SeekToFirst();
    while (iter->Valid()) {
        Slice key = iter->key();
        Slice value = iter->value();
        std::cout << "key: " << key.ToString() << " value: " << value.ToString() << std::endl;
        iter->Next();
    }

    delete iter;
    delete db;
    return 0;
}