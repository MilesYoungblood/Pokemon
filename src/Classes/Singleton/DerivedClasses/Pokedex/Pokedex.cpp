//
// Created by Miles Youngblood on 3/4/2024.
//

#include "Pokedex.h"

Pokedex::Pokedex() {
    const auto error_message = [](const std::filesystem::path &path, const char *name, const char *type) -> void {
        std::clog << "Invalid XML file format in file " << path << ": missing \"" << name << "\" " << type << '\n';
    };

    for (const auto &entry : std::filesystem::recursive_directory_iterator("../assets/data/Pokemon/")) {
        tinyxml2::XMLDocument xmlDocument;
        const std::string path = entry.path().string();

        if (xmlDocument.LoadFile(path.c_str()) != tinyxml2::XML_SUCCESS) {
            xmlDocument.PrintError();
            continue;
        }

        tinyxml2::XMLElement *xmlElement = xmlDocument.FirstChildElement("xml");
        if (xmlElement == nullptr) {
            error_message(entry, "xml", "element");
            continue;
        }

        tinyxml2::XMLElement *data = xmlElement->FirstChildElement("data");
        if (data == nullptr) {
            error_message(entry, "data", "element");
            continue;
        }

        tinyxml2::XMLElement *dexElement = data->FirstChildElement("dex");
        if (dexElement == nullptr) {
            error_message(entry, "dex", "element");
            continue;
        }

        // Dex number

        const int dex_num = dexElement->IntText(-1);
        if (dex_num == -1) {
            error_message(entry, "dex", "text");
            continue;
        }

        // Name

        tinyxml2::XMLElement *nameElement = dexElement->NextSiblingElement("name");
        if (nameElement == nullptr) {
            error_message(entry, "name", "element");
            continue;
        }

        this->names.at(dex_num) = nameElement->GetText();

        // Species

        tinyxml2::XMLElement *speciesElement = nameElement->NextSiblingElement("species");
        if (speciesElement == nullptr) {
            error_message(entry, "species", "element");
            continue;
        }

        this->species.at(dex_num) = speciesElement->GetText();

        // Types

        tinyxml2::XMLElement *typeListElement = speciesElement->NextSiblingElement("types");
        if (typeListElement == nullptr) {
            error_message(entry, "types", "element");
            continue;
        }

        tinyxml2::XMLElement *type1Element = typeListElement->FirstChildElement("type");
        if (type1Element == nullptr) {
            error_message(entry, "type", "element");
            continue;
        }

        const int type1 = type1Element->IntText(-1);
        if (type1 == -1) {
            error_message(entry, "type", "text");
            continue;
        }

        this->type1Array.at(dex_num) = Type(type1);

        tinyxml2::XMLElement *type2Element = type1Element->NextSiblingElement("type");
        if (type2Element != nullptr) {
            const int type2 = type2Element->IntText(-1);
            if (type2 == -1) {
                error_message(entry, "type", "text");
                continue;
            }

            this->type2Array.at(dex_num) = Type(type2);
        }

        // Abilities

        tinyxml2::XMLElement *abilityListElement = typeListElement->NextSiblingElement("abilities");
        if (abilityListElement == nullptr) {
            error_message(entry, "abilities", "element");
            continue;
        }

        tinyxml2::XMLElement *ability1Element = abilityListElement->FirstChildElement("ability");
        if (ability1Element == nullptr) {
            error_message(entry, "ability", "element");
            continue;
        }

        const int ability1 = ability1Element->IntText(-1);
        if (ability1 == -1) {
            error_message(entry, "ability", "text");
            continue;
        }

        this->ability1Array.at(dex_num) = Ability::Id(ability1);

        tinyxml2::XMLElement *ability2Element = ability1Element->NextSiblingElement("ability");
        if (ability2Element != nullptr) {
            const int ability2 = ability2Element->IntText(-1);
            if (ability2 == -1) {
                error_message(entry, "ability", "text");
                continue;
            }

            this->ability2Array.at(dex_num) = Ability::Id(ability2);
        }

        // Height

        tinyxml2::XMLElement *heightElement = abilityListElement->NextSiblingElement("height");
        if (heightElement == nullptr) {
            error_message(entry, "height", "element");
            continue;
        }

        const double height = heightElement->DoubleText(-1.0);
        if (height == -1.0) {
            error_message(entry, "height", "text");
            continue;
        }

        this->heights.at(dex_num) = height;

        // Weight

        tinyxml2::XMLElement *weightElement = heightElement->NextSiblingElement("weight");
        if (weightElement == nullptr) {
            error_message(entry, "weight", "element");
            continue;
        }

        const double weight = weightElement->DoubleText(-1.0);
        if (weight == -1.0) {
            error_message(entry, "weight", "text");
            continue;
        }

        this->weights.at(dex_num) = weight;

        // Gender ratios

        tinyxml2::XMLElement *genderElement = weightElement->NextSiblingElement("gender");
        if (genderElement == nullptr) {
            error_message(entry, "gender", "element");
            continue;
        }

        const double male = genderElement->DoubleAttribute("male", std::numeric_limits<int>::max());
        if (male == std::numeric_limits<int>::max()) {
            error_message(entry, "male", "attribute");
            continue;
        }

        this->genderRatios.at(dex_num) = male;

        // Base stats

        tinyxml2::XMLElement *baseStatListElement = genderElement->NextSiblingElement("base_stats");
        if (baseStatListElement == nullptr) {
            error_message(entry, "base_stats", "element");
            continue;
        }

        int i = 0;
        for (tinyxml2::XMLElement *statElement = baseStatListElement->FirstChildElement("stat");
             statElement != nullptr; statElement = statElement->NextSiblingElement("stat")) {
            const int stat = statElement->IntText(-1);
            if (stat == -1) {
                error_message(entry, "stat", "text");
                continue;
            }
            this->baseStats.at(dex_num).at(i) = statElement->IntText();
            ++i;
        }

        // Catch rate

        tinyxml2::XMLElement *catchRateElement = baseStatListElement->NextSiblingElement("catch_rate");
        if (catchRateElement == nullptr) {
            error_message(entry, "catch_rate", "element");
            continue;
        }

        const int catch_rate = catchRateElement->IntText(-1);
        if (catch_rate == -1) {
            error_message(entry, "catch_rate", "text");
            continue;
        }

        this->catchRates.at(dex_num) = catch_rate;
    }
}
