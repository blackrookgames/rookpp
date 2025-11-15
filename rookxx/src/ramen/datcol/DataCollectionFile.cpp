#include "ramen/datcol/DataCollectionFile.h"

using namespace rookxx::ramen::datcol;

#pragma region init

DataCollectionFile::DataCollectionFile(bool deleteOnDisown) :
    DataCollectionItem(deleteOnDisown)
{ }


DataCollectionFile::~DataCollectionFile()
{ }

#pragma endregion

#pragma region properties

bool DataCollectionFile::isFile() const { return true; }

bool DataCollectionFile::isDirectory() const { return false; }

bool DataCollectionFile::isRoot() const { return false; }

#pragma endregion