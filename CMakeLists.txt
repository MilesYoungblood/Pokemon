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

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts")

#add_custom_command(
#        OUTPUT ${CMAKE_BINARY_DIR}/test.gcm
#        COMMAND ${CMAKE_CXX_COMPILER} -std=c++20 -fmodules-ts ${CMAKE_CURRENT_SOURCE_DIR}/src/test.cppm -o ${CMAKE_BINARY_DIR}/test.gcm
#        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/test.cppm
#)

#add_custom_target(ModuleCompilation DEPENDS ${CMAKE_BINARY_DIR}/test.gcm)

#add_library(my_lib test.ixx)
add_executable(PokemonBattle
        src/main.cpp
        src/Classes/Pokemon/Pokemon.h
        src/Classes/Pokemon/Pokemon.cpp
        src/Classes/Move/Move.h
        src/Classes/Move/Move.cpp
        src/Classes/Item/Item.cpp
        src/Classes/Item/Item.h
        src/Functions/ItemFunctions.h
        src/Data/MoveList.h
        src/Functions/TypeCalculations/TypeChart.h
        src/Functions/TypeCalculations/PhysicalTypes.h
        src/Functions/TypeCalculations/SpecialTypes.h
        src/Classes/Trainer/Trainer.cpp
        src/Classes/Trainer/Trainer.h
        src/Functions/GeneralFunctions.h
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
        src/Data/MoveList/WaterShuriken.h
        src/Data/MoveList/VoltTackle.h
        src/Data/MoveList/IceBeam.h
        src/Data/MoveList/Flamethrower.h
        src/Data/MoveList/AuraSphere.h
        src/Data/MoveList/FlashCannon.h
        src/Data/MoveList/Thunder.h
        src/Data/MoveList/FocusBlast.h
        src/Data/MoveList/IronTail.h
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
        src/Data/Pokedex.h
        src/Classes/Game/Game.cpp
        src/Classes/Game/Game.h
        src/Classes/Player/Player.cpp
        src/Classes/Player/Player.h
        src/Namespaces/Factory/MoveFactory.h
        src/Namespaces/Factory/ItemFactory.h
        src/Data/MoveList/DarkPulse.h
        src/Data/MoveList/Extrasensory.h
        src/Data/MoveList/AirSlash.h
        src/Classes/TextureManager/TextureManager.cpp
        src/Classes/TextureManager/TextureManager.h
        src/Namespaces/Camera/Camera.h
        src/Namespaces/Factory/PokemonFactory.h

)

#add_dependencies(PokemonBattle ModuleCompilation)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
target_link_libraries(${PROJECT_NAME} "C:/libs/SDL2_image-2.6.3/x86_64-w64-mingw32/bin/SDL2_image.dll")
target_link_libraries(${PROJECT_NAME} "C:/libs/SDL2_mixer-2.6.3/x86_64-w64-mingw32/bin/SDL2_mixer.dll")