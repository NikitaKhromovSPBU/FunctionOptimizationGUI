#pragma once
#include "GeneralFunction.h"

/**
 * Implements the Levi function.
 * 
 * Levi function's formula: \f[ f(x,y) = \sin^2(3\pi x) + (x-1)^2 (1 + \sin^2(3\pi y)) + (y-1)^2(1 + \sin^2(2\pi y)) \f].
 */
class LeviFunction :
    public GeneralFunction
{
public:
    LeviFunction() : GeneralFunction(2, FunctionType::Levi) {};

    double evaluate(const std::vector<double>& parameters) const override;

    std::vector<double> get_gradient(const std::vector<double>& parameters) const override;

    ~LeviFunction() override = default;

protected:
    const static double PI;
};

