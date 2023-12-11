#pragma once
#include "GeneralFunction.h"

/**
 * Implements the Rosenbrock function.
 *
 * Rosenbrock function's formula: \f[ f(x,y,z) = 100(y-x^2)^2 + (x-1)^2 + 100(z-y^2)^2 + (y-1)^2\f].
 */
class RosenbrockFunction :
    public GeneralFunction
{
public:
    RosenbrockFunction() : GeneralFunction(3, FunctionType::Rosenbrock) {};

    double evaluate(const std::vector<double>& parameters) const override;

    std::vector<double> get_gradient(const std::vector<double>& parameters) const override;

    ~RosenbrockFunction() override = default;
};

