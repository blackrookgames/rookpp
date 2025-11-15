#include "ramen/datcol/DataCollectionDirectory.h"

#include "ramen/datcol/DataCollection.h"

using namespace rookxx::ramen::datcol;

#pragma region init

DataCollectionDirectory::DataCollectionDirectory(bool isRoot, bool deleteOnDisown) :
    DataCollectionItem(deleteOnDisown)
{
    f_IsRoot = isRoot;
}

DataCollectionDirectory::DataCollectionDirectory(bool deleteOnDisown) :
    DataCollectionDirectory(false, deleteOnDisown)
{ }

DataCollectionDirectory::~DataCollectionDirectory()
{ }

#pragma endregion

#pragma region properties

bool DataCollectionDirectory::isFile() const { return false; }

bool DataCollectionDirectory::isDirectory() const { return true; }

bool DataCollectionDirectory::isRoot() const { return f_IsRoot; }

#pragma endregion