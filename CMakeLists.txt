cmake_minimum_required(VERSION 3.20)
project(OptionsTradingSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(ENABLE_TESTS "Build unit tests" ON)

add_library(options_core
    src/primary/MarketData.cpp
    src/primary/OrderManager.cpp
    src/primary/PositionManager.cpp
    src/primary/Strategy.cpp
    src/primary/RiskManager.cpp
    src/primary/Logger.cpp
    src/models/Option.cpp
    src/models/Greeks.cpp
    src/utils/ConfigLoader.cpp
    src/utils/MathUtils.cpp
    strategies/IronCondorStrategy.cpp
)

target_include_directories(options_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/strategies
)

add_executable(options_app src/main.cpp)
target_link_libraries(options_app PRIVATE options_core)

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
