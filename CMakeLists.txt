# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.23)

project(ServerCrud VERSION 1.0.0
	DESCRIPTION "Simple Rest server implementation"
	LANGUAGES CXX C)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT
	"$<$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>:$<$<CONFIG:Debug>:ProgramDatabase>>")
endif()

add_executable(ServerCrud)
set_property(TARGET ServerCrud PROPERTY CXX_STANDARD 20)

add_subdirectory(include)
add_subdirectory(src)
