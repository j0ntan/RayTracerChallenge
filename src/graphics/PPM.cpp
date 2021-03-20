#include <graphics/PPM.hpp>

const size_t PPM::max_color = 255;

PPM::PPM(size_t width, size_t height, MagicIdentifier ID)
    : width{width}, height{height}, magic{ID == MagicIdentifier::ASCII ? "P3"
                                                                       : "P6"} {
}
