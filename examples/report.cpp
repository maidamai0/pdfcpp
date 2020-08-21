#include "common.h"
#include "pdf_report.h"
#include "pdf_table.h"

auto insert_table() {
  PdfReport report("table.pdf");
  report.UseFont(font_arial_unicode_ms);
  // add a table
  auto table = report.CreateTable(3, 3);
  report.DrawTable(10, 10, table);
  report.Generate();
}

auto insert_image_in_table() {
  PdfReport report("draw_image_in_table.pdf");
  report.UseFont(font_arial_unicode_ms);
  auto table = report.CreateTable(3, 3);
  table->SetImage(
      1, 1, full_path("peaks_alone_loneliness_125128_3840x2160.jpg").c_str());
  report.DrawTable(100, 100, table);
  report.Generate();
}

int main() {
  insert_table();
  insert_image_in_table();
}