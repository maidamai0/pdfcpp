#include "common.h"
#include "podofo/podofo.h"

#include <iostream>

auto main(int argc, char **argv) -> int {
  PoDoFo::PdfStreamedDocument doc{"draw_image.pdf"};
  PoDoFo::PdfPainter painter;

  // page
  const auto page = doc.CreatePage(
      PoDoFo::PdfPage::CreateStandardPageSize(PoDoFo::ePdfPageSize_A4));
  if (!page) {
    PODOFO_RAISE_ERROR(PoDoFo::ePdfError_InvalidHandle);
  }
  painter.SetPage(page);
  // painter.FinishPage();

  // page 2
  const auto page2 = doc.CreatePage(
      PoDoFo::PdfPage::CreateStandardPageSize(PoDoFo::ePdfPageSize_A4));
  painter.SetPage(page2);

  // image
  PoDoFo::PdfImage image(&doc);
  image.LoadFromFile(full_path("smile_upside_down.png").c_str());

  auto [x, y] = get_position_for_center(image);

  painter.DrawImage(x, y, &image);
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
