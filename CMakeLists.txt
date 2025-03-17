# CMakeList.txt : CMake project for Chessli, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Chessli")

# Add source to this project's executable.
add_executable (Chessli "src/Chessli.cpp" "src/Chessli.h" "src/pieces.h" "src/utils/utils.h" "src/utils/chess_constants.h" "src/utils/chess_constants.cpp" "src/utils/utils.cpp" "src/bitboard.h" "src/board.h" "src/board.cpp" "src/engine/engine.h" "src/engine/engine.cpp" "src/bitboard.cpp" "src/engine/magic.h" "src/game.h" "src/game.cpp"  "src/engine/magic.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Chessli PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
