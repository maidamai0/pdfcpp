#include "common.h"
#include "podofo/podofo.h"

#include <iostream>
#include <string>

auto main(int argc, char **argv) -> int {
  PoDoFo::PdfStreamedDocument doc("draw_table.pdf");
  PoDoFo::PdfPainter painter;

  // page
  const auto page = doc.CreatePage(
      PoDoFo::PdfPage::CreateStandardPageSize(PoDoFo::ePdfPageSize_A4));
  if (!page) {
    std::cerr << "create page failed" << std::endl;
    return -1;
  }
  painter.SetPage(page);
  painter.SetColor(1.0, 0.0, 0.0);

  // font
  const auto font = doc.CreateFont("Arial");
  if (!font) {
    std::cerr << "create font Arial failed" << std::endl;
    return -1;
  }
  font->SetFontSize(12.0f);
  painter.SetFont(font);

  // draw table
  constexpr int column_num = 2;
  constexpr int row_num = 4;
  PoDoFo::PdfSimpleTableModel table_model(column_num, row_num);
  table_model.SetAlignment(PoDoFo::ePdfAlignment_Left);
  //   table_model.SetBorderEnabled(PoDoFo::PODOFO_FALSE);
  table_model.SetBackgroundColor(PoDoFo::PdfColor(0.3));
  //   table_model.SetBackgroundEnabled(PoDoFo::PODOFO_TRUE);
  table_model.SetForegroundColor(PoDoFo::PdfColor(0, 0, 0)); // text color
  //   painter.SetColor(0, 0, 0);
  for (int c = 0; c < column_num; ++c) {
    for (int r = 0; r < row_num; ++r) {
      const auto text = std::string("Cell[") + std::to_string(c) + "," +
                        std::to_string(r) + "]";
      table_model.SetText(c, r, text.c_str());
    }
  }

  PoDoFo::PdfTable table(column_num, row_num);
  table.SetTableWidth(400);
  table.SetTableHeight(200);
  table.SetModel(&table_model);
  table.Draw(10, page->GetPageSize().GetHeight() / 2, &painter);

  painter.FinishPage();

  doc.Close();
}
