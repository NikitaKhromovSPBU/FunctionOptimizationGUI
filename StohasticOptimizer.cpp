#include "StohasticOptimizer.h"

std::uniform_real_distribution<> StohasticOptimizer::_U01(0.0, 1.0);

StohasticOptimizer::StohasticOptimizer(const GeneralFunction *f, std::vector<double> starting_point,
                                       RectangularArea area, const GeneralStopCriterion *sc, double p, double delta,
                                       double alpha)
    : GeneralOptimizer(f, std::move(starting_point), area, sc), _p(p), _delta(delta), _delta0(delta), _alpha(alpha),
    _current_function_value(_function->evaluate(*_trajectory.rbegin())), _generator()
{
    if (_p < 0 || _p > 1)
        throw std::domain_error("Probability p must be in range [0,1].");
    if (_alpha < 0)
        throw std::domain_error("Reduction rate alpha must be non-negative");

    std::random_device rd;
    _generator.seed(rd());
}

void StohasticOptimizer::step()
{
    const std::vector<double> &last_point = *_trajectory.rbegin();
    const size_t dimensions = last_point.size();
    std::vector<std::uniform_real_distribution<>> rect_distribution(dimensions);
    double a = _U01(_generator);
    std::vector<double> generated_point(dimensions);

    double new_function_value;

    if (a < _p)
    {
        for (size_t i{}; i < dimensions; ++i)
        {
            rect_distribution[i] = std::uniform_real_distribution<>(std::max(_area[2 * i], last_point[i] - _delta),
                                                                    std::min(_area[2 * i + 1], last_point[i] + _delta));
            generated_point[i] = rect_distribution[i](_generator);
        }

        new_function_value = _function->evaluate(generated_point);
        if (new_function_value < _current_function_value)
        {
            _current_function_value = new_function_value;
            _trajectory.push_back(std::move(generated_point));
            _delta = _delta0;
        }
        else
        {
            _trajectory.push_back(last_point);
            _delta *= _alpha;
        }
    }
    else
    {
        for (size_t i{}; i < dimensions; ++i)
        {
            rect_distribution[i] = std::uniform_real_distribution<>(_area[2 * i], _area[2 * i + 1]);
            generated_point[i] = rect_distribution[i](_generator);
        }

        new_function_value = _function->evaluate(generated_point);
        if (new_function_value < _current_function_value)
        {
            _current_function_value = new_function_value;
            _trajectory.push_back(std::move(generated_point));
            _delta = _delta0;
        }
        else
        {
            _trajectory.push_back(last_point);
            _delta *= _alpha;
        }
    }
}
