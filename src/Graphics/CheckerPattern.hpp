#pragma once

#include <Graphics/Pattern.hpp>

/**
 * @brief Represents a 3D checker pattern with two colors (a and b)
 *
 */
struct CheckerPattern final : public Pattern
{
    /**
     * @brief The two colors that make up the pattern
     *
     */
    Color a;
    Color b;

    /**
     * @brief Construct a new Checker Pattern object with initialized colors
     *
     * @param a The first color
     * @param b The second color
     */
    CheckerPattern(const Color &a, const Color &b);

    /**
     * @brief Destroy the Checker Pattern object
     *
     */
    virtual ~CheckerPattern() = default;

    /**
     * @brief Clone and provide a pointer to checker pattern
     *
     * @return std::unique_ptr<Pattern> A unique pointer to the cloned pattern
     */
    std::unique_ptr<Pattern> clone() const override;

    /**
     * @brief Calculate the checkered color at a given point in world space
     *
     * @param point The point in world-space
     * @return Color The ring color at the specified point
     */
    Color pattern_at(const Point &point) const override;
};
