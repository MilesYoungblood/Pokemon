cmake_minimum_required(VERSION 3.25)
project(PokemonBattle)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include/third_party/SDL2/SDL)
include_directories(${PROJECT_SOURCE_DIR}/include/third_party/SDL2/SDL_image)
include_directories(${PROJECT_SOURCE_DIR}/include/third_party/SDL2/SDL_mixer)
include_directories(${PROJECT_SOURCE_DIR}/include/third_party/SDL2/SDL_ttf)

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
        src/Classes/Entity/Entity.cpp
        src/Classes/Entity/Entity.h
        src/Classes/Entity/Character/Character.cpp
        src/Classes/Entity/Character/Character.h
        src/Classes/Entity/Character/Pokemon/Pokemon.cpp
        src/Classes/Entity/Character/Pokemon/Pokemon.h
        src/Classes/Entity/Character/Trainer/Trainer.cpp
        src/Classes/Entity/Character/Trainer/Trainer.h
        src/Classes/Entity/Character/Trainer/Player/Player.cpp
        src/Classes/Entity/Character/Trainer/Player/Player.h
        src/Classes/Map/Map.cpp
        src/Classes/Map/Map.h
        src/Classes/Singleton/Singleton.h
        src/Classes/Singleton/Camera/Camera.cpp
        src/Classes/Singleton/Camera/Camera.h
        src/Classes/Singleton/EventHandler/EventHandler.cpp
        src/Classes/Singleton/EventHandler/EventHandler.h
        src/Classes/Singleton/Game/Game.cpp
        src/Classes/Singleton/Game/Game.h
        src/Classes/Singleton/GraphicsEngine/GraphicsEngine.cpp
        src/Classes/Singleton/GraphicsEngine/GraphicsEngine.h
        src/Classes/Singleton/ItemRegistry/ItemRegistry.cpp
        src/Classes/Singleton/ItemRegistry/ItemRegistry.h
        src/Classes/Singleton/KeyManager/KeyManager.cpp
        src/Classes/Singleton/KeyManager/KeyManager.h
        src/Classes/Singleton/Mixer/Mixer.cpp
        src/Classes/Singleton/Mixer/Mixer.h
        src/Classes/Singleton/Pokedex/Pokedex.cpp
        src/Classes/Singleton/Pokedex/Pokedex.h
        src/Classes/Singleton/TextureManager/TextureManager.cpp
        src/Classes/Singleton/TextureManager/TextureManager.h
        include/pch.h
        src/Enums/Type/Type.cpp
        src/Enums/Type/Type.h
        src/Enums/StatusCondition/StatusCondition.cpp
        src/Enums/StatusCondition/StatusCondition.h
        src/Enums/Direction/Direction.h
        utility/Stopwatch/Stopwatch.cpp
        utility/Stopwatch/Stopwatch.h
        utility/Constants/constants.cpp
        utility/Constants/constants.h
        utility/ThreadPool/ThreadPool.cpp
        utility/ThreadPool/ThreadPool.h
        utility/Matrix/Matrix.h
        utility/Sorter/Sorter.h
        utility/Functions/GeneralFunctions.cpp
        utility/Functions/GeneralFunctions.h
)

set(MOVES
        src/Classes/Move/Move.cpp
        src/Classes/Move/Move.h
        src/Classes/Move/AirSlash/AirSlash.cpp
        src/Classes/Move/AirSlash/AirSlash.h
        src/Classes/Move/AuraSphere/AuraSphere.cpp
        src/Classes/Move/AuraSphere/AuraSphere.h
        src/Classes/Move/DarkPulse/DarkPulse.cpp
        src/Classes/Move/DarkPulse/DarkPulse.h
        src/Classes/Move/DragonPulse/DragonPulse.cpp
        src/Classes/Move/DragonPulse/DragonPulse.h
        src/Classes/Move/Extrasensory/Extrasensory.cpp
        src/Classes/Move/Extrasensory/Extrasensory.h
        src/Classes/Move/Flamethrower/Flamethrower.cpp
        src/Classes/Move/Flamethrower/Flamethrower.h
        src/Classes/Move/FlashCannon/FlashCannon.cpp
        src/Classes/Move/FlashCannon/FlashCannon.h
        src/Classes/Move/FocusBlast/FocusBlast.cpp
        src/Classes/Move/FocusBlast/FocusBlast.h
        src/Classes/Move/HeadSmash/HeadSmash.cpp
        src/Classes/Move/HeadSmash/HeadSmash.h
        src/Classes/Move/HeatCrash/HeatCrash.cpp
        src/Classes/Move/HeatCrash/HeatCrash.h
        src/Classes/Move/IceBeam/IceBeam.cpp
        src/Classes/Move/IceBeam/IceBeam.h
        src/Classes/Move/IronTail/IronTail.cpp
        src/Classes/Move/IronTail/IronTail.h
        src/Classes/Move/QuickAttack/QuickAttack.cpp
        src/Classes/Move/QuickAttack/QuickAttack.h
        src/Classes/Move/SolarBeam/SolarBeam.cpp
        src/Classes/Move/SolarBeam/SolarBeam.h
        src/Classes/Move/Thunder/Thunder.cpp
        src/Classes/Move/Thunder/Thunder.h
        src/Classes/Move/VoltTackle/VoltTackle.cpp
        src/Classes/Move/VoltTackle/VoltTackle.h
)

