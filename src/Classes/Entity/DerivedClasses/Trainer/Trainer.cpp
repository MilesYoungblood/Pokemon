//
// Created by Miles Youngblood on 6/13/2022.
//

#include "../../../Singleton/DerivedClasses/Game/Game.h"
#include "Trainer.h"

Trainer::Trainer() {
    this->items[typeid(RestoreItem).hash_code()];
    this->items[typeid(StatusItem).hash_code()];
    this->items[typeid(PokeBall).hash_code()];
    this->items[typeid(BattleItem).hash_code()];
}

Trainer::Trainer(const char *name, int x, int y) : Entity(name, x, y) {
    this->items[typeid(RestoreItem).hash_code()];
    this->items[typeid(StatusItem).hash_code()];
    this->items[typeid(PokeBall).hash_code()];
    this->items[typeid(BattleItem).hash_code()];

    const std::string base("sprites/Hilbert/HilbertSpriteSheet");
    const std::string ext = ".png";

    //FIXME change these to not be Hilbert
    this->setAnimation(Direction::UP, base + "Up" + ext);
    this->setAnimation(Direction::DOWN, base + "Down" + ext);
    this->setAnimation(Direction::LEFT, base + "Left" + ext);
    this->setAnimation(Direction::RIGHT, base + "Right" + ext);
}

Trainer::Trainer(const char *name, int x, int y, Direction direction) : Trainer(name, x, y) {
    this->setDirection(direction);
}

Trainer::Trainer(const char *name, int x, int y, Direction direction, int vision) : Trainer(name, x, y, direction) {
    this->setVision(vision);
}

std::size_t Trainer::partySize() const {
    return this->party.size();
}

void Trainer::addPokemon(std::unique_ptr<Pokemon> toAdd) {
    if (this->party.size() == Trainer::MAX_POKEMON) {
        return;
    }

    this->party.push_back(std::move(toAdd));
}

void Trainer::removePokemon(long long int index) {
    try {
        // decrement the faint counter if the Pokémon we're removing is fainted
        if (this->party.at(index)->isFainted()) {
            --this->numFainted;
        }

        this->party.erase(this->party.begin() + index);
    }
    catch (const std::out_of_range &e) {
        throw std::out_of_range(std::string("Error removing Pokemon: ") + e.what() + '\n');
    }
}

void Trainer::swapPokemon(std::size_t a, std::size_t b) {
    try {
        std::unique_ptr<Pokemon> copy = std::move(this->party.at(a));
        this->party.at(a) = std::move(this->party.at(b));
        this->party.at(b) = std::move(copy);
    }
    catch (const std::out_of_range &e) {
        throw std::out_of_range(std::string("Error swapping Pokemon: ") + e.what() + '\n');
    }
}

void Trainer::clearParty() {
    this->party.clear();
}

void Trainer::incFaintCount() {
    ++this->numFainted;
}

void Trainer::decFaintCount() {
    --this->numFainted;
}

int Trainer::getFaintCount() const {
    return this->numFainted;
}

Pokemon &Trainer::operator[](std::size_t index) {
    try {
        return *this->party.at(index);
    }
    catch (const std::out_of_range &e) {
        throw std::out_of_range(std::string("Error accessing party: ") + e.what() + '\n');
    }
}

const Pokemon &Trainer::operator[](std::size_t index) const {
    try {
        return *this->party.at(index);
    }
    catch (const std::out_of_range &e) {
        throw std::out_of_range(std::string("Error accessing party: ") + e.what() + '\n');
    }
}

std::vector<std::unique_ptr<Pokemon>>::iterator Trainer::begin() {
    return this->party.begin();
}

std::vector<std::unique_ptr<Pokemon>>::iterator Trainer::end() {
    return this->party.end();
}

void Trainer::idle() {
    this->act();

    static int frameCounter = 0;    // makes this that spotted the player stand still for a set number of frames
    static bool haltMusic = true;
    static bool playMusic = true;

    // checks if the player is in LoS for any this
    if ((Player::getPlayer().getState() == Entity::State::IDLE or
         Player::getPlayer().getState() == Entity::State::FROZEN) and this->canFight() and
        (this->getState() == Entity::State::IDLE or this->getState() == Entity::State::FROZEN) and keepLooping[this] and
        this->hasVisionOf(&Player::getPlayer())) {
        if (haltMusic) {
            Player::getPlayer().setState(Entity::State::FROZEN);
            this->setState(Entity::State::FROZEN);
            momentum = false;

            Mix_HaltMusic();
            haltMusic = false;

            GraphicsEngine::getInstance().addGraphic<TimedVisual>(
                    "exclamation.png",
                    50 * (Game::getInstance().getFps() / 30) / 2,
                    SDL_Rect(
                            this->getScreenX(),
                            this->getScreenY() - Map::TILE_SIZE,
                            Map::TILE_SIZE,
                            Map::TILE_SIZE
                    )
            );
            Mixer::getInstance().playSound("spotted");
        }

        ++frameCounter;
        if (frameCounter < 50 * (Game::getInstance().getFps() / 30)) {
            return;
        }

        if (playMusic) {
            Mixer::getInstance().playMusic("GymBattle");
            playMusic = false;
        }

        if (not this->isNextTo(&Player::getPlayer())) {
            this->shift(this->getDirection(), Overworld::getInstance().getScrollSpeed());
            this->incWalkCounter(Overworld::getInstance().getScrollSpeed());

            if (this->getWalkCounter() % (Map::TILE_SIZE / 2) == 0) {
                this->updateAnimation();
            }

            if (this->getWalkCounter() % Map::TILE_SIZE == 0) {
                this->moveForward();
                this->resetWalkCounter();
            }
        }
        else {
            Player::getPlayer().face(this);

            Overworld::createTextBox(this->getDialogue());

            keepLooping[this] = false;

            frameCounter = 0;
            haltMusic = true;
            playMusic = true;
        }
    }
}

bool Trainer::canFight() const {
    return not this->party.empty();
}
