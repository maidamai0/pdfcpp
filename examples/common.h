#pragma once

#include <string>
#include <tuple>

#include "podofo/podofo.h"
#include "src/doc/PdfImage.h"
#include "src/doc/PdfPage.h"

#ifndef RESOURCE_PATH
#define RESOURCE_PATH "./"
#endif

constexpr auto a4_page_width = 595.0;
constexpr auto a4_page_height = 842.0;
constexpr auto font_arial_unicode_ms = "Arial Unicode MS";

[[maybe_unused]] inline auto full_path(std::string &&file_name) {
  return std::string(RESOURCE_PATH) + file_name;
}

[[maybe_unused]] inline auto
get_position_for_center(const PoDoFo::PdfImage &image) {
  const auto image_width = image.GetWidth();
  const auto image_height = image.GetHeight();

  const auto x = a4_page_width / 2 - image_width / 2;
  const auto y = a4_page_height / 2 - image_height / 2;

  return std::make_tuple(x, y);
}
