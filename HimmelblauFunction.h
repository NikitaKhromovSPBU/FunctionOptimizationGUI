#pragma once
#include "GeneralFunction.h"

/**
 * Implements the Himmelblau function.
 * 
 * Himmelblau function's formula: \f[ f(x,y) = (x^2 + y - 11)^2 + (x + y^2 - 7)^2 \f].
 */
class HimmelblauFunction : public GeneralFunction
{
  public:
    HimmelblauFunction() : GeneralFunction(2, FunctionType::Himmelblau){};

    double evaluate(const std::vector<double> &parameters) const override;

    std::vector<double> get_gradient(const std::vector<double> &parameters) const override;

    ~HimmelblauFunction() override = default;
};
