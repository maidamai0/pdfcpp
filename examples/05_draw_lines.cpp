#include "podofo/podofo.h"
#include <array>
#include <cmath>
#include <utility>

auto main() -> int {
  using namespace PoDoFo;
  PdfStreamedDocument doc{"draw_lines.pdf"};
  auto page = doc.CreatePage(PdfPage::CreateStandardPageSize(ePdfPageSize_A4));
  if (!page) {
    PODOFO_RAISE_ERROR(ePdfError_InvalidHandle);
  }

  PdfPainter painter;
  painter.SetPage(page);

  // line settiings
  constexpr auto line_length = 100.0;
  auto x_start = page->GetPageSize().GetWidth() / 2 - line_length / 2;
  auto y_start = page->GetPageSize().GetHeight() - 40;

  // draw lines in gray
  for (int i = 0; i < 10; ++i) {
    painter.SetStrokeWidth(i);
    painter.SetStrokingGray(1 / 10.0);
    painter.DrawLine(x_start, y_start, x_start + line_length, y_start);

    y_start -= 20;
  }
  y_start -= 20;

  // draw lines in rgb
  for (int i = 0; i < 10; ++i) {
    const auto sine = 0.5 + 0.5 * std::sin(i);
    const auto cosine = 0.5 + 0.5 * std::cos(i);
    painter.SetStrokeWidth(i);
    painter.SetStrokingColor(sine, cosine, 0.5 * (sine + cosine));
    painter.DrawLine(x_start, y_start, x_start + line_length, y_start);

    y_start -= 20;
  }
  y_start -= 20;

  // clang-format off
  const auto styles = std::array<std::pair<EPdfStrokeStyle, std::string>, 10>{{
        {ePdfStrokeStyle_Solid, {}},
        {ePdfStrokeStyle_Dash, {}},
        {ePdfStrokeStyle_DashDot, {}},
        {ePdfStrokeStyle_DashDotDot, {}},
        {ePdfStrokeStyle_Custom, {"[1 2 3] 4"}},
        {ePdfStrokeStyle_Custom, {"[3 4 5] 4"}},
        {ePdfStrokeStyle_Custom, {"[6 7 8] 4"}},
        {ePdfStrokeStyle_Custom, {"[8 2 4] 7"}},
        {ePdfStrokeStyle_Custom, {"[4 3 7] 4"}},
        {ePdfStrokeStyle_Custom, {"[3 6 9] 2"}}
    }};
  // clang-format on

  // draw lines of different style
  for (auto i = 0; i < 10; ++i) {
    const auto sine = 0.5 + 0.5 * std::sin(i);
    const auto cosine = 0.5 + 0.5 * std::cos(i);
    painter.SetStrokeWidth(i);
    const auto &style = styles[i];
    if (style.second.empty()) {
      painter.SetStrokeStyle(style.first);
    } else {
      painter.SetStrokeStyle(style.first, style.second.c_str());
    }
    painter.SetStrokingColor(sine, cosine, 0.5 * (sine + cosine));
    painter.DrawLine(x_start, y_start, x_start + line_length, y_start);

    y_start -= 20;
  }

  painter.FinishPage();
  doc.Close();
}