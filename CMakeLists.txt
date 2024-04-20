cmake_minimum_required(VERSION 3.25)
project(Pokemon)

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
        src/Entity/Entity.cpp
        src/Entity/Entity.h
        src/Entity/Character/Character.cpp
        src/Entity/Character/Character.h
        src/Entity/Character/Pokemon/Pokemon.cpp
        src/Entity/Character/Pokemon/Pokemon.h
        src/Entity/Character/Trainer/Trainer.cpp
        src/Entity/Character/Trainer/Trainer.h
        src/Entity/Character/Trainer/Player/Player.cpp
        src/Entity/Character/Trainer/Player/Player.h
        src/Map/Map.cpp
        src/Map/Map.h
        src/Singleton/Singleton.h
        src/Singleton/Camera/Camera.cpp
        src/Singleton/Camera/Camera.h
        src/Singleton/EventHandler/EventHandler.cpp
        src/Singleton/EventHandler/EventHandler.h
        src/Singleton/Game/Game.cpp
        src/Singleton/Game/Game.h
        src/Singleton/GraphicsEngine/GraphicsEngine.cpp
        src/Singleton/GraphicsEngine/GraphicsEngine.h
        src/Singleton/ItemRegistry/ItemRegistry.cpp
        src/Singleton/ItemRegistry/ItemRegistry.h
        src/Singleton/KeyManager/KeyManager.cpp
        src/Singleton/KeyManager/KeyManager.h
        src/Singleton/Mixer/Mixer.cpp
        src/Singleton/Mixer/Mixer.h
        src/Singleton/Pokedex/Pokedex.cpp
        src/Singleton/Pokedex/Pokedex.h
        src/Singleton/TextureManager/TextureManager.cpp
        src/Singleton/TextureManager/TextureManager.h
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
        src/Move/Move.cpp
        src/Move/Move.h
        src/Move/AirSlash/AirSlash.cpp
        src/Move/AirSlash/AirSlash.h
        src/Move/AuraSphere/AuraSphere.cpp
        src/Move/AuraSphere/AuraSphere.h
        src/Move/DarkPulse/DarkPulse.cpp
        src/Move/DarkPulse/DarkPulse.h
        src/Move/DragonPulse/DragonPulse.cpp
        src/Move/DragonPulse/DragonPulse.h
        src/Move/Extrasensory/Extrasensory.cpp
        src/Move/Extrasensory/Extrasensory.h
        src/Move/Flamethrower/Flamethrower.cpp
        src/Move/Flamethrower/Flamethrower.h
        src/Move/FlashCannon/FlashCannon.cpp
        src/Move/FlashCannon/FlashCannon.h
        src/Move/FocusBlast/FocusBlast.cpp
        src/Move/FocusBlast/FocusBlast.h
        src/Move/HeadSmash/HeadSmash.cpp
        src/Move/HeadSmash/HeadSmash.h
        src/Move/HeatCrash/HeatCrash.cpp
        src/Move/HeatCrash/HeatCrash.h
        src/Move/IceBeam/IceBeam.cpp
        src/Move/IceBeam/IceBeam.h
        src/Move/IronTail/IronTail.cpp
        src/Move/IronTail/IronTail.h
        src/Move/QuickAttack/QuickAttack.cpp
        src/Move/QuickAttack/QuickAttack.h
        src/Move/SolarBeam/SolarBeam.cpp
        src/Move/SolarBeam/SolarBeam.h
        src/Move/Thunder/Thunder.cpp
        src/Move/Thunder/Thunder.h
        src/Move/VoltTackle/VoltTackle.cpp
        src/Move/VoltTackle/VoltTackle.h
)

