cmake_minimum_required(VERSION 3.25)
project(PokemonBattle)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("C:/libs/SDL2-2.28.4/x86_64-w64-mingw32/include/SDL2")
include_directories("C:/libs/SDL2_image-2.6.3/x86_64-w64-mingw32/include/SDL2")
include_directories("C:/libs/SDL2_mixer-2.6.3/x86_64-w64-mingw32/include/SDL2")
include_directories("C:/libs/SDL2_ttf-2.20.2/x86_64-w64-mingw32/include/SDL2")

set(SOURCES
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
        src/Classes/Item/ItemList.h
        src/Classes/Battle/Battle.h
        src/Classes/Battle/Battle.cpp
        src/Classes/Item/DerivedClasses/Pokeball/DerivedClasses/PokeBalls.h
        src/Classes/Item/DerivedClasses/StatusItem/DerivedClasses/StatusItems.h
        src/Classes/Item/DerivedClasses/RestoreItem/DerivedClasses/RestoreItems.h
        src/Classes/Entity/Entity.cpp
        src/Classes/Entity/Entity.h
        src/Classes/Item/DerivedClasses/BattleItem/DerivedClasses/BattleItems.h
        src/Classes/Game/Game.cpp
        src/Classes/Game/Game.h
        src/Classes/Entity/DerivedClasses/Trainer/DerivedClasses/Player/Player.cpp
        src/Classes/Entity/DerivedClasses/Trainer/DerivedClasses/Player/Player.h
        src/Namespaces/Factories/MoveFactory.h
        src/Namespaces/Factories/ItemFactory.h
        src/Classes/Move/DerivedClasses/DarkPulse.h
        src/Classes/Move/DerivedClasses/Extrasensory.h
        src/Classes/Move/DerivedClasses/AirSlash.h
        src/Singletons/TextureManager/TextureManager.h
        src/Singletons/Camera/Camera.h
        src/Namespaces/Factories/PokemonFactory.h
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Pokedex.h
        src/Classes/Move/MoveList.h
        src/Classes/Move/DerivedClasses/DragonPulse.h
        src/Classes/Move/DerivedClasses/QuickAttack.h
        src/Classes/Move/DerivedClasses/SolarBeam.h
        src/Classes/Game/OverworldFunctions.cpp
        src/Classes/Game/BattleFunctions.cpp
        src/Classes/Game/TitleScreenFunctions.cpp
        src/Singletons/KeyManager/KeyManager.h
        src/Singletons/Stopwatch/Stopwatch.h
        src/Classes/Animation/Animation.h
        src/Singletons/SoundPlayer/SoundPlayer.h
        #src/Classes/Move/Move.ixx
        #src/Functions/GeneralFunctions.ixx
        src/pch.h
        src/Classes/GameComponent/GameComponent.h
        src/Classes/GameObject/GameObject.h
        src/Classes/GameComponent/DerivedClasses/Position/PositionComponent.h
        src/Classes/GameComponent/DerivedClasses/Resource/ResourceComponent.h
        src/Classes/GameComponent/DerivedClasses/Sprite/SpriteComponent.h
        src/Classes/GameComponent/DerivedClasses/Components.h
)

add_executable(PokemonBattle ${SOURCES})

target_precompile_headers(PokemonBattle PRIVATE src/pch.h)

target_compile_options(PokemonBattle PRIVATE -fmodules-ts)

#set_source_files_properties(src/Classes/Move/Move.ixx PROPERTIES
#        LANGUAGE CXX
#        LINKER_LANGUAGE CXX
#        COMPILE_FLAGS "-fmodules-ts"
#)

#set_source_files_properties(src/Functions/GeneralFunctions.ixx PROPERTIES
#        LANGUAGE CXX
#        LINKER_LANGUAGE CXX
#        COMPILE_FLAGS "-fmodules-ts"
#)

target_link_libraries(${PROJECT_NAME} "C:/libs/SDL2-2.28.4/x86_64-w64-mingw32/bin/SDL2.dll")
target_link_libraries(${PROJECT_NAME} "C:/libs/SDL2_image-2.6.3/x86_64-w64-mingw32/bin/SDL2_image.dll")
target_link_libraries(${PROJECT_NAME} "C:/libs/SDL2_mixer-2.6.3/x86_64-w64-mingw32/bin/SDL2_mixer.dll")
target_link_libraries(${PROJECT_NAME} "C:/libs/SDL2_ttf-2.20.2/x86_64-w64-mingw32/bin/SDL2_ttf.dll")