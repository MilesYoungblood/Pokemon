//
// Created by Miles Youngblood on 3/4/2024.
//

#include "Pokedex.h"

Pokedex::Pokedex() {
    const auto errorMessage = [](const std::filesystem::path &path, const char *name, const char *type) -> void {
        std::clog << "Invalid XML file format in file " << path << ": missing \"" << name << "\" " << type << '\n';
    };

    for (const auto &entry : std::filesystem::recursive_directory_iterator("../assets/data/Pokemon/")) {
        tinyxml2::XMLDocument xmlDocument;
        const std::string path = entry.path().string();

        if (xmlDocument.LoadFile(path.c_str()) != tinyxml2::XML_SUCCESS) {
            xmlDocument.PrintError();
            continue;
        }

        const std::string name(entry.path().stem().string());

        tinyxml2::XMLElement *xmlElement = xmlDocument.FirstChildElement("xml");
        if (xmlElement == nullptr) {
            errorMessage(entry, "xml", "element");
            continue;
        }

        tinyxml2::XMLElement *dataElement = xmlElement->FirstChildElement("data");
        if (dataElement == nullptr) {
            errorMessage(entry, "data", "element");
            continue;
        }

        // Species

        tinyxml2::XMLElement *speciesElement = dataElement->FirstChildElement("species");
        if (speciesElement == nullptr) {
            errorMessage(entry, "species", "element");
            continue;
        }

        this->species[name] = speciesElement->GetText();

        // Types

        tinyxml2::XMLElement *typeListElement = speciesElement->NextSiblingElement("types");
        if (typeListElement == nullptr) {
            errorMessage(entry, "types", "element");
            continue;
        }

        tinyxml2::XMLElement *type1Element = typeListElement->FirstChildElement("type");
        if (type1Element == nullptr) {
            errorMessage(entry, "type", "element");
            continue;
        }

        const int type1 = type1Element->IntText(-1);
        if (type1 == -1) {
            errorMessage(entry, "type", "text");
            continue;
        }

        this->type1Array[name] = static_cast<Type>(type1);

        if (tinyxml2::XMLElement *type2Element = type1Element->NextSiblingElement("type"); type2Element != nullptr) {
            const int type2 = type2Element->IntText(-1);
            if (type2 == -1) {
                errorMessage(entry, "type", "text");
                continue;
            }

            this->type2Array[name] = static_cast<Type>(type2);
        }
        else {
            this->type2Array[name] = Type::NONE;
        }

        // Abilities

        tinyxml2::XMLElement *abilityListElement = typeListElement->NextSiblingElement("abilities");
        if (abilityListElement == nullptr) {
            errorMessage(entry, "abilities", "element");
            continue;
        }

        tinyxml2::XMLElement *ability1Element = abilityListElement->FirstChildElement("ability");
        if (ability1Element == nullptr) {
            errorMessage(entry, "ability", "element");
            continue;
        }

        const char *ability1 = ability1Element->GetText();
        if (ability1 == nullptr) {
            errorMessage(entry, "ability", "text");
            continue;
        }

        this->ability1Array[name] = ability1;

        if (tinyxml2::XMLElement *ability2Element = ability1Element->NextSiblingElement("ability"); ability2Element != nullptr) {
            const char *ability2 = ability2Element->GetText();
            if (ability2 == nullptr) {
                errorMessage(entry, "ability", "text");
                continue;
            }

            this->ability2Array[name] = ability2;
        }

        // Height

        tinyxml2::XMLElement *heightElement = abilityListElement->NextSiblingElement("height");
        if (heightElement == nullptr) {
            errorMessage(entry, "height", "element");
            continue;
        }

        const double height = heightElement->DoubleText(-1.0);
        if (height == -1.0) {
            errorMessage(entry, "height", "text");
            continue;
        }

        this->heights[name] = height;

        // Weight

        tinyxml2::XMLElement *weightElement = heightElement->NextSiblingElement("weight");
        if (weightElement == nullptr) {
            errorMessage(entry, "weight", "element");
            continue;
        }

        const double weight = weightElement->DoubleText(-1.0);
        if (weight == -1.0) {
            errorMessage(entry, "weight", "text");
            continue;
        }

        this->weights[name] = weight;

        // Gender ratios

        tinyxml2::XMLElement *genderElement = weightElement->NextSiblingElement("gender");
        if (genderElement == nullptr) {
            errorMessage(entry, "gender", "element");
            continue;
        }

        const double male = genderElement->DoubleAttribute("male", std::numeric_limits<int>::max());
        if (male == std::numeric_limits<int>::max()) {
            errorMessage(entry, "male", "attribute");
            continue;
        }

        this->genderRatios[name] = male;

        // Base stats

        tinyxml2::XMLElement *baseStatListElement = genderElement->NextSiblingElement("base_stats");
        if (baseStatListElement == nullptr) {
            errorMessage(entry, "base_stats", "element");
            continue;
        }

        int i = 0;
        for (tinyxml2::XMLElement *statElement = baseStatListElement->FirstChildElement("stat");
             statElement != nullptr; statElement = statElement->NextSiblingElement("stat")) {
            if (const int stat = statElement->IntText(-1); stat == -1) {
                errorMessage(entry, "stat", "text");
                continue;
            }
            this->baseStats[name].at(i) = statElement->IntText();
            ++i;
        }

        // Base level

        tinyxml2::XMLElement *baseLevelElement = baseStatListElement->NextSiblingElement("base_level");
        if (baseLevelElement == nullptr) {
            errorMessage(entry, "base_level", "element");
            continue;
        }

        const int baseLevel = baseLevelElement->IntText(-1);
        if (baseLevel == -1) {
            errorMessage(entry, "base_level", "text");
            continue;
        }

        this->baseLevels[name] = baseLevel;

        // Catch rate

        tinyxml2::XMLElement *catchRateElement = baseLevelElement->NextSiblingElement("catch_rate");
        if (catchRateElement == nullptr) {
            errorMessage(entry, "catch_rate", "element");
            continue;
        }

        const int catchRate = catchRateElement->IntText(-1);
        if (catchRate == -1) {
            errorMessage(entry, "catch_rate", "text");
            continue;
        }

        this->catchRates[name] = catchRate;

        // Dex num

        tinyxml2::XMLElement *dexElement = catchRateElement->NextSiblingElement("dex");
        if (dexElement == nullptr) {
            errorMessage(entry, "dex", "element");
            continue;
        }

        const int dex = dexElement->IntText(-1);
        if (dex == -1) {
            errorMessage(entry, "dex", "text");
            continue;
        }

        this->dexNums[name] = dex;
    }
}

std::string Pokedex::getSpecies(const std::string &id) const {
    return this->species.at(id);
}

Type Pokedex::getType1(const std::string &id) const {
    return this->type1Array.at(id);
}

Type Pokedex::getType2(const std::string &id) const {
    return this->type2Array.at(id);
}

double Pokedex::getHeight(const std::string &id) const {
    return this->heights.at(id);
}

double Pokedex::getWeight(const std::string &id) const {
    return this->weights.at(id);
}

double Pokedex::getGenderRatio(const std::string &id) const {
    return this->genderRatios.at(id);
}

int Pokedex::getBaseStat(const std::string &id, const int stat) const {
    return this->baseStats.at(id).at(stat);
}

int Pokedex::getBaseLevel(const std::string &id) const {
    return this->baseLevels.at(id);
}

int Pokedex::getCatchRate(const std::string &id) const {
    return this->catchRates.at(id);
}

int Pokedex::getDexNum(const std::string &id) const {
    return this->dexNums.at(id);
}
