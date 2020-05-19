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

  // image
  PoDoFo::PdfImage image(&doc);
  image.LoadFromFile(
      common::full_path("peaks_alone_loneliness_125128_3840x2160.jpg").c_str());
  painter.DrawImage(0, 0, &image, 0.1, 0.1);
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
