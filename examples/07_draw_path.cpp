#include "podofo/base/PdfDefines.h"
#include "podofo/doc/PdfPage.h"
#include "podofo/doc/PdfPainter.h"
#include "podofo/podofo.h"

constexpr auto width = 100;
constexpr auto height = 100;

auto main() -> int {
  using namespace PoDoFo;
  PdfStreamedDocument doc{"draw_path.pdf"};
  auto page =
      doc.CreatePage(PdfPage::CreateStandardPageSize(PoDoFo::ePdfPageSize_A4));

  PdfPainter painter;
  painter.SetPage(page);

  // draw triangle
  painter.SetColor(0.0, 1.0, 1.0);
  auto x_start = page->GetPageSize().GetWidth() / 2;
  auto y_start = page->GetPageSize().GetHeight() - 20;
  painter.MoveTo(x_start, y_start);
  painter.LineTo(x_start - width / 2, y_start - height);
  painter.LineTo(x_start + width / 2, y_start - height);
  painter.ClosePath();
  painter.Fill();

  painter.FinishPage();
  doc.Close();
}