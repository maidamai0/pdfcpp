#include "common.h"
#include "podofo/podofo.h"
#include <string>

int main(int argc, char **argv) {
  using namespace PoDoFo;
  PdfStreamedDocument doc{"outlines.pdf"};

  // create painter
  PdfPainter painter;

  // outline
  const auto outlines = doc.GetOutlines();
  auto root = outlines->CreateRoot("Test Outline");

  for (int i = 0; i < 10; ++i) {
    // crate page
    const auto page = doc.CreatePage(
        PdfPage::CreateStandardPageSize(PoDoFo::ePdfPageSize_A4));

    if (!page) {
      PODOFO_RAISE_ERROR(PoDoFo::ePdfError_InvalidHandle);
    }

    painter.SetPage(page);

    root->CreateChild("Page " + std::to_string(i + 1), PdfDestination(page));
    painter.FinishPage();
  }

  doc.Close();
}