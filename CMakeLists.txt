cmake_minimum_required(VERSION 3.25)
project(PokemonBattle)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include/third_party/SDL2/SDL)
include_directories(${PROJECT_SOURCE_DIR}/include/third_party/SDL2/SDL_image)
include_directories(${PROJECT_SOURCE_DIR}/include/third_party/SDL2/SDL_mixer)
include_directories(${PROJECT_SOURCE_DIR}/include/third_party/SDL2/SDL_ttf)

include_directories(C:/libs/GSL-4.0.0/include)

include_directories(${PROJECT_SOURCE_DIR}/include/third_party/tinyxml2)

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    message("64-bit system detected")
elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
    message("32-bit system detected")
else ()
    message(FATAL_ERROR "Unsupported architecture")
endif ()

set(SOURCES
        src/main.cpp
        src/Classes/Entity/DerivedClasses/Character/DerivedClasses/Pokemon/Pokemon.h
        src/Classes/Entity/DerivedClasses/Character/DerivedClasses/Pokemon/Pokemon.cpp
        src/Classes/Move/Move.h
        src/Classes/Move/Move.cpp
        src/Classes/Entity/DerivedClasses/Item/Item.cpp
        src/Classes/Entity/DerivedClasses/Item/Item.h
        src/Classes/Entity/DerivedClasses/Character/DerivedClasses/Trainer/Trainer.cpp
        src/Classes/Entity/DerivedClasses/Character/DerivedClasses/Trainer/Trainer.h
        src/Functions/GeneralFunctions.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/RestoreItem/RestoreItem.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/RestoreItem/RestoreItem.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/StatusItem/StatusItem.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/StatusItem/StatusItem.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/PokeBall/PokeBall.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/PokeBall/PokeBall.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/BattleItem/BattleItem.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/BattleItem/BattleItem.cpp
        src/Classes/Map/Map.cpp
        src/Classes/Map/Map.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/Items.h
        src/Classes/Entity/DerivedClasses/Character/Character.cpp
        src/Classes/Entity/DerivedClasses/Character/Character.h
        src/Classes/Singleton/DerivedClasses/Game/Game.cpp
        src/Classes/Singleton/DerivedClasses/Game/Game.h
        src/Classes/Entity/DerivedClasses/Character/DerivedClasses/Trainer/DerivedClasses/Player/Player.cpp
        src/Classes/Entity/DerivedClasses/Character/DerivedClasses/Trainer/DerivedClasses/Player/Player.h
        src/Classes/Singleton/DerivedClasses/TextureManager/TextureManager.h
        src/Classes/Singleton/DerivedClasses/TextureManager/TextureManager.cpp
        src/Classes/Singleton/DerivedClasses/Camera/Camera.h
        src/Classes/Singleton/DerivedClasses/Camera/Camera.cpp
        src/Classes/Singleton/DerivedClasses/KeyManager/KeyManager.h
        src/Classes/Singleton/DerivedClasses/KeyManager/KeyManager.cpp
        src/Classes/Stopwatch/Stopwatch.h
        src/Classes/Stopwatch/Stopwatch.cpp
        src/Classes/Singleton/DerivedClasses/Mixer/Mixer.h
        src/Classes/Singleton/DerivedClasses/Mixer/Mixer.cpp
        src/pch.h
        src/Constants/constants.h
        src/Constants/constants.cpp
        src/Classes/Singleton/DerivedClasses/GraphicsEngine/GraphicsEngine.cpp
        src/Classes/Singleton/DerivedClasses/GraphicsEngine/GraphicsEngine.h
        src/Classes/Singleton/Singleton.h
        src/Classes/Singleton/DerivedClasses/Pokedex/Pokedex.cpp
        src/Classes/Singleton/DerivedClasses/Pokedex/Pokedex.h
        src/Enums/Type/Type.cpp
        src/Enums/Type/Type.h
        src/Enums/Time/Time.h
        src/Enums/StatusCondition/StatusCondition.cpp
        src/Enums/StatusCondition/StatusCondition.h
        src/Enums/Direction/Direction.h
        src/Classes/Entity/Entity.cpp
        src/Classes/Entity/Entity.h
        src/Classes/ThreadPool/ThreadPool.cpp
        src/Classes/ThreadPool/ThreadPool.h
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
        src/Classes/Move/DerivedClasses/HeadSmash/HeadSmash.cpp
        src/Classes/Move/DerivedClasses/HeadSmash/HeadSmash.h
        src/Classes/Move/DerivedClasses/HeatCrash/HeatCrash.cpp
        src/Classes/Move/DerivedClasses/HeatCrash/HeatCrash.h
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

set(RESTORE_ITEMS
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/RestoreItem/DerivedClasses/Potion/Potion.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/RestoreItem/DerivedClasses/Potion/Potion.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/RestoreItem/DerivedClasses/SuperPotion/SuperPotion.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/RestoreItem/DerivedClasses/SuperPotion/SuperPotion.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/RestoreItem/DerivedClasses/HyperPotion/HyperPotion.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/RestoreItem/DerivedClasses/HyperPotion/HyperPotion.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/RestoreItem/DerivedClasses/MaxPotion/MaxPotion.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/RestoreItem/DerivedClasses/MaxPotion/MaxPotion.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/RestoreItem/DerivedClasses/Ether/Ether.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/RestoreItem/DerivedClasses/Ether/Ether.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/RestoreItem/DerivedClasses/MaxEther/MaxEther.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/RestoreItem/DerivedClasses/MaxEther/MaxEther.h
)

set(STATUS_ITEMS
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/StatusItem/DerivedClasses/Antidote/Antidote.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/StatusItem/DerivedClasses/Antidote/Antidote.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/StatusItem/DerivedClasses/Awakening/Awakening.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/StatusItem/DerivedClasses/Awakening/Awakening.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/StatusItem/DerivedClasses/BurnHeal/BurnHeal.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/StatusItem/DerivedClasses/BurnHeal/BurnHeal.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/StatusItem/DerivedClasses/IceHeal/IceHeal.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/StatusItem/DerivedClasses/IceHeal/IceHeal.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/StatusItem/DerivedClasses/ParalyzeHeal/ParalyzeHeal.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/StatusItem/DerivedClasses/ParalyzeHeal/ParalyzeHeal.h
)

set(POKE_BALLS
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/PokeBall/DerivedClasses/GreatBall/GreatBall.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/PokeBall/DerivedClasses/GreatBall/GreatBall.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/PokeBall/DerivedClasses/UltraBall/UltraBall.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/PokeBall/DerivedClasses/UltraBall/UltraBall.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/PokeBall/DerivedClasses/MasterBall/MasterBall.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/PokeBall/DerivedClasses/MasterBall/MasterBall.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/PokeBall/DerivedClasses/NetBall/NetBall.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/PokeBall/DerivedClasses/NetBall/NetBall.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/PokeBall/DerivedClasses/NestBall/NestBall.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/PokeBall/DerivedClasses/NestBall/NestBall.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/PokeBall/DerivedClasses/TimerBall/TimerBall.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/PokeBall/DerivedClasses/TimerBall/TimerBall.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/PokeBall/DerivedClasses/PremierBall/PremierBall.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/PokeBall/DerivedClasses/PremierBall/PremierBall.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/PokeBall/DerivedClasses/DuskBall/DuskBall.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/PokeBall/DerivedClasses/DuskBall/DuskBall.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/PokeBall/DerivedClasses/HealBall/HealBall.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/PokeBall/DerivedClasses/HealBall/HealBall.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/PokeBall/DerivedClasses/QuickBall/QuickBall.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/PokeBall/DerivedClasses/QuickBall/QuickBall.h
)

set(BATTLE_ITEMS
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/BattleItem/DerivedClasses/XAttack/XAttack.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/BattleItem/DerivedClasses/XAttack/XAttack.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/BattleItem/DerivedClasses/XDefense/XDefense.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/BattleItem/DerivedClasses/XDefense/XDefense.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/BattleItem/DerivedClasses/XSpAttack/XSpAttack.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/BattleItem/DerivedClasses/XSpAttack/XSpAttack.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/BattleItem/DerivedClasses/XSpDefense/XSpDefense.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/BattleItem/DerivedClasses/XSpDefense/XSpDefense.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/BattleItem/DerivedClasses/XSpeed/XSpeed.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/BattleItem/DerivedClasses/XSpeed/XSpeed.h
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/BattleItem/DerivedClasses/XAccuracy/XAccuracy.cpp
        src/Classes/Entity/DerivedClasses/Item/DerivedClasses/BattleItem/DerivedClasses/XAccuracy/XAccuracy.h
)

set(ITEMS
        ${RESTORE_ITEMS}
        ${STATUS_ITEMS}
        ${POKE_BALLS}
        ${BATTLE_ITEMS}
)

set(GRAPHICS
        src/Classes/Graphic/Graphic.cpp
        src/Classes/Graphic/Graphic.h
        src/Classes/Graphic/DerivedClasses/Graphics.h
        src/Classes/Graphic/DerivedClasses/Texture/DerivedClasses/Animation/Animation.h
        src/Classes/Graphic/DerivedClasses/Texture/DerivedClasses/Animation/Animation.cpp
        src/Classes/Graphic/DerivedClasses/Texture/DerivedClasses/TimedVisual/TimedVisual.cpp
        src/Classes/Graphic/DerivedClasses/Texture/DerivedClasses/TimedVisual/TimedVisual.h
        src/Classes/Graphic/DerivedClasses/Rectangle/DerivedClasses/TextBox/TextBox.cpp
        src/Classes/Graphic/DerivedClasses/Rectangle/DerivedClasses/TextBox/TextBox.h
        src/Classes/Graphic/DerivedClasses/Texture/Texture.cpp
        src/Classes/Graphic/DerivedClasses/Texture/Texture.h
        src/Classes/Graphic/DerivedClasses/Rectangle/Rectangle.cpp
        src/Classes/Graphic/DerivedClasses/Rectangle/Rectangle.h
        src/Classes/Graphic/DerivedClasses/Rectangle/DerivedClasses/SelectionBox/SelectionBox.cpp
        src/Classes/Graphic/DerivedClasses/Rectangle/DerivedClasses/SelectionBox/SelectionBox.h
        src/Classes/Graphic/DerivedClasses/Rectangle/DerivedClasses/ResourceBar/ResourceBar.cpp
        src/Classes/Graphic/DerivedClasses/Rectangle/DerivedClasses/ResourceBar/ResourceBar.h
        src/Classes/Graphic/DerivedClasses/Rectangle/DerivedClasses/Button/Button.cpp
        src/Classes/Graphic/DerivedClasses/Rectangle/DerivedClasses/Button/Button.h
        src/Classes/Graphic/DerivedClasses/Rectangle/DerivedClasses/Panel/Panel.cpp
        src/Classes/Graphic/DerivedClasses/Rectangle/DerivedClasses/Panel/Panel.h
)

set(SCENES
        src/Classes/Singleton/DerivedClasses/Scene/Scene.h
        src/Classes/Singleton/DerivedClasses/Scene/DerivedClasses/Scenes.h
        src/Classes/Singleton/DerivedClasses/Scene/DerivedClasses/Battle/Battle.cpp
        src/Classes/Singleton/DerivedClasses/Scene/DerivedClasses/Battle/Battle.h
        src/Classes/Singleton/DerivedClasses/Scene/DerivedClasses/Overworld/Overworld.cpp
        src/Classes/Singleton/DerivedClasses/Scene/DerivedClasses/Overworld/Overworld.h
        src/Classes/Singleton/DerivedClasses/Scene/DerivedClasses/TitleScreen/TitleScreen.cpp
        src/Classes/Singleton/DerivedClasses/Scene/DerivedClasses/TitleScreen/TitleScreen.h
        src/Classes/Singleton/DerivedClasses/Scene/Scene.cpp
)

add_executable(PokemonBattle
        ${SOURCES}
        ${MOVES}
        ${ITEMS}
        ${GRAPHICS}
        ${SCENES}
)

target_precompile_headers(PokemonBattle PRIVATE src/pch.h src/Constants/constants.h)

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

target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/include/third_party/tinyxml2/tinyxml2.cpp)
