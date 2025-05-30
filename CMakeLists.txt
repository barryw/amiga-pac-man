cmake_minimum_required(VERSION 3.29)
include(CheckCCompilerFlag)

project(AmigaPacMan C)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR m68k)
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_C_FLAGS_DEBUG "-DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O2 -DRELEASE")

set(CMAKE_C_STANDARD 99)
check_c_compiler_flag("-D__AMIGAOS32__" AMIGAOS32_FLAG)
check_c_compiler_flag("-D__AMIGAOS13__" AMIGAOS13_FLAG)
if (AMIGAOS32_FLAG)
    include_directories(SYSTEM /Users/barry/amiga-cc/vbcc/targets/m68k-amigaos/include/)
endif ()
if (AMIGAOS13_FLAG)
    include_directories(SYSTEM /Users/barry/amiga-cc/vbcc/targets/m68k-kick13/include/)
endif ()


add_executable(th_DrawMaze test-harnesses/DrawMaze/DrawMaze.c)
add_executable(th_DrawStage test-harnesses/DrawStage/DrawStage.c)
add_executable(th_GelBob test-harnesses/GelBOB/GELBOB.c)
add_executable(th_GELVSprite test-harnesses/GELVSprite/GELVSprite.c)
add_executable(th_PacAndMaze test-harnesses/PacAndMaze/PacAndMaze.c)
add_executable(th_Pellets test-harnesses/Pellets/Pellets.c)
add_executable(th_Planes test-harnesses/Planes/Planes.c)
add_executable(th_PowerPelletTask test-harnesses/PowerPelletTask/powerpellettask.c)
add_executable(th_ScoreTask test-harnesses/ScoreTask/ScoreTask.c)
add_executable(th_ScreenTask test-harnesses/ScreenTask/screenTask.c)
add_executable(th_SpritePac test-harnesses/SpritePac/SpritePac.c)
add_executable(th_SpritesAndBob test-harnesses/SpritesAndBob/SpritesAndBOB.c)
add_executable(th_WSG test-harnesses/WSG/WSG.c)
add_executable(th_WSG2 test-harnesses/WSG2/WSG2.c)
add_executable(th_WSG3 test-harnesses/WSG3/WSG3.c)
add_executable(wsg-slice sound-work/wsg-slice.c)
add_executable(th_CoinDrop coindrop/coindrop.h
        coindrop/coindrop.c)
add_executable(th_IntroMusic intromusic/intromusic.h
        intromusic/intromusic.c)
add_executable(th_Intermission intermission/intermission.h
        intermission/intermission.c)
add_executable(th_SoundSystem sound_system/credit.h
        sound_system/sound_manager.c
        sound_system/sound_manager.h
        sound_system/sound_system.c
        sound_system/intermission.h
        sound_system/intromusic.h)
