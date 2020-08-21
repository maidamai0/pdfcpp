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
  image.LoadFromFile(
      R"(C:\Program Files (x86)\Common Files\Trophy\Acquisition\DriverAltair\resources\shade_report\report_logo.png)");
  painter.DrawImage(0, 0, &image);
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
