#pragma once

#include <memory>
#include <Math/Point.hpp>
#include <Math/Matrix.hpp>
#include <Graphics/Color.hpp>

/**
 * @brief Abstract base class for different types of patterns
 *
 */
struct Pattern
{
    /**
     * @brief The transform applied to the pattern
     *
     */
    Matrix<4> transform = {IDENTITY};

    /**
     * @brief Destroy the Pattern object
     *
     */
    virtual ~Pattern() = default;

    /**
     * @brief Clone and provide a pointer to a pattern
     *
     * This method is used to facilitate deep copying of pattern objects via
     * the Prototype design pattern.
     *
     * @return std::unique_ptr<Pattern> A unique pointer to the cloned pattern
     */
    virtual std::unique_ptr<Pattern> clone() const = 0;

    /**
     * @brief Calculate the pattern color at a given point in world space
     *
     * The concrete subclass must implement this method to provide the actual
     * pattern logic.
     *
     * @param point The point in world-space where the pattern color is queried
     * @return Color The pattern color at the specified point
     */
    virtual Color pattern_at(const Point &point) const = 0;
};