set(POKE_BALLS
        src/Entity/Item/PokeBall/GreatBall/GreatBall.cpp
        src/Entity/Item/PokeBall/GreatBall/GreatBall.h
        src/Entity/Item/PokeBall/UltraBall/UltraBall.cpp
        src/Entity/Item/PokeBall/UltraBall/UltraBall.h
        src/Entity/Item/PokeBall/MasterBall/MasterBall.cpp
        src/Entity/Item/PokeBall/MasterBall/MasterBall.h
        src/Entity/Item/PokeBall/NetBall/NetBall.cpp
        src/Entity/Item/PokeBall/NetBall/NetBall.h
        src/Entity/Item/PokeBall/NestBall/NestBall.cpp
        src/Entity/Item/PokeBall/NestBall/NestBall.h
        src/Entity/Item/PokeBall/TimerBall/TimerBall.cpp
        src/Entity/Item/PokeBall/TimerBall/TimerBall.h
        src/Entity/Item/PokeBall/PremierBall/PremierBall.cpp
        src/Entity/Item/PokeBall/PremierBall/PremierBall.h
        src/Entity/Item/PokeBall/DuskBall/DuskBall.cpp
        src/Entity/Item/PokeBall/DuskBall/DuskBall.h
        src/Entity/Item/PokeBall/HealBall/HealBall.cpp
        src/Entity/Item/PokeBall/HealBall/HealBall.h
        src/Entity/Item/PokeBall/QuickBall/QuickBall.cpp
        src/Entity/Item/PokeBall/QuickBall/QuickBall.h
)

set(ITEMS
        src/Entity/Item/Item.cpp
        src/Entity/Item/Item.h
        src/Entity/Item/BattleItem/BattleItem.cpp
        src/Entity/Item/BattleItem/BattleItem.h
        src/Entity/Item/PokeBall/PokeBall.cpp
        src/Entity/Item/PokeBall/PokeBall.h
        ${POKE_BALLS}
        src/Entity/Item/RestoreItem/RestoreItem.cpp
        src/Entity/Item/RestoreItem/RestoreItem.h
        src/Entity/Item/StatusItem/StatusItem.cpp
        src/Entity/Item/StatusItem/StatusItem.h
)

set(GRAPHICS
        src/Graphic/Graphic.cpp
        src/Graphic/Graphic.h
        src/Graphic/Graphics.h
        src/Graphic/Texture/TimedVisual/TimedVisual.cpp
        src/Graphic/Texture/TimedVisual/TimedVisual.h
        src/Graphic/Rectangle/TextBox/TextBox.cpp
        src/Graphic/Rectangle/TextBox/TextBox.h
        src/Graphic/Texture/Texture.cpp
        src/Graphic/Texture/Texture.h
        src/Graphic/Rectangle/Rectangle.cpp
        src/Graphic/Rectangle/Rectangle.h
        src/Graphic/Rectangle/SelectionBox/SelectionBox.cpp
        src/Graphic/Rectangle/SelectionBox/SelectionBox.h
        src/Graphic/Rectangle/ResourceBar/ResourceBar.cpp
        src/Graphic/Rectangle/ResourceBar/ResourceBar.h
        src/Graphic/Rectangle/Button/Button.cpp
        src/Graphic/Rectangle/Button/Button.h
        src/Graphic/Rectangle/Panel/Panel.cpp
        src/Graphic/Rectangle/Panel/Panel.h
)

set(COMPONENTS
        src/Component/Intelligence/Intelligence.cpp
        src/Component/Intelligence/Intelligence.h
        src/Component/Position/Position.cpp
        src/Component/Position/Position.h
        src/Component/Resource/Resource.cpp
        src/Component/Resource/Resource.h
        src/Component/Sprite/Sprite.cpp
        src/Component/Sprite/Sprite.h
)

set(SCENES
        src/Singleton/Scene/Scene.h
        src/Singleton/Scene/Battle/Battle.cpp
        src/Singleton/Scene/Battle/Battle.h
        src/Singleton/Scene/Overworld/Overworld.cpp
        src/Singleton/Scene/Overworld/Overworld.h
        src/Singleton/Scene/TitleScreen/TitleScreen.cpp
        src/Singleton/Scene/TitleScreen/TitleScreen.h
        src/Singleton/Scene/Scene.cpp
)

add_executable(${PROJECT_NAME}
        ${SOURCES}
        ${MOVES}
        ${ITEMS}
        ${GRAPHICS}
        ${COMPONENTS}
        ${SCENES}
)

target_precompile_headers(${PROJECT_NAME} PRIVATE include/pch.h utility/Constants/constants.h)

target_link_libraries(${PROJECT_NAME} ${PROJECT_BINARY_DIR}/SDL2.dll)
target_link_libraries(${PROJECT_NAME} ${PROJECT_BINARY_DIR}/SDL2_image.dll)
target_link_libraries(${PROJECT_NAME} ${PROJECT_BINARY_DIR}/SDL2_mixer.dll)
target_link_libraries(${PROJECT_NAME} ${PROJECT_BINARY_DIR}/SDL2_ttf.dll)

target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/include/third_party/tinyxml2/tinyxml2.cpp)
