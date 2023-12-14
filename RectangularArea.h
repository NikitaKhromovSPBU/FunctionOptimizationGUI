#pragma once
#include <stdexcept>
#include <vector>

class RectangularArea
{
  private:
    /**
     * Space dimensionality.
     */
    size_t _dimensions;

    /**
     * Rectangular area boundary array.
     * 2i-th and 2i+1-st elements are the lower and the upper bounds for the i-th coordinate respectively.
     */
    std::vector<double> _bounds;

  public:
    /**
     * Creates an empty rectangular area with given number of dimensions.
     *
     * @param dimensions Number of dimensions of the RectangularArea object.
     */
    explicit RectangularArea(size_t dimensions) : _dimensions(dimensions), _bounds(std::vector<double>(2 * dimensions)){};

    /**
     * Creates a rectangular area with given bounds.
     *
     * \param dimensions Number of dimensions of the RectangularArea object.
     */
    RectangularArea(const std::vector<double> &bounds)
        : _dimensions(bounds.size() % 2 == 0 ? bounds.size() / 2 : throw std::logic_error("Odd number of bounds.")),
          _bounds(bounds){};

    void set_bounds(const std::vector<double> &bounds)
    {
        if (bounds.size() % 2 != 0)
            throw std::logic_error("Odd number of bounds.");

        _bounds = bounds;
        _dimensions = _bounds.size() / 2;
    };

    void set_bounds(std::vector<double>&& bounds)
    {
        if (bounds.size() % 2 != 0)
            throw std::logic_error("Odd number of bounds.");

        _bounds = std::move(bounds);
        _dimensions = _bounds.size() / 2;
    };

    std::vector<double> get_bounds() const
    {
        return _bounds;
    };

    size_t get_dimensions() const
    {
        return _dimensions;
    };

    /**
     * Get i-th bound.
     * For more info on bounds see _bounds.
     * 
     * \param i Number of the bound.
     * \return Reference to the bound value.
     */
    double& operator[](size_t i);
    double operator[](size_t i) const;

    /**
     * Checks whether the RectangularArea object has valid bounds.
     *
     * \return true if the bounds are valid, false otherwise.
     */
    bool is_valid() const;

    /**
     * Checks whether the given point lies within the RectangularArea object.
     *
     * \param point A vector of coordinates of the point in question. Must be of length equal to the number of
     * dimensions of the RectangularArea object.
     * \return true if the point lies within the rectangle, false otherwise.
     * \throw std::logic_error point size and number of dimensions are not equal.
     */
    bool contains(const std::vector<double> &point) const;
};
