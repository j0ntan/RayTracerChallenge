#include <graphics/PPM.hpp>

PPM::PPM(size_t width, size_t height, MagicIdentifier ID)
    : width{width}, height{height}, magic{ID == MagicIdentifier::ASCII ? "P3"
                                                                       : "P6"} {
}
