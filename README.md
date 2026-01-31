Project overview
This C++ framework is a modular, extensible platform for designing, backtesting, and deploying systematic options strategies focused on SPX index options. It combines a clean runtime architecture—market‑data ingestion, pluggable strategy modules, order and position management, and risk controls—with a research‑driven approach so strategy logic, sizing, and hedging are informed by contemporary academic methods rather than ad‑hoc heuristics.

Academic grounding
The framework is explicitly informed by four research themes common in recent arXiv/SSRN literature: stochastic control for multi‑leg option portfolios, empirical modeling of option price and implied‑volatility surface dynamics, hedging and transaction‑cost aware sizing, and multi‑factor / rough volatility models for realistic tail and IV behavior. Concretely, entry/exit rules are framed as control objectives (state = spot, IV surface, time‑to‑expiry), pricers and simulators accept evolving IV surfaces learned or calibrated from historical option data, and risk/hedging modules implement rebalancing policies and cost penalties derived from empirical hedging studies.

Design implications
Strategy as control — Strategies expose objective functions and stopping rules so IronCondorStrategy (and others) can optimize entry/exit under explicit reward/cost criteria rather than fixed thresholds.

Pluggable pricers and surface simulators — Replace single‑model Black‑Scholes with a pricer interface that accepts an IV surface or a calibrated stochastic volatility model; this enables backtests to use empirical or rough‑vol dynamics for realistic P&L and Greeks.

Data and calibration pipeline — A dedicated data module ingests historical SPX, VIX, and option chains, builds IV surfaces, and produces scenario generators used by the backtester and risk stress tests.

Risk and hedging policies — RiskManager codifies hedging cadence, position sizing, and transaction‑cost penalties so the system can evaluate tradeoffs between premium capture and hedging cost as shown in hedging literature.

Validation and reproducibility — Unit tests and backtest suites validate strategy performance across simulated IV evolutions and empirical replay, enabling reproducible comparisons between heuristic rules and control‑based policies.

Short technical summary
The codebase remains modular: strategies implement a control interface; market data supports both live (Yahoo polling or vendor feeds) and replay; pricers and IV simulators are swappable; and risk/position managers enforce empirically motivated constraints. This structure lets researchers and engineers iterate on model choices (empirical surface, NN simulators, rough‑vol calibration) without rewriting core execution and bookkeeping logic.

I can map each cited research theme to concrete C++ modules and API signatures so you can implement the control objective, IV surface pricer, and hedging policies.

#### License
This project is licensed under the [MIT License](https://github.com/manuelmusngi/regime_switching_models/edit/main/LICENSE).
