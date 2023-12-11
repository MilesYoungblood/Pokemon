cmake_minimum_required(VERSION 3.25)
project(PokemonBattle)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(C:/libs/GSL-4.0.0/include)

include_directories(C:/libs/tinyxml2-master)

include_directories(${PROJECT_SOURCE_DIR}/include/third_party/SDL2/SDL)
include_directories(${PROJECT_SOURCE_DIR}/include/third_party/SDL2/SDL_image)
include_directories(${PROJECT_SOURCE_DIR}/include/third_party/SDL2/SDL_mixer)
include_directories(${PROJECT_SOURCE_DIR}/include/third_party/SDL2/SDL_ttf)

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    message("64-bit system detected")
elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
    message("32-bit system detected")
else ()
    message(FATAL_ERROR "Unsupported architecture")
endif ()

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
        src/Classes/Map/Map.cpp
        src/Classes/Map/Map.h
        src/Classes/Item/ItemList.h
        src/Classes/Singleton/DerivedClasses/Battle/Battle.h
        src/Classes/Singleton/DerivedClasses/Battle/Battle.cpp
        src/Classes/Entity/Entity.cpp
        src/Classes/Entity/Entity.h
        src/Classes/Singleton/DerivedClasses/Game/Game.cpp
        src/Classes/Singleton/DerivedClasses/Game/Game.h
        src/Classes/Entity/DerivedClasses/Trainer/DerivedClasses/Player/Player.cpp
        src/Classes/Entity/DerivedClasses/Trainer/DerivedClasses/Player/Player.h
        src/Classes/Singleton/DerivedClasses/TextureManager/TextureManager.h
        src/Classes/Singleton/DerivedClasses/TextureManager/TextureManager.cpp
        src/Classes/Singleton/DerivedClasses/Camera/Camera.h
        src/Classes/Singleton/DerivedClasses/Camera/Camera.cpp
        src/Classes/Singleton/DerivedClasses/Game/OverworldFunctions.cpp
        src/Classes/Singleton/DerivedClasses/Game/BattleFunctions.cpp
        src/Classes/Singleton/DerivedClasses/Game/TitleScreenFunctions.cpp
        src/Classes/Singleton/DerivedClasses/KeyManager/KeyManager.h
        src/Classes/Singleton/DerivedClasses/KeyManager/KeyManager.cpp
        src/Classes/Stopwatch/Stopwatch.h
        src/Classes/Animation/Animation.h
        src/Classes/Animation/Animation.cpp
        src/Classes/Singleton/DerivedClasses/SoundPlayer/SoundPlayer.h
        src/Classes/Singleton/DerivedClasses/SoundPlayer/SoundPlayer.cpp
        src/Classes/GameObject/GameObject.cpp
        src/Classes/GameObject/GameObject.h
        src/Classes/GameComponent/GameComponent.h
        src/Classes/GameComponent/DerivedClasses/Position/PositionComponent.cpp
        src/Classes/GameComponent/DerivedClasses/Position/PositionComponent.h
        src/Classes/GameComponent/DerivedClasses/Resource/ResourceComponent.cpp
        src/Classes/GameComponent/DerivedClasses/Resource/ResourceComponent.h
        src/Classes/GameComponent/DerivedClasses/Sprite/SpriteComponent.cpp
        src/Classes/GameComponent/DerivedClasses/Sprite/SpriteComponent.h
        src/Classes/GameComponent/DerivedClasses/Components.h
        src/pch.h
        src/constants.h
        src/constants.cpp
        src/Classes/Ability/Ability.cpp
        src/Classes/Ability/Ability.h
        src/Classes/Graphic/DerivedClasses/TextBox/TextBox.cpp
        src/Classes/Graphic/DerivedClasses/TextBox/TextBox.h
        src/Classes/Singleton/DerivedClasses/GraphicsEngine/GraphicsEngine.cpp
        src/Classes/Singleton/DerivedClasses/GraphicsEngine/GraphicsEngine.h
        src/Classes/Graphic/Graphic.cpp
        src/Classes/Graphic/Graphic.h
        src/Classes/Singleton/Singleton.h
        src/Classes/Graphic/DerivedClasses/Button/Button.cpp
        src/Classes/Graphic/DerivedClasses/Button/Button.h
        src/Classes/Graphic/DerivedClasses/Graphics.h
        src/Classes/Graphic/DerivedClasses/Visual/Visual.cpp
        src/Classes/Graphic/DerivedClasses/Visual/Visual.h
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
        src/Classes/Move/DerivedClasses/AirSlash/AirSlash.cpp
        src/Classes/Move/DerivedClasses/AirSlash/AirSlash.h
        src/Classes/Move/DerivedClasses/AuraSphere/AuraSphere.cpp
        src/Classes/Move/DerivedClasses/AuraSphere/AuraSphere.h
        src/Classes/Move/DerivedClasses/DarkPulse/DarkPulse.cpp
        src/Classes/Move/DerivedClasses/DarkPulse/DarkPulse.h
        src/Classes/Move/DerivedClasses/DragonPulse/DragonPulse.cpp
        src/Classes/Move/DerivedClasses/DragonPulse/DragonPulse.h
        src/Classes/Move/DerivedClasses/Extrasensory/Extrasensory.cpp
        src/Classes/Move/DerivedClasses/Extrasensory/Extrasensory.h
        src/Classes/Move/DerivedClasses/Flamethrower/Flamethrower.cpp
        src/Classes/Move/DerivedClasses/Flamethrower/Flamethrower.h
        src/Classes/Move/DerivedClasses/FlashCannon/FlashCannon.cpp
        src/Classes/Move/DerivedClasses/FlashCannon/FlashCannon.h
        src/Classes/Move/DerivedClasses/FocusBlast/FocusBlast.cpp
        src/Classes/Move/DerivedClasses/FocusBlast/FocusBlast.h
        src/Classes/Move/DerivedClasses/IceBeam/IceBeam.cpp
        src/Classes/Move/DerivedClasses/IceBeam/IceBeam.h
        src/Classes/Move/DerivedClasses/IronTail/IronTail.cpp
        src/Classes/Move/DerivedClasses/IronTail/IronTail.h
        src/Classes/Move/DerivedClasses/QuickAttack/QuickAttack.cpp
        src/Classes/Move/DerivedClasses/QuickAttack/QuickAttack.h
        src/Classes/Move/DerivedClasses/SolarBeam/SolarBeam.cpp
        src/Classes/Move/DerivedClasses/SolarBeam/SolarBeam.h
        src/Classes/Move/DerivedClasses/Thunder/Thunder.cpp
        src/Classes/Move/DerivedClasses/Thunder/Thunder.h
        src/Classes/Move/DerivedClasses/VoltTackle/VoltTackle.cpp
        src/Classes/Move/DerivedClasses/VoltTackle/VoltTackle.h
)

