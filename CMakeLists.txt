cmake_minimum_required(VERSION 3.20)

if(POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("RayCaster" LANGUAGES CXX C)

add_subdirectory("Source")

set_target_properties(
    "RayCaster"
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Bin"
)

file(COPY "Assets" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/Bin")

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries("RayCaster" PRIVATE nlohmann_json::nlohmann_json)

find_package(Stb REQUIRED)
target_include_directories("RayCaster" PRIVATE ${Stb_INCLUDE_DIR})

find_package(glm CONFIG REQUIRED)
target_link_libraries("RayCaster" PRIVATE glm::glm)

target_include_directories("RayCaster" PRIVATE "Source")
