import argparse
import yaml
from pathlib import Path

from data_loader.loaders import MarketDataLoader
from portfolio.portfolio_builder import PortfolioBuilder
from scenarios.scenario_engine import ScenarioEngine
from stress_tests.stress_engine import StressEngine
from sensitivity.sensitivity_engine import SensitivityEngine
from risk.risk_engine import RiskEngine


def load_yaml(path: Path) -> dict:
    with open(path, "r") as f:
        return yaml.safe_load(f)


def main():
    parser = argparse.ArgumentParser(
        description="Natural Gas Portfolio Scenario & Stress Testing Platform"
    )
    parser.add_argument(
        "--portfolio-config",
        type=str,
        default="config/portfolio.yaml",
        help="Path to portfolio configuration YAML.",
    )
    parser.add_argument(
        "--scenarios-config",
        type=str,
        default="config/scenarios.yaml",
        help="Path to scenarios configuration YAML.",
    )
    parser.add_argument(
        "--stress-config",
        type=str,
        default="config/stress_tests.yaml",
        help="Path to stress tests configuration YAML.",
    )
    parser.add_argument(
        "--sensitivity-config",
        type=str,
        default="config/sensitivity.yaml",
        help="Path to sensitivity configuration YAML.",
    )
    parser.add_argument(
        "--data-paths-config",
        type=str,
        default="config/data_paths.yaml",
        help="Path to data paths configuration YAML.",
    )
    args = parser.parse_args()

    portfolio_cfg = load_yaml(Path(args.portfolio_config))
    scenarios_cfg = load_yaml(Path(args.scenarios_config))
    stress_cfg = load_yaml(Path(args.stress_config))
    sensitivity_cfg = load_yaml(Path(args.sensitivity_config))
    data_paths_cfg = load_yaml(Path(args.data_paths_config))

    # 1. Load market data
    md_loader = MarketDataLoader(data_paths_cfg)
    market_data = md_loader.load_all()

    # 2. Build portfolio
    portfolio_builder = PortfolioBuilder(portfolio_cfg)
    portfolio = portfolio_builder.build_portfolio()

    # 3. Scenario generation
    scenario_engine = ScenarioEngine(scenarios_cfg, market_data)
    scenarios = scenario_engine.generate_all()

    # 4. Stress testing
    stress_engine = StressEngine(stress_cfg, market_data)
    stressed_curves = stress_engine.apply_all()

    # 5. Sensitivity analysis
    sensitivity_engine = SensitivityEngine(sensitivity_cfg, market_data)
    sensitivities = sensitivity_engine.compute_all(portfolio)

    # 6. Risk metrics
    risk_engine = RiskEngine()
    scenario_results = risk_engine.evaluate_scenarios(portfolio, scenarios)
    stress_results = risk_engine.evaluate_stress_tests(portfolio, stressed_curves)
    risk_summary = risk_engine.summarize(
        scenario_results=scenario_results,
        stress_results=stress_results,
        sensitivities=sensitivities,
    )

    # 7. Output / reporting (placeholder)
    print("=== Risk Summary ===")
    for k, v in risk_summary.items():
        print(f"{k}: {v}")


if __name__ == "__main__":
    main()
