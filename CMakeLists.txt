cmake_minimum_required(VERSION 3.20)
project(OptionsTradingSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(ENABLE_TESTS "Build unit tests" ON)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

add_library(options_core
    src/core/MarketData.cpp
    src/core/YahooMarketData.cpp
    src/core/OrderManager.cpp
    src/core/PositionManager.cpp
    src/core/RiskManager.cpp
    src/core/Logger.cpp
    src/models/Option.cpp
    src/models/Greeks.cpp
    src/models/IVSurface.cpp
    src/pricing/Pricer_BlackScholes.cpp
    src/pricing/RoughVolModel.cpp
    src/strategies/IronCondorStrategy.cpp
)

target_include_directories(options_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/strategies
)

target_link_libraries(options_core PUBLIC CURL::libcurl nlohmann_json::nlohmann_json)

add_executable(options_app src/main.cpp)
target_link_libraries(options_app PRIVATE options_core)

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
