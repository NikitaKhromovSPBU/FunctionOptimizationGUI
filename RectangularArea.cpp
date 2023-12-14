#include "RectangularArea.h"

double& RectangularArea::operator[](size_t i)
{
    return _bounds[i];
}

const double RectangularArea::operator[](size_t i) const
{
    return _bounds[i];
}

bool RectangularArea::is_valid() const
{
    for (size_t i{}; i < _dimensions; ++i) {
        if (_bounds[2 * i] >= _bounds[2 * i + 1])
            return false;
    }
    return true;
}

bool RectangularArea::contains(const std::vector<double> &point) const
{
    if (point.size() != _dimensions)
        throw std::logic_error("Wrong number of dimensions.");

    for (size_t i{}; i < _dimensions; ++i)
    {
        if (point[i] < _bounds[2 * i] || point[i] > _bounds[2 * i + 1])
            return false;
    }
    return true;
}
