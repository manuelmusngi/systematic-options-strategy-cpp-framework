#### systematic-options-strategy: Iron Condor in C++ framework

This C++ project provides a modular and extensible framework for developing, testing, and executing systematic options trading strategies, with an emphasis on SPX index options. Built for both backtesting and live trading, the architecture supports strategy plug-ins, real-time market data handling, risk management, and position tracking.

#### Project architecture
OptionsTradingSystem/\
├── include/\
│   ├── primary/\
│   │   ├── MarketData.hpp\
│   │   ├── OrderManager.hpp\
│   │   ├── PositionManager.hpp\
│   │   ├── Strategy.hpp\
│   │   ├── RiskManager.hpp\
│   │   └── Logger.hpp\
│   ├── models/\
│   │   ├── Option.hpp\
│   │   └── Greeks.hpp\
│   └── utils/\
│       ├── ConfigLoader.hpp\
│       └── MathUtils.hpp\
├── src/\
│   ├── primary/\
│   │   ├── MarketData.cpp\
│   │   ├── OrderManager.cpp\
│   │   ├── PositionManager.cpp\
│   │   ├── Strategy.cpp\
│   │   ├── RiskManager.cpp\
│   │   └── Logger.cpp\
│   ├── models/\
│   │   ├── Option.cpp\
│   │   └── Greeks.cpp\
│   ├── utils/\
│   │   ├── ConfigLoader.cpp\
│   │   └── MathUtils.cpp\
│   └── main.cpp\
├── strategies/\
│   ├── IronCondorStrategy.hpp\
│   └── IronCondorStrategy.cpp\
├── tests/\
│   ├── test_MarketData.cpp\
│   ├── test_Strategy.cpp\
│   └── ...
├── CMakeLists.txt\
└── config/\
    └── strategy_config.json

#### License
This project is licensed under the [MIT License](https://github.com/manuelmusngi/regime_switching_models/edit/main/LICENSE).
