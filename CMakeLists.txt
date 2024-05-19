# CMakeList.txt: проект CMake для OpenGL; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.10)

set(VCPKG_ROOT "vcpkg")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")

project ("OpenGL")

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (OpenGL)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/main.cpp" "src/snake.cpp")

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src
)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES} "include/snake.h" "src/snake.cpp" "src/main.cpp"  "src/menu.cpp" "include/Menu.h")

# this is heuristically generated, and may not be correct
target_link_libraries(OpenGL PRIVATE OpenGL::GL)  
target_link_libraries(OpenGL PRIVATE glfw)
target_link_libraries(OpenGL PRIVATE imgui::imgui)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OpenGL PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
