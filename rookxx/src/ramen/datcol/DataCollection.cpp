#include "ramen/datcol/DataCollection.h"

using namespace rookxx::ramen::datcol;

#pragma region init

DataCollection::DataCollection() :
    f_Root(true, false)
{ }

DataCollection::~DataCollection()
{ }

#pragma endregion

#pragma region serialization

bool DataCollection::serialize(uint8_t*& data, size_t& size) const
{
    data = nullptr;
    size = 0;
    return false;
}

bool DataCollection::deserialize(const uint8_t* data, size_t size)
{
    return false;
}

bool DataCollection::serialize(SmartWriter& sw) const
{
    return false;
}

bool DataCollection::deserialize(SmartReader& sr)
{
    return false;
}

#pragma endregion

#pragma region properties

DataCollectionDirectory& DataCollection::root() { return f_Root; }
const DataCollectionDirectory& DataCollection::root() const { return f_Root; }

#pragma endregion