set(ABILITIES
        src/Classes/Ability/DerivedClasses/Blaze/Blaze.cpp
        src/Classes/Ability/DerivedClasses/Blaze/Blaze.h
        src/Classes/Ability/DerivedClasses/Intimidate/Intimidate.cpp
        src/Classes/Ability/DerivedClasses/Intimidate/Intimidate.h
)

set(RESTORE_ITEMS
        src/Classes/Item/DerivedClasses/RestoreItem/DerivedClasses/Potion/Potion.cpp
        src/Classes/Item/DerivedClasses/RestoreItem/DerivedClasses/Potion/Potion.h
        src/Classes/Item/DerivedClasses/RestoreItem/DerivedClasses/SuperPotion/SuperPotion.cpp
        src/Classes/Item/DerivedClasses/RestoreItem/DerivedClasses/SuperPotion/SuperPotion.h
        src/Classes/Item/DerivedClasses/RestoreItem/DerivedClasses/HyperPotion/HyperPotion.cpp
        src/Classes/Item/DerivedClasses/RestoreItem/DerivedClasses/HyperPotion/HyperPotion.h
        src/Classes/Item/DerivedClasses/RestoreItem/DerivedClasses/MaxPotion/MaxPotion.cpp
        src/Classes/Item/DerivedClasses/RestoreItem/DerivedClasses/MaxPotion/MaxPotion.h
        src/Classes/Item/DerivedClasses/RestoreItem/DerivedClasses/Ether/Ether.cpp
        src/Classes/Item/DerivedClasses/RestoreItem/DerivedClasses/Ether/Ether.h
        src/Classes/Item/DerivedClasses/RestoreItem/DerivedClasses/MaxEther/MaxEther.cpp
        src/Classes/Item/DerivedClasses/RestoreItem/DerivedClasses/MaxEther/MaxEther.h
)

set(STATUS_ITEMS
        src/Classes/Item/DerivedClasses/StatusItem/DerivedClasses/Antidote/Antidote.cpp
        src/Classes/Item/DerivedClasses/StatusItem/DerivedClasses/Antidote/Antidote.h
        src/Classes/Item/DerivedClasses/StatusItem/DerivedClasses/Awakening/Awakening.cpp
        src/Classes/Item/DerivedClasses/StatusItem/DerivedClasses/Awakening/Awakening.h
        src/Classes/Item/DerivedClasses/StatusItem/DerivedClasses/BurnHeal/BurnHeal.cpp
        src/Classes/Item/DerivedClasses/StatusItem/DerivedClasses/BurnHeal/BurnHeal.h
        src/Classes/Item/DerivedClasses/StatusItem/DerivedClasses/IceHeal/IceHeal.cpp
        src/Classes/Item/DerivedClasses/StatusItem/DerivedClasses/IceHeal/IceHeal.h
        src/Classes/Item/DerivedClasses/StatusItem/DerivedClasses/ParalyzeHeal/ParalyzeHeal.cpp
        src/Classes/Item/DerivedClasses/StatusItem/DerivedClasses/ParalyzeHeal/ParalyzeHeal.h
)

