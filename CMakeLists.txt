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
        src/Singletons/TextureManager/TextureManager.h
        src/Singletons/Camera/Camera.h
        src/Data/Pokemon/Pokedex.h
        src/Data/Moves/MoveList.h
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
        src/Classes/GameComponent/GameComponent.h
        src/Classes/GameObject/GameObject.h
        src/Classes/GameComponent/DerivedClasses/Position/PositionComponent.h
        src/Classes/GameComponent/DerivedClasses/Resource/ResourceComponent.h
        src/Classes/GameComponent/DerivedClasses/Sprite/SpriteComponent.h
        src/Classes/GameComponent/DerivedClasses/Components.h
        src/pch.h
        src/Singletons/TextureManager/TextureManager.cpp
)

set(POKEMON
        src/Data/Pokemon/Victini.cpp
        src/Data/Pokemon/Snivy.cpp
        src/Data/Pokemon/Servine.cpp
        src/Data/Pokemon/Serperior.cpp
        src/Data/Pokemon/Tepig.cpp
        src/Data/Pokemon/Pignite.cpp
        src/Data/Pokemon/Emboar.cpp
        src/Data/Pokemon/Oshawott.cpp
        src/Data/Pokemon/Dewott.cpp
        src/Data/Pokemon/Samurott.cpp
        src/Data/Pokemon/Patrat.cpp
        src/Data/Pokemon/Watchog.cpp
        src/Data/Pokemon/Lillipup.cpp
        src/Data/Pokemon/Herdier.cpp
        src/Data/Pokemon/Stoutland.cpp
        src/Data/Pokemon/Purrloin.cpp
        src/Data/Pokemon/Liepard.cpp
        src/Data/Pokemon/Pansage.cpp
        src/Data/Pokemon/Simisage.cpp
        src/Data/Pokemon/Pansear.cpp
        src/Data/Pokemon/Simisear.cpp
        src/Data/Pokemon/Panpour.cpp
        src/Data/Pokemon/Simipour.cpp
        src/Data/Pokemon/Munna.cpp
        src/Data/Pokemon/Musharna.cpp
        src/Data/Pokemon/Pidove.cpp
        src/Data/Pokemon/Tranquill.cpp
        src/Data/Pokemon/Unfezant.cpp
        src/Data/Pokemon/Blitzle.cpp
        src/Data/Pokemon/Zebstrika.cpp
        src/Data/Pokemon/Roggenrola.cpp
        src/Data/Pokemon/Boldore.cpp
        src/Data/Pokemon/Gigalith.cpp
        src/Data/Pokemon/Woobat.cpp
        src/Data/Pokemon/Swoobat.cpp
        src/Data/Pokemon/Drilbur.cpp
        src/Data/Pokemon/Excadrill.cpp
        src/Data/Pokemon/Audino.cpp
        src/Data/Pokemon/Timburr.cpp
        src/Data/Pokemon/Gurdurr.cpp
        src/Data/Pokemon/Conkeldurr.cpp
        src/Data/Pokemon/Tympole.cpp
        src/Data/Pokemon/Palpitoad.cpp
        src/Data/Pokemon/Seismitoad.cpp
        src/Data/Pokemon/Throh.cpp
        src/Data/Pokemon/Sawk.cpp
        src/Data/Pokemon/Sewaddle.cpp
        src/Data/Pokemon/Swadloon.cpp
        src/Data/Pokemon/Leavanny.cpp
        src/Data/Pokemon/Venipede.cpp
        src/Data/Pokemon/Whirlipede.cpp
        src/Data/Pokemon/Scolipede.cpp
        src/Data/Pokemon/Cottonee.cpp
        src/Data/Pokemon/Whimsicott.cpp
        src/Data/Pokemon/Petilil.cpp
        src/Data/Pokemon/Lilligant.cpp
        src/Data/Pokemon/Basculin.cpp
        src/Data/Pokemon/Sandile.cpp
        src/Data/Pokemon/Krokorok.cpp
        src/Data/Pokemon/Krookodile.cpp
        src/Data/Pokemon/Darumaka.cpp
        src/Data/Pokemon/Darmanitan.cpp
        src/Data/Pokemon/Maractus.cpp
        src/Data/Pokemon/Dwebble.cpp
        src/Data/Pokemon/Crustle.cpp
        src/Data/Pokemon/Scraggy.cpp
        src/Data/Pokemon/Scrafty.cpp
        src/Data/Pokemon/Sigilyph.cpp
        src/Data/Pokemon/Yamask.cpp
        src/Data/Pokemon/Cofagrigus.cpp
        src/Data/Pokemon/Tirtouga.cpp
        src/Data/Pokemon/Carracosta.cpp
        src/Data/Pokemon/Archen.cpp
        src/Data/Pokemon/Archeops.cpp
        src/Data/Pokemon/Trubbish.cpp
        src/Data/Pokemon/Garbodor.cpp
        src/Data/Pokemon/Zorua.cpp
        src/Data/Pokemon/Zoroark.cpp
        src/Data/Pokemon/Minccino.cpp
        src/Data/Pokemon/Cinccino.cpp
        src/Data/Pokemon/Gothita.cpp
        src/Data/Pokemon/Gothorita.cpp
        src/Data/Pokemon/Gothitelle.cpp
        src/Data/Pokemon/Solosis.cpp
        src/Data/Pokemon/Duosion.cpp
        src/Data/Pokemon/Reuniclus.cpp
        src/Data/Pokemon/Ducklett.cpp
        src/Data/Pokemon/Swanna.cpp
        src/Data/Pokemon/Vanillite.cpp
        src/Data/Pokemon/Vanillish.cpp
        src/Data/Pokemon/Vanilluxe.cpp
        src/Data/Pokemon/Deerling.cpp
        src/Data/Pokemon/Sawsbuck.cpp
        src/Data/Pokemon/Emolga.cpp
        src/Data/Pokemon/Karrablast.cpp
        src/Data/Pokemon/Escavalier.cpp
        src/Data/Pokemon/Foongus.cpp
        src/Data/Pokemon/Amoonguss.cpp
        src/Data/Pokemon/Frillish.cpp
        src/Data/Pokemon/Jellicent.cpp
        src/Data/Pokemon/Alomomola.cpp
        src/Data/Pokemon/Joltik.cpp
        src/Data/Pokemon/Galvantula.cpp
        src/Data/Pokemon/Ferroseed.cpp
        src/Data/Pokemon/Ferrothorn.cpp
        src/Data/Pokemon/Klink.cpp
        src/Data/Pokemon/Klang.cpp
        src/Data/Pokemon/Klinklang.cpp
        src/Data/Pokemon/Tynamo.cpp
        src/Data/Pokemon/Eelektrik.cpp
        src/Data/Pokemon/Eelektross.cpp
        src/Data/Pokemon/Elgyem.cpp
        src/Data/Pokemon/Beheeyem.cpp
        src/Data/Pokemon/Litwick.cpp
        src/Data/Pokemon/Lampent.cpp
        src/Data/Pokemon/Chandelure.cpp
        src/Data/Pokemon/Axew.cpp
        src/Data/Pokemon/Fraxure.cpp
        src/Data/Pokemon/Haxorus.cpp
        src/Data/Pokemon/Cubchoo.cpp
        src/Data/Pokemon/Beartic.cpp
        src/Data/Pokemon/Cryogonal.cpp
        src/Data/Pokemon/Shelmet.cpp
        src/Data/Pokemon/Accelgor.cpp
        src/Data/Pokemon/Stunfisk.cpp
        src/Data/Pokemon/Mienfoo.cpp
        src/Data/Pokemon/Mienshao.cpp
        src/Data/Pokemon/Druddigon.cpp
        src/Data/Pokemon/Golett.cpp
        src/Data/Pokemon/Golurk.cpp
        src/Data/Pokemon/Pawniard.cpp
        src/Data/Pokemon/Bisharp.cpp
        src/Data/Pokemon/Bouffalant.cpp
        src/Data/Pokemon/Rufflet.cpp
        src/Data/Pokemon/Braviary.cpp
        src/Data/Pokemon/Vullaby.cpp
        src/Data/Pokemon/Mandibuzz.cpp
        src/Data/Pokemon/Heatmor.cpp
        src/Data/Pokemon/Durant.cpp
        src/Data/Pokemon/Deino.cpp
        src/Data/Pokemon/Zweilous.cpp
        src/Data/Pokemon/Hydreigon.cpp
        src/Data/Pokemon/Larvesta.cpp
        src/Data/Pokemon/Volcarona.cpp
        src/Data/Pokemon/Cobalion.cpp
        src/Data/Pokemon/Terrakion.cpp
        src/Data/Pokemon/Virizion.cpp
        src/Data/Pokemon/Tornadus.cpp
        src/Data/Pokemon/Thundurus.cpp
        src/Data/Pokemon/Reshiram.cpp
        src/Data/Pokemon/Zekrom.cpp
        src/Data/Pokemon/Landorus.cpp
        src/Data/Pokemon/Kyurem.cpp
        src/Data/Pokemon/Keldeo.cpp
        src/Data/Pokemon/Meloetta.cpp
        src/Data/Pokemon/Genesect.cpp
)

set(MOVES

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
        src/Singletons/Camera/Camera.cpp
        src/Singletons/KeyManager/KeyManager.cpp
        src/Singletons/SoundPlayer/SoundPlayer.cpp
        src/Data/Moves/AirSlash.cpp
        src/Data/Moves/AuraSphere.cpp
)

add_executable(PokemonBattle ${SOURCES} ${POKEMON} ${MOVES} ${ITEMS})

target_precompile_headers(PokemonBattle PRIVATE src/pch.h)

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
