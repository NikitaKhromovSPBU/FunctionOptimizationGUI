#pragma once
#include <vector>

/**
 * Abstract class for different functions.
 */
class GeneralFunction
{
  public:

    /**
     * Types of implemented functions.
     */
    enum class FunctionType
    {
        ExpSin,
        Himmelblau,
        Levi,
        Rosenbrock,
    };

  private:
    /**
     * Dimensionality of the function.
     */
    size_t _dimensions;
    /**
     * Type of the function.
     */
    FunctionType _type;

  public:
    GeneralFunction(const GeneralFunction &f) = default;

    /**
     * Evaluates the function in the given point.
     *
     * \param parameters Coordinates in which the function is evaluated.
     * \return Value of the function on the given parameters.
     * \throw std::domain_error parameters size and number of dimensions are not equal.
     */
    virtual double evaluate(const std::vector<double> &parameters) const = 0;

    /**
     * Evaluates the gradient of the function.
     *
     * \param parameters Coordinates in which the gradient is evaluated
     * \return Gradient vector on the given parameters.
     * \throw std::domain_error parameters size and number of dimensions are not equal.
     */
    virtual std::vector<double> get_gradient(const std::vector<double> &parameters) const = 0;

    size_t get_dimensions() const
    {
        return _dimensions;
    };

    FunctionType get_type() const
    {
        return _type;
    }

    virtual ~GeneralFunction() = default;

  protected:
    GeneralFunction(size_t d, FunctionType t) : _dimensions(d), _type(t){};
};
