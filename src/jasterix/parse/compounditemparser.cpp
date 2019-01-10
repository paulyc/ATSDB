#include "compounditemparser.h"

using namespace std;
using namespace nlohmann;

namespace jASTERIX
{

CompoundItemParser::CompoundItemParser (const nlohmann::json& item_definition)
 : ItemParser (item_definition)
{
    assert (type_ == "compound");

    if (item_definition.find("field_specification") == item_definition.end())
        throw runtime_error ("compound item '"+name_+"' parsing without field specification");

    const json& field_specification = item_definition.at("field_specification");

    if (!field_specification.is_object())
        throw runtime_error ("parsing compound item '"+name_+"' field specification is not an object");

    //field_specification_name_ = field_specification.at("name");

    field_specification_.reset(ItemParser::createItemParser(field_specification));
    assert (field_specification_);

    if (item_definition.find("items") == item_definition.end())
        throw runtime_error ("parsing compound item '"+name_+"' without items");

    const json& items = item_definition.at("items");

    if (!items.is_array())
        throw runtime_error ("parsing compound item '"+name_+"' field specification is not an array");

    std::string item_name;
    ItemParser* item {nullptr};

    for (const json& data_item_it : items)
    {
        item_name = data_item_it.at("name");
        item = ItemParser::createItemParser(data_item_it);
        assert (item);
        items_.push_back(std::unique_ptr<ItemParser>{item});
    }
}

size_t CompoundItemParser::parseItem (const char* data, size_t index, size_t size, size_t current_parsed_bytes,
                              nlohmann::json& target, nlohmann::json& parent, bool debug)
{
    if (debug)
        loginf << "parsing compound item '" << name_ << "' with " << items_.size() << " items";

    size_t parsed_bytes {0};

    if (debug)
        loginf << "parsing compound item '"+name_+"' field specification";

    parsed_bytes = field_specification_->parseItem(data, index+parsed_bytes, size, parsed_bytes, target, target, debug);

    if (debug)
        loginf << "parsing compound item '"+name_+"' data items";

    for (auto& data_item_it : items_)
    {
        if (debug)
            loginf << "parsing compound item '" << name_ << "' data item '" << data_item_it->name() << "' index "
                   << index+parsed_bytes;

        parsed_bytes += data_item_it->parseItem(data, index+parsed_bytes, size, parsed_bytes, target, target, debug);
    }

    return parsed_bytes;
}

}