set(POKE_BALLS
        src/Classes/Entity/Item/PokeBall/GreatBall/GreatBall.cpp
        src/Classes/Entity/Item/PokeBall/GreatBall/GreatBall.h
        src/Classes/Entity/Item/PokeBall/UltraBall/UltraBall.cpp
        src/Classes/Entity/Item/PokeBall/UltraBall/UltraBall.h
        src/Classes/Entity/Item/PokeBall/MasterBall/MasterBall.cpp
        src/Classes/Entity/Item/PokeBall/MasterBall/MasterBall.h
        src/Classes/Entity/Item/PokeBall/NetBall/NetBall.cpp
        src/Classes/Entity/Item/PokeBall/NetBall/NetBall.h
        src/Classes/Entity/Item/PokeBall/NestBall/NestBall.cpp
        src/Classes/Entity/Item/PokeBall/NestBall/NestBall.h
        src/Classes/Entity/Item/PokeBall/TimerBall/TimerBall.cpp
        src/Classes/Entity/Item/PokeBall/TimerBall/TimerBall.h
        src/Classes/Entity/Item/PokeBall/PremierBall/PremierBall.cpp
        src/Classes/Entity/Item/PokeBall/PremierBall/PremierBall.h
        src/Classes/Entity/Item/PokeBall/DuskBall/DuskBall.cpp
        src/Classes/Entity/Item/PokeBall/DuskBall/DuskBall.h
        src/Classes/Entity/Item/PokeBall/HealBall/HealBall.cpp
        src/Classes/Entity/Item/PokeBall/HealBall/HealBall.h
        src/Classes/Entity/Item/PokeBall/QuickBall/QuickBall.cpp
        src/Classes/Entity/Item/PokeBall/QuickBall/QuickBall.h
)

set(ITEMS
        src/Classes/Entity/Item/Item.cpp
        src/Classes/Entity/Item/Item.h
        src/Classes/Entity/Item/BattleItem/BattleItem.cpp
        src/Classes/Entity/Item/BattleItem/BattleItem.h
        src/Classes/Entity/Item/PokeBall/PokeBall.cpp
        src/Classes/Entity/Item/PokeBall/PokeBall.h
        ${POKE_BALLS}
        src/Classes/Entity/Item/RestoreItem/RestoreItem.cpp
        src/Classes/Entity/Item/RestoreItem/RestoreItem.h
        src/Classes/Entity/Item/StatusItem/StatusItem.cpp
        src/Classes/Entity/Item/StatusItem/StatusItem.h
)

set(GRAPHICS
        src/Classes/Graphic/Graphic.cpp
        src/Classes/Graphic/Graphic.h
        src/Classes/Graphic/Graphics.h
        src/Classes/Graphic/Texture/TimedVisual/TimedVisual.cpp
        src/Classes/Graphic/Texture/TimedVisual/TimedVisual.h
        src/Classes/Graphic/Rectangle/TextBox/TextBox.cpp
        src/Classes/Graphic/Rectangle/TextBox/TextBox.h
        src/Classes/Graphic/Texture/Texture.cpp
        src/Classes/Graphic/Texture/Texture.h
        src/Classes/Graphic/Rectangle/Rectangle.cpp
        src/Classes/Graphic/Rectangle/Rectangle.h
        src/Classes/Graphic/Rectangle/SelectionBox/SelectionBox.cpp
        src/Classes/Graphic/Rectangle/SelectionBox/SelectionBox.h
        src/Classes/Graphic/Rectangle/ResourceBar/ResourceBar.cpp
        src/Classes/Graphic/Rectangle/ResourceBar/ResourceBar.h
        src/Classes/Graphic/Rectangle/Button/Button.cpp
        src/Classes/Graphic/Rectangle/Button/Button.h
        src/Classes/Graphic/Rectangle/Panel/Panel.cpp
        src/Classes/Graphic/Rectangle/Panel/Panel.h
)

set(COMPONENTS
        src/Classes/Component/Intelligence/Intelligence.cpp
        src/Classes/Component/Intelligence/Intelligence.h
        src/Classes/Component/Position/Position.cpp
        src/Classes/Component/Position/Position.h
        src/Classes/Component/Resource/Resource.cpp
        src/Classes/Component/Resource/Resource.h
        src/Classes/Component/Sprite/Sprite.cpp
        src/Classes/Component/Sprite/Sprite.h
)

set(SCENES
        src/Classes/Singleton/Scene/Scene.h
        src/Classes/Singleton/Scene/Battle/Battle.cpp
        src/Classes/Singleton/Scene/Battle/Battle.h
        src/Classes/Singleton/Scene/Overworld/Overworld.cpp
        src/Classes/Singleton/Scene/Overworld/Overworld.h
        src/Classes/Singleton/Scene/TitleScreen/TitleScreen.cpp
        src/Classes/Singleton/Scene/TitleScreen/TitleScreen.h
        src/Classes/Singleton/Scene/Scene.cpp
)

add_executable(PokemonBattle
        ${SOURCES}
        ${MOVES}
        ${ITEMS}
        ${GRAPHICS}
        ${COMPONENTS}
        ${SCENES}
)

target_precompile_headers(PokemonBattle PRIVATE include/pch.h utility/Constants/constants.h)

target_link_libraries(${PROJECT_NAME} ${PROJECT_BINARY_DIR}/SDL2.dll)
target_link_libraries(${PROJECT_NAME} ${PROJECT_BINARY_DIR}/SDL2_image.dll)
target_link_libraries(${PROJECT_NAME} ${PROJECT_BINARY_DIR}/SDL2_mixer.dll)
target_link_libraries(${PROJECT_NAME} ${PROJECT_BINARY_DIR}/SDL2_ttf.dll)

target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/include/third_party/tinyxml2/tinyxml2.cpp)
