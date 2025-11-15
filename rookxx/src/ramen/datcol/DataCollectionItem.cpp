#include "ramen/datcol/DataCollectionItem.h"

#include "ramen/datcol/DataCollectionDirectory.h"

using namespace rookxx::ramen::datcol;

#pragma region init

DataCollectionItem::DataCollectionItem(bool deleteOnDisown)
{
    f_Deleted = false;
    f_DeleteOnDisown = deleteOnDisown;
    f_Parent = nullptr;
}

DataCollectionItem::~DataCollectionItem()
{
    // TODO: Remove from parent
}

#pragma endregion

#pragma region properties

DataCollectionDirectory* DataCollectionItem::parent() { return f_Parent; }
const DataCollectionDirectory* DataCollectionItem::parent() const { return f_Parent; }

bool DataCollectionItem::deleteOnDisown() const { return f_DeleteOnDisown; }
void DataCollectionItem::deleteOnDisown(bool value) { f_DeleteOnDisown = value; }

const rookxx::ramen::String8& DataCollectionItem::name() const { return f_Name; }

#pragma endregion

#pragma region functions

bool DataCollectionItem::rename(const rookxx::ramen::String8& name)
{
    // Do not rename a root directory
    if (isRoot()) return false;
    // Is item within a directory?
    if (!f_Parent)
    {
        f_Name = name;
        return true;
    }
    // Yes!
    // TODO: Add code
    return false;
}

bool DataCollectionItem::rename(rookxx::ramen::String8&& name)
{
    // Do not rename a root directory
    if (isRoot()) return false;
    // Is item within a directory?
    if (!f_Parent)
    {
        f_Name = std::move(name);
        return true;
    }
    // Yes!
    // TODO: Add code
    return false;
}

#pragma endregion