set(POKE_BALLS
        src/Classes/Item/DerivedClasses/Pokeball/DerivedClasses/GreatBall/GreatBall.cpp
        src/Classes/Item/DerivedClasses/Pokeball/DerivedClasses/GreatBall/GreatBall.h
        src/Classes/Item/DerivedClasses/Pokeball/DerivedClasses/UltraBall/UltraBall.cpp
        src/Classes/Item/DerivedClasses/Pokeball/DerivedClasses/UltraBall/UltraBall.h
        src/Classes/Item/DerivedClasses/Pokeball/DerivedClasses/MasterBall/MasterBall.cpp
        src/Classes/Item/DerivedClasses/Pokeball/DerivedClasses/MasterBall/MasterBall.h
        src/Classes/Item/DerivedClasses/Pokeball/DerivedClasses/NetBall/NetBall.cpp
        src/Classes/Item/DerivedClasses/Pokeball/DerivedClasses/NetBall/NetBall.h
        src/Classes/Item/DerivedClasses/Pokeball/DerivedClasses/NestBall/NestBall.cpp
        src/Classes/Item/DerivedClasses/Pokeball/DerivedClasses/NestBall/NestBall.h
        src/Classes/Item/DerivedClasses/Pokeball/DerivedClasses/TimerBall/TimerBall.cpp
        src/Classes/Item/DerivedClasses/Pokeball/DerivedClasses/TimerBall/TimerBall.h
        src/Classes/Item/DerivedClasses/Pokeball/DerivedClasses/PremierBall/PremierBall.cpp
        src/Classes/Item/DerivedClasses/Pokeball/DerivedClasses/PremierBall/PremierBall.h
        src/Classes/Item/DerivedClasses/Pokeball/DerivedClasses/DuskBall/DuskBall.cpp
        src/Classes/Item/DerivedClasses/Pokeball/DerivedClasses/DuskBall/DuskBall.h
        src/Classes/Item/DerivedClasses/Pokeball/DerivedClasses/HealBall/HealBall.cpp
        src/Classes/Item/DerivedClasses/Pokeball/DerivedClasses/HealBall/HealBall.h
        src/Classes/Item/DerivedClasses/Pokeball/DerivedClasses/QuickBall/QuickBall.cpp
        src/Classes/Item/DerivedClasses/Pokeball/DerivedClasses/QuickBall/QuickBall.h
)

set(BATTLE_ITEMS
        src/Classes/Item/DerivedClasses/BattleItem/DerivedClasses/XAttack/XAttack.cpp
        src/Classes/Item/DerivedClasses/BattleItem/DerivedClasses/XAttack/XAttack.h
        src/Classes/Item/DerivedClasses/BattleItem/DerivedClasses/XDefense/XDefense.cpp
        src/Classes/Item/DerivedClasses/BattleItem/DerivedClasses/XDefense/XDefense.h
        src/Classes/Item/DerivedClasses/BattleItem/DerivedClasses/XSpAttack/XSpAttack.cpp
        src/Classes/Item/DerivedClasses/BattleItem/DerivedClasses/XSpAttack/XSpAttack.h
        src/Classes/Item/DerivedClasses/BattleItem/DerivedClasses/XSpDefense/XSpDefense.cpp
        src/Classes/Item/DerivedClasses/BattleItem/DerivedClasses/XSpDefense/XSpDefense.h
        src/Classes/Item/DerivedClasses/BattleItem/DerivedClasses/XSpeed/XSpeed.cpp
        src/Classes/Item/DerivedClasses/BattleItem/DerivedClasses/XSpeed/XSpeed.h
        src/Classes/Item/DerivedClasses/BattleItem/DerivedClasses/XAccuracy/XAccuracy.cpp
        src/Classes/Item/DerivedClasses/BattleItem/DerivedClasses/XAccuracy/XAccuracy.h
)

set(ITEMS
        ${RESTORE_ITEMS}
        ${STATUS_ITEMS}
        ${POKE_BALLS}
        ${BATTLE_ITEMS}
)

add_executable(PokemonBattle ${SOURCES} ${POKEMON} ${MOVES} ${ABILITIES} ${ITEMS})

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

target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/libs/third_party/SDL2/SDL2.dll)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/libs/third_party/SDL2/SDL2_image.dll)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/libs/third_party/SDL2/SDL2_mixer.dll)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/libs/third_party/SDL2/SDL2_ttf.dll)

target_link_libraries(${PROJECT_NAME} C:/libs/tinyxml2-master/tinyxml2.cpp)