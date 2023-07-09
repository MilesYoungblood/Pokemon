cmake_minimum_required(VERSION 3.22)
project(PokemonBattle)

set(CMAKE_CXX_STANDARD 14)

add_executable(PokemonBattle
        src/main.cpp
        src/Classes/Pokemon/Pokemon.h
        src/Classes/Pokemon/Pokemon.cpp
        src/Functions/GeneralFunctions.h
        src/Classes/Move/Move.h
        src/Classes/Move/Move.cpp
        src/Classes/Item/Item.cpp
        src/Classes/Item/Item.h
        src/Functions/AttackFunctions.h
        src/Functions/ItemFunctions.h
        src/Data/MoveList.h
        src/Functions/TypeCalculations/TypeChart.h
        src/Functions/TypeCalculations/PhysicalTypes.h
        src/Functions/TypeCalculations/SpecialTypes.h
        src/Classes/Trainer/Trainer.cpp
        src/Classes/Trainer/Trainer.h
        src/main.h
        src/Data/Data.cpp
        src/Data/Data.h
        src/Classes/Item/RestoreItem.cpp
        src/Classes/Item/RestoreItem.h
        src/Classes/Item/StatusItem.cpp
        src/Classes/Item/StatusItem.h
        src/Classes/Item/Pokeball.h
        src/Classes/Item/Pokeball.cpp
        src/Classes/Item/BattleItem.cpp
        src/Classes/Item/BattleItem.h
        src/Functions/CoreFunctions.h
        src/Data/MoveList/WaterShuriken.h
        src/Data/MoveList/VoltTackle.h
        src/Data/MoveList/IceBeam.h
        src/Data/MoveList/Flamethrower.h
        src/Data/MoveList/AuraSphere.h
        src/Data/MoveList/FlashCannon.h
        src/Data/MoveList/Thunder.h
        src/Data/MoveList/FocusBlast.h
        src/Data/MoveList/IronTail.h src/Classes/NPC/NPC.cpp src/Classes/NPC/NPC.h)
