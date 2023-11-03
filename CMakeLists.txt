cmake_minimum_required(VERSION 3.25)
project(PokemonBattle)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

set(SDL2_PATH "C:/libs/SDL2-2.28.4/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

include_directories("C:/libs/SDL2_image-2.6.3/x86_64-w64-mingw32/include/SDL2")
include_directories("C:/libs/SDL2_mixer-2.6.3/x86_64-w64-mingw32/include/SDL2")
include_directories("C:/libs/SDL2_ttf-2.20.2/x86_64-w64-mingw32/include/SDL2")
#include_directories("C:/libs/GSL-4.0.0/include/gsl")

#find_package(Microsoft.GSL CONFIG)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts")

#add_custom_command(
#        OUTPUT ${CMAKE_BINARY_DIR}/test.gcm
#        COMMAND ${CMAKE_CXX_COMPILER} -std=c++20 -fmodules-ts ${CMAKE_CURRENT_SOURCE_DIR}/src/test.cppm -o ${CMAKE_BINARY_DIR}/test.gcm
#        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/test.cppm
#)

#add_custom_target(ModuleCompilation DEPENDS ${CMAKE_BINARY_DIR}/test.gcm)

add_executable(PokemonBattle
        src/main.cpp
        src/Classes/Entity/DerivedClasses/Pokemon/Pokemon.h
        src/Classes/Entity/DerivedClasses/Pokemon/Pokemon.cpp
        src/Classes/Move/Move.h
        src/Classes/Move/Move.cpp
        src/Classes/Item/Item.cpp
        src/Classes/Item/Item.h
        src/Functions/ItemFunctions.h
        src/Classes/Entity/DerivedClasses/Trainer/Trainer.cpp
        src/Classes/Entity/DerivedClasses/Trainer/Trainer.h
        src/Functions/GeneralFunctions.h
        src/Classes/Item/DerivedClasses/RestoreItem/RestoreItem.cpp
        src/Classes/Item/DerivedClasses/RestoreItem/RestoreItem.h
        src/Classes/Item/DerivedClasses/StatusItem/StatusItem.cpp
        src/Classes/Item/DerivedClasses/StatusItem/StatusItem.h
        src/Classes/Item/DerivedClasses/Pokeball/Pokeball.h
        src/Classes/Item/DerivedClasses/Pokeball/Pokeball.cpp
        src/Classes/Item/DerivedClasses/BattleItem/BattleItem.cpp
        src/Classes/Item/DerivedClasses/BattleItem/BattleItem.h
        src/Classes/Move/DerivedClasses/WaterShuriken.h
        src/Classes/Move/DerivedClasses/VoltTackle.h
        src/Classes/Move/DerivedClasses/IceBeam.h
        src/Classes/Move/DerivedClasses/Flamethrower.h
        src/Classes/Move/DerivedClasses/AuraSphere.h
        src/Classes/Move/DerivedClasses/FlashCannon.h
        src/Classes/Move/DerivedClasses/Thunder.h
        src/Classes/Move/DerivedClasses/FocusBlast.h
        src/Classes/Move/DerivedClasses/IronTail.h
        src/Classes/Map/Map.cpp
        src/Classes/Map/Map.h
        src/Data/ItemList.h
        src/Classes/Battle/Battle.h
        src/Classes/Battle/Battle.cpp
        src/Data/ItemList/PokeBalls.h
        src/Data/ItemList/StatusItems.h
        src/Data/ItemList/RestoreItems.h
        src/Classes/Entity/Entity.cpp
        src/Classes/Entity/Entity.h
        src/Data/ItemList/BattleItems.h
        src/Classes/Game/Game.cpp
        src/Classes/Game/Game.h
        src/Classes/Entity/DerivedClasses/Trainer/DerivedClasses/Player/Player.cpp
        src/Classes/Entity/DerivedClasses/Trainer/DerivedClasses/Player/Player.h
        src/Namespaces/Factories/MoveFactory.h
        src/Namespaces/Factories/ItemFactory.h
        src/Classes/Move/DerivedClasses/DarkPulse.h
        src/Classes/Move/DerivedClasses/Extrasensory.h
        src/Classes/Move/DerivedClasses/AirSlash.h
        src/Namespaces/TextureManager/TextureManager.h
        src/Namespaces/Camera/Camera.h
        src/Namespaces/Factories/PokemonFactory.h
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Pokedex.h
        src/Classes/Move/MoveList.h
        src/Classes/Move/DerivedClasses/DragonPulse.h
        src/Classes/Move/DerivedClasses/QuickAttack.h
        src/Classes/Move/DerivedClasses/SolarBeam.h
        src/Classes/Game/OverworldFunctions.cpp
        src/Classes/Game/BattleFunctions.cpp
        src/Classes/Game/TitleScreenFunctions.cpp
        src/Namespaces/KeyManager/KeyManager.h
        src/Namespaces/Stopwatch.h
)

#add_dependencies(PokemonBattle ModuleCompilation)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
target_link_libraries(${PROJECT_NAME} "C:/libs/SDL2_image-2.6.3/x86_64-w64-mingw32/bin/SDL2_image.dll")
target_link_libraries(${PROJECT_NAME} "C:/libs/SDL2_mixer-2.6.3/x86_64-w64-mingw32/bin/SDL2_mixer.dll")
target_link_libraries(${PROJECT_NAME} "C:/libs/SDL2_ttf-2.20.2/x86_64-w64-mingw32/bin/SDL2_ttf.dll")