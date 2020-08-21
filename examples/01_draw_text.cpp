#include "podofo/podofo.h"
#include "src/base/PdfEncodingFactory.h"
#include "src/doc/PdfFontCache.h"

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
  const auto font = doc.CreateFontSubset(
      "Arial Unicode MS", false, false, false,
      PoDoFo::PdfEncodingFactory::GlobalIdentityEncodingInstance());
  if (!font) {
    PODOFO_RAISE_ERROR(PoDoFo::ePdfError_InvalidHandle);
  }
  font->SetFontSize(18.0);
  painter.SetFont(font);
  painter.SetColor(0.8, 0.4, 0.2);

  // Draw text
  PoDoFo::PdfString pString(
      reinterpret_cast<const PoDoFo::pdf_utf8 *>("12345abvdcft"));
  PoDoFo::PdfString sJap(reinterpret_cast<const PoDoFo::pdf_utf8 *>(
      "「PoDoFo」世界は今から日本語も話せます。"));
  painter.DrawText(
      10, page->GetPageSize().GetHeight() - 10 - font->GetFontSize(), pString);
  painter.DrawText(
      10, page->GetPageSize().GetHeight() - 50 - font->GetFontSize(), sJap);
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
