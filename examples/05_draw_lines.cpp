#include "podofo/podofo.h"

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
  auto y_start = page->GetPageSize().GetHeight() - 20;

  // draw lines
  for (int i = 0; i < 10; ++i) {
    painter.SetStrokeWidth(i);
    painter.SetStrokingGray(1 / 10.0);
    painter.DrawLine(x_start, y_start, x_start + line_length, y_start);

    y_start -= 20;
  }

  painter.FinishPage();
  doc.Close();
}