cmake_minimum_required(VERSION 3.22)
project(PokemonBattle)

set(CMAKE_CXX_STANDARD 14)

add_executable(PokemonBattle main.cpp Pokemon.h Pokemon.cpp main.h Moves.h Moves.cpp Items.cpp Items.h AttackFunctions.h ItemFunctions.h MoveList.h TypeChart.h PhysicalTypes.h SpecialTypes.h Trainer.cpp Trainer.h GeneralFunctions.h)
