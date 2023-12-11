#include "FletcherReevesOptimizer.h"

const double FletcherReevesOptimizer::golden_ratio{1.618033988749894848};

FletcherReevesOptimizer::FletcherReevesOptimizer(const GeneralFunction *f, std::vector<double> starting_point,
                                                 RectangularArea area, const GeneralStopCriterion *sc)
    : GeneralOptimizer(f, std::move(starting_point), area, sc), _grad_new(f->get_gradient(starting_point)),
      _p(_grad_new)
{
    for (auto &x : _p)
    {
        x = -x;
    }
}

double find_interception(const std::vector<double> &v, const std::vector<double> &start_point,
                         const RectangularArea &rect)
{
    if (v.size() != rect.get_dimensions())
        throw std::exception("Number of dimensions of vector and rectangle are not equal.");

    double res = std::min(abs((start_point[0] - rect[0]) / v[0]), abs((start_point[0] - rect[1]) / v[0]));
    for (size_t i{1}; i < v.size(); ++i)
    {
        res = std::min(abs((start_point[i] - rect[2 * i]) / v[i]), res);
        res = std::min(abs((start_point[i] - rect[2 * i + 1]) / v[i]), res);
    }
    return res;
}

void FletcherReevesOptimizer::step()
{
    const double precision{1e-8};
    const size_t max_iterations{ 100 };

    const std::vector<double> &starting_point{*_trajectory.rbegin()};
    const size_t dimensions{starting_point.size()};
    std::vector<double> p_moved(dimensions);
   /* for (size_t i{}; i < dimensions; ++i)
    {
        p_moved[i] = starting_point[i] + _p[i];
    }*/

    double max_alpha = find_interception(_p, starting_point, _area);
    //double max_alpha = find_interception(p_moved, starting_point, _area);

    double left_alpha{}, right_alpha{max_alpha},
        left_alpha_temp{right_alpha - (right_alpha - left_alpha) / golden_ratio},
        right_alpha_temp{left_alpha + (right_alpha - left_alpha) / golden_ratio};
    double left_function_value{}, right_function_value{};
    bool left_known;
    std::vector<double> short_vec_temp(dimensions), long_vec_temp(dimensions);

    for (size_t i{}; i < dimensions; ++i)
    {
        short_vec_temp[i] = starting_point[i] + left_alpha_temp * _p[i];
        long_vec_temp[i] = starting_point[i] + right_alpha_temp * _p[i];
    }

    left_function_value = _function->evaluate(short_vec_temp);
    right_function_value = _function->evaluate(long_vec_temp);
    if (left_function_value < right_function_value)
    {
        right_alpha = right_alpha_temp;
        right_function_value = left_function_value;
        left_known = false;
    }
    else
    {
        left_alpha = left_alpha_temp;
        left_function_value = right_function_value;
        left_known = true;
    }

    for (size_t i{}; right_alpha - left_alpha > precision && i < max_iterations; ++i)
    {
        left_alpha_temp = right_alpha - (right_alpha - left_alpha) / golden_ratio;
        right_alpha_temp = left_alpha + (right_alpha - left_alpha) / golden_ratio;

        if (left_known)
        {
            for (size_t i{}; i < dimensions; ++i)
            {
                long_vec_temp[i] = starting_point[i] + right_alpha_temp * _p[i];
            }
            right_function_value = _function->evaluate(long_vec_temp);
        }
        else
        {

            for (size_t i{}; i < dimensions; ++i)
            {
                short_vec_temp[i] = starting_point[i] + left_alpha_temp * _p[i];
            }
            left_function_value = _function->evaluate(short_vec_temp);
        }

        if (left_function_value < right_function_value)
        {
            right_alpha = right_alpha_temp;
            right_function_value = left_function_value;
            left_known = false;
        }
        else
        {
            left_alpha = left_alpha_temp;
            left_function_value = right_function_value;
            left_known = true;
        }
    }

    _alpha = (left_alpha + right_alpha) / 2;

    std::vector<double> new_point(dimensions);

    for (size_t i{}; i < dimensions; ++i)
    {
        new_point[i] = starting_point[i] + _alpha * _p[i];
    }

    if (_function->evaluate(new_point) < _function->evaluate(starting_point))
        _trajectory.push_back(new_point);
    else
        _trajectory.push_back(starting_point);

    _grad_prev = _grad_new;
    _grad_new = _function->get_gradient(new_point);

    double numerator{}, denominator{};
    for (size_t i{}; i < dimensions; ++i)
    {
        numerator += _grad_new[i] * _grad_new[i];
        denominator += _grad_prev[i] * _grad_prev[i];
    }

    _beta = numerator / denominator;

    for (size_t i{}; i < dimensions; ++i)
    {
        _p[i] = -_grad_new[i] + _beta * _p[i];
    }
}
