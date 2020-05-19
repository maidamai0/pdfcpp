#include "podofo/podofo.h"

#include <iostream>

auto main(int argc, char **argv) -> int {
  PoDoFo::PdfStreamedDocument doc{"draw_text.pdf"};
  PoDoFo::PdfPainter painter;

  // page
  const auto page = doc.CreatePage(
      PoDoFo::PdfPage::CreateStandardPageSize(PoDoFo::ePdfPageSize_A4));
  if (!page) {
    PODOFO_RAISE_ERROR(PoDoFo::ePdfError_InvalidHandle);
  }
  painter.SetPage(page);

  // font
  const auto font = doc.CreateFont("Arial");
  if (!font) {
    PODOFO_RAISE_ERROR(PoDoFo::ePdfError_InvalidHandle);
  }
  font->SetFontSize(18.0);
  painter.SetFont(font);
  painter.SetColor(0.8, 0.4, 0.2);

  // Draw text
  painter.DrawText(10,
                   page->GetPageSize().GetHeight() - 10 - font->GetFontSize(),
                   "left 10, top 10");
  painter.FinishPage();

  // meta data
  doc.GetInfo()->SetCreator(PoDoFo::PdfString("creator"));
  doc.GetInfo()->SetAuthor(PoDoFo::PdfString("author"));
  doc.GetInfo()->SetTitle("This is a title");
  doc.GetInfo()->SetSubject("This is the subject of pdf file");
  doc.GetInfo()->SetKeywords("keyword1;keyword2;keyword3");

  // finish
  doc.Close();

  std::cout << "created" << std::endl;
}
