cmake_minimum_required(VERSION 3.25)
project(PokemonBattle)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("C:/libs/SDL2-2.28.4/x86_64-w64-mingw32/include/SDL2")
include_directories("C:/libs/SDL2_image-2.6.3/x86_64-w64-mingw32/include/SDL2")
include_directories("C:/libs/SDL2_mixer-2.6.3/x86_64-w64-mingw32/include/SDL2")
include_directories("C:/libs/SDL2_ttf-2.20.2/x86_64-w64-mingw32/include/SDL2")

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

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
        src/Classes/Item/DerivedClasses/BattleItem/BattleItem.cpp
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
        src/Data/Items/PokeBalls/PokeBalls.h
        src/Data/Items/StatusItems/StatusItems.h
        src/Data/Items/RestoreItems/RestoreItems.h
        src/Classes/Entity/Entity.cpp
        src/Classes/Entity/Entity.h
        src/Data/Items/BattleItems/BattleItems.h
        src/Classes/Game/Game.cpp
        src/Classes/Game/Game.h
        src/Classes/Entity/DerivedClasses/Trainer/DerivedClasses/Player/Player.cpp
        src/Classes/Entity/DerivedClasses/Trainer/DerivedClasses/Player/Player.h
        src/Classes/Move/DerivedClasses/DarkPulse.h
        src/Classes/Move/DerivedClasses/Extrasensory.h
        src/Classes/TextureManager/TextureManager.h
        src/Classes/TextureManager/TextureManager.cpp
        src/Classes/Camera/Camera.h
        src/Classes/Camera/Camera.cpp
        src/Data/Moves/MoveList.h
        src/Classes/Move/DerivedClasses/DragonPulse.h
        src/Classes/Move/DerivedClasses/QuickAttack.h
        src/Classes/Move/DerivedClasses/SolarBeam.h
        src/Classes/Game/OverworldFunctions.cpp
        src/Classes/Game/BattleFunctions.cpp
        src/Classes/Game/TitleScreenFunctions.cpp
        src/Classes/KeyManager/KeyManager.h
        src/Classes/KeyManager/KeyManager.cpp
        src/Classes/Stopwatch/Stopwatch.h
        src/Classes/Animation/Animation.h
        src/Classes/Animation/Animation.cpp
        src/Classes/SoundPlayer/SoundPlayer.h
        src/Classes/SoundPlayer/SoundPlayer.cpp
        #src/Classes/Move/Move.ixx
        #src/Functions/GeneralFunctions.ixx
        src/Classes/GameComponent/GameComponent.h
        src/Classes/GameObject/GameObject.h
        src/Classes/GameComponent/DerivedClasses/Position/PositionComponent.h
        src/Classes/GameComponent/DerivedClasses/Resource/ResourceComponent.h
        src/Classes/GameComponent/DerivedClasses/Sprite/SpriteComponent.h
        src/Classes/GameComponent/DerivedClasses/Components.h
        src/pch.h
        src/Classes/AutoThread/AutoThread.h
        src/Classes/Invoker/Invoker.h
)

set(POKEMON
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Victini/Victini.cpp
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Victini/Victini.h
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Snivy/Snivy.cpp
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Snivy/Snivy.h
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Servine/Servine.cpp
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Servine/Servine.h
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Serperior/Serperior.cpp
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Serperior/Serperior.h
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Tepig/Tepig.cpp
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Tepig/Tepig.h
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Pignite/Pignite.cpp
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Pignite/Pignite.h
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Emboar/Emboar.cpp
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Emboar/Emboar.h
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Oshawott/Oshawott.cpp
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Oshawott/Oshawott.h
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Dewott/Dewott.cpp
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Dewott/Dewott.h
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Samurott/Samurott.cpp
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Samurott/Samurott.h
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Patrat/Patrat.cpp
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Patrat/Patrat.h
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Watchog/Watchog.cpp
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Watchog/Watchog.h
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Lillipup/Lillipup.cpp
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Lillipup/Lillipup.h
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Herdier/Herdier.cpp
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Herdier/Herdier.h
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Stoutland/Stoutland.cpp
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Stoutland/Stoutland.h
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Purrloin/Purrloin.cpp
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Purrloin/Purrloin.h
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Liepard/Liepard.cpp
        src/Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Liepard/Liepard.h
)

set(MOVES
        src/Data/Moves/AirSlash.cpp
        src/Data/Moves/AuraSphere.cpp
)

set(RESTORE_ITEMS
        src/Data/Items/RestoreItems/Potion.cpp
        src/Data/Items/RestoreItems/SuperPotion.cpp
        src/Data/Items/RestoreItems/HyperPotion.cpp
        src/Data/Items/RestoreItems/MaxPotion.cpp
        src/Data/Items/RestoreItems/Ether.cpp
        src/Data/Items/RestoreItems/MaxEther.cpp
)

set(STATUS_ITEMS
        src/Data/Items/StatusItems/Antidote.cpp
        src/Data/Items/StatusItems/Awakening.cpp
        src/Data/Items/StatusItems/BurnHeal.cpp
        src/Data/Items/StatusItems/IceHeal.cpp
        src/Data/Items/StatusItems/ParalyzeHeal.cpp
)

set(POKE_BALLS
        src/Data/Items/PokeBalls/PokeBall.cpp
        src/Data/Items/PokeBalls/GreatBall.cpp
        src/Data/Items/PokeBalls/UltraBall.cpp
        src/Data/Items/PokeBalls/MasterBall.cpp
        src/Data/Items/PokeBalls/NetBall.cpp
        src/Data/Items/PokeBalls/NestBall.cpp
        src/Data/Items/PokeBalls/TimerBall.cpp
        src/Data/Items/PokeBalls/PremierBall.cpp
        src/Data/Items/PokeBalls/DuskBall.cpp
        src/Data/Items/PokeBalls/HealBall.cpp
        src/Data/Items/PokeBalls/QuickBall.cpp
)

set(BATTLE_ITEMS
        src/Data/Items/BattleItems/XAttack.cpp
        src/Data/Items/BattleItems/XDefense.cpp
        src/Data/Items/BattleItems/XSpAttack.cpp
        src/Data/Items/BattleItems/XSpDefense.cpp
        src/Data/Items/BattleItems/XSpeed.cpp
        src/Data/Items/BattleItems/XAccuracy.cpp
)

set(ITEMS
        ${RESTORE_ITEMS}
        ${STATUS_ITEMS}
        ${POKE_BALLS}
        ${BATTLE_ITEMS}
        src/Data/Items/Items.h
        src/constants.h
        src/constants.cpp
)

add_executable(PokemonBattle ${SOURCES} ${POKEMON} ${MOVES} ${ITEMS})

target_precompile_headers(PokemonBattle PRIVATE src/pch.h src/constants.h)

#target_compile_options(PokemonBattle PRIVATE -fmodules-ts)

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
