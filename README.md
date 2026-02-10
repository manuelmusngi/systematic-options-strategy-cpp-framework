#### Project overview

This C++ framework is a modular, extensible platform for designing, backtesting, and deploying systematic options strategies focused on SPX index options, but can be implemented to any instruments with Options contracts. It combines a clean runtime architecture—market‑data ingestion, pluggable strategy modules, order and position management, and risk controls—with a research‑driven approach so strategy logic, sizing, and hedging are informed by contemporary academic methods rather than ad‑hoc heuristics.

#### Academic grounding

📊 The framework is explicitly informed by four research themes common in recent arXiv/SSRN literature: 

- stochastic control for multi‑leg option portfolios 
- empirical modeling of option price and implied‑volatility surface dynamics,
- hedging and transaction‑cost aware sizing, 
- multi‑factor / rough volatility models for realistic tail and IV behavior. 

Concretely, entry/exit rules are framed as control objectives (state = spot, IV surface, time‑to‑expiry), pricers and simulators accept evolving IV surfaces learned or calibrated from historical option data, and risk/hedging modules implement rebalancing policies and cost penalties derived from empirical hedging studies.

#### Design implications

The architecture maps the four research themes into concrete modules:

- Control‑based strategy: entry/exit as stochastic control objectives (state = spot, IV surface, time‑to‑expiry).
- Pluggable pricers & IV simulators: empirical/ML or rough‑vol models can be swapped into the pricer interface for realistic option paths and Greeks.
- Empirical hedging & sizing: RiskManager encodes hedging cadence, transaction costs, and sizing rules from hedging studies.
- Data & calibration pipeline: ingest historical SPX/VIX/option chains, build IV surfaces, calibrate multi‑factor models or train empirical simulators for backtests.

#### Short technical summary

The codebase remains modular: 
- strategies implement a control interface
- market data supports both live (Yahoo polling or vendor feeds) and replay;
- pricers and IV simulators are swappable
- risk/position managers enforce empirically motivated constraints.

This structure lets researchers and engineers iterate on model choices (empirical surface, NN simulators, rough‑vol calibration) without rewriting core execution and bookkeeping logic.

🏗️ Project Architecture

OptionsTradingSystem/\
├── include/\
│ ├── primary/\
│ │ ├── MarketData.hpp\
│ │ ├── OrderManager.hpp\
│ │ ├── PositionManager.hpp\
│ │ ├── Strategy.hpp\
│ │ ├── RiskManager.hpp\
│ │ └── Logger.hpp\
│ ├── models/\
│ │ ├── Option.hpp\
│ │ └── Greeks.hpp\
│ └── utils/\
│ ├── ConfigLoader.hpp\
│ └── MathUtils.hpp\
├── src/\
│ ├── primary/\
│ │ ├── MarketData.cpp\
│ │ ├── OrderManager.cpp\
│ │ ├── PositionManager.cpp\
│ │ ├── Strategy.cpp\
│ │ ├── RiskManager.cpp\
│ │ └── Logger.cpp\
│ ├── models/\
│ │ ├── Option.cpp\
│ │ └── Greeks.cpp\
│ ├── utils/\
│ │ ├── ConfigLoader.cpp\
│ │ └── MathUtils.cpp\
│ └── main.cpp\
├── strategies/\
│ ├── IronCondorStrategy.hpp\
│ └── IronCondorStrategy.cpp\
└── config/\
└── strategy_config.json(Example)



📚 Research Reference Foundation

- [Stochastic Optimal Control of Iron Condor Portfolios for Profitability and Risk Management](https://arxiv.org/abs/2501.12397?utm_source=copilot.com)
- [Construction and Hedging of Equity Index Options Portfolios](https://arxiv.org/abs/2407.13908)
- [Empirical Models of the Time Evolution of SPX Option Prices](https://arxiv.org/abs/2506.17511)
- [Rough multifactor volatility for SPX and VIX options](https://arxiv.org/abs/2112.14310)
 
#### License
This project is licensed under the [MIT License](https://github.com/manuelmusngi/regime_switching_models/edit/main/LICENSE).



