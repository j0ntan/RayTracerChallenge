#ifndef PPM_H
#define PPM_H

#include <cstddef>
#include <string>

enum class MagicIdentifier { BINARY, ASCII };

class PPM {
public:
  PPM(size_t width = 100, size_t height = 100,
      MagicIdentifier ID = MagicIdentifier::BINARY);

  const size_t width;
  const size_t height;
  const std::string magic;
};

#endif
