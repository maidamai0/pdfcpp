#include "podofo/base/PdfDefines.h"
#include "podofo/doc/PdfStreamedDocument.h"
#include "podofo/podofo.h"

#include <array>

constexpr auto rectangle_width = 200;
constexpr auto rectangle_height = 100;

auto main() -> int {
  using namespace PoDoFo;

  PdfStreamedDocument doc{"draw_rectangle.pdf"};
  auto *page =
      doc.CreatePage(PdfPage::CreateStandardPageSize(PoDoFo::ePdfPageSize_A4));
  if (!page) {
    PODOFO_RAISE_ERROR(ePdfError_InvalidHandle);
  }

  PdfPainter painter;
  painter.SetPage(page);

  auto y_start = page->GetPageSize().GetHeight() - 40 - rectangle_height;
  auto x_start = page->GetPageSize().GetWidth() / 2 - rectangle_width / 2;

  // clang-format off
  const auto styles = std::array<EPdfStrokeStyle, 4>{
      ePdfStrokeStyle_Dash,
      ePdfStrokeStyle_DashDot,
      ePdfStrokeStyle_DashDotDot,
      ePdfStrokeStyle_Solid
  };
  // clang-format on

  // draw without fill
  for (int i = 5; i < 9; ++i) {
    painter.SetStrokeWidth(i);
    painter.SetStrokeStyle(styles[i - 5]);
    painter.Rectangle(x_start, y_start, rectangle_width, rectangle_height);
    painter.Stroke();

    y_start -= (rectangle_height + 20);
  }

  // draw and fill
  painter.SetStrokeStyle(ePdfStrokeStyle_Solid);
  painter.SetStrokingColor(1.0, 0.0, 0.0);
  painter.SetColor(0.0, 0.0, 1.0);
  painter.Rectangle(x_start, y_start, rectangle_width, rectangle_height);
  painter.FillAndStroke();
  y_start -= (rectangle_height + 20);

  painter.SetStrokeStyle(ePdfStrokeStyle_Solid);
  painter.SetStrokingColor(0.5, 0.5, 0.5);
  painter.SetColor(0.5, 0.5, 0.5);
  painter.Rectangle(x_start, y_start, rectangle_width, rectangle_height);
  painter.FillAndStroke();
  y_start -= (rectangle_height + 20);

  painter.FinishPage();
  doc.Close();
}