//
// Created by miles on 5/25/2022.
//

#include "Items.h"

Items::Items() {
    quantity = 0;
    name = "No name";
}

Items::Items(const Items& copy) {
    this->quantity = copy.quantity;
    this->name = copy.name;
}

Items::Items(int quantityToSet, const std::string& nameToSet) {
    quantity = quantityToSet;
    name = nameToSet;
}

void Items::SetQuantity(int quantityToSet) {
    quantity = quantityToSet;
}
int Items::GetQuantity() const {
    return quantity;
}

void Items::SetName(const std::string &nameToSet) {
    name = nameToSet;
}
std::string Items::GetName() const {
    return name;
}

void Items::UseItem(Items& itemToUse) {
    itemToUse.SetQuantity(itemToUse.GetQuantity() - 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RestoreItems::RestoreItems() : Items() {
    amount = 0;
}
RestoreItems::RestoreItems(int quantityToSet, int restoreAmount, const std::string& nameToSet) : Items(quantityToSet, nameToSet){
    amount = restoreAmount;
}

void RestoreItems::ItemErrorMessage(const std::vector<RestoreItems>& items, int item) {
    std::cout << "You don't have any " << items.at(item - 1).GetName() << "s." << std::endl;
    sleep(2);
}

//void RestoreItems::Restore() {}

int RestoreItems::GetAmount() const {
    return amount;
}

//void RestoreItems::Restore() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HPItems::HPItems() : RestoreItems() {}
HPItems::HPItems(int quantity, int amount, const std::string& name) : RestoreItems(quantity, amount, name){}

/*void HPItems::Restore(Pokemon& pokemon, int restoreAmount) {
    pokemon.SetHP(pokemon.GetHP() + restoreAmount);
}
*/
PPItems::PPItems() : RestoreItems() {}
PPItems::PPItems(int quantity, int amount, const std::string& name) : RestoreItems(quantity, amount, name){}

/*void PPItems::Restore(Pokemon &pokemon, int restoreAmount, int moveToRestore) {
    pokemon.GetMoves().at(moveToRestore - 1).SetPP(pokemon.GetMoves().at(moveToRestore - 1).GetPP() + restoreAmount);
}*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

StatusItems::StatusItems() : Items() {}
StatusItems::StatusItems(const StatusItems &copy) = default;
StatusItems::StatusItems(int quantity, const std::string& name) : Items(quantity, name) {}

void StatusItems::ItemErrorMessage(const std::vector<StatusItems> &items, int item) {
    std::cout << "You don't have any " << items.at(item - 1).GetName() << "'s." << std::endl;
}

ParalysisItems::ParalysisItems() : StatusItems() {}
ParalysisItems::ParalysisItems(int quantity, const std::string& name) : StatusItems(quantity, name) {}

void ParalysisItems::Heal(StatusItems& ItemToUse, Pokemon& pokemonToCure) {
    if (pokemonToCure.GetStatus() == "paralyzed") {
        pokemonToCure.SetStatus("No status");
    }
}

BurnItems::BurnItems() : StatusItems() {}
BurnItems::BurnItems(int quantity, const std::string& name) : StatusItems(quantity, name) {}

void BurnItems::Heal(StatusItems& ItemToUse, Pokemon& pokemonToCure) {
    if (pokemonToCure.GetStatus() == "burn") {
        pokemonToCure.SetStatus("No status");
    }
}

FreezeItems::FreezeItems() : StatusItems() {}
FreezeItems::FreezeItems(int quantity, const std::string& name) : StatusItems(quantity, name) {}

void FreezeItems::Heal(StatusItems& ItemToUse, Pokemon& pokemonToCure) {
    if (pokemonToCure.GetStatus() == "frozen") {
        pokemonToCure.SetStatus("No status");
    }
}

PoisonItems::PoisonItems() : StatusItems() {}
PoisonItems::PoisonItems(int quantity, const std::string &name) : StatusItems(quantity, name) {}

void PoisonItems::Heal(StatusItems &itemToUse, Pokemon &pokemonToCure) {
    if (pokemonToCure.GetStatus() == "poisoned") {
        pokemonToCure.SetStatus("No status");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PokeBalls::PokeBalls() : Items() {}
PokeBalls::PokeBalls(int quantity, const std::string &name) : Items(quantity, name) {}