# CMakeList.txt : CMake project for platformer, include source and define
# project specific logic here.
#

# Add source to this project's executable.

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)


add_compile_definitions("SOURCE_ROOT=${CMAKE_SOURCE_DIR}")
#TODO::скопировать все ассеты в папку с exe средствами CMake

set(SRC "OwnGCF.h" "OwnGCF.cpp" "Control.h" "ParametrsGame.h" "Physics.h"  "Hero.h" "Hero.cpp" "ObjectMapa.h"  )

add_executable (platformer "platformer.cpp" ${SRC} "SetStruct.h" "usefull_sfml.cpp" "ComplexFields.h")

target_link_libraries(platformer PRIVATE sfml-graphics sfml-audio sfml-main sfml-network sfml-system sfml-window)
target_compile_features(platformer PRIVATE cxx_std_20)

#if(WIN32)
#    add_custom_command(
#        TARGET platformer
#        COMMENT "Copy OpenAL DLL"
#        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
#        VERBATIM)
#endif()