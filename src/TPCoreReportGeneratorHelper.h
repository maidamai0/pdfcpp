#pragma once

#include <podofo/podofo.h>

using namespace PoDoFo;

class ReportGeneratorHelper {
public:
  // Conversion methods
  static std::string IntToString(const int &value);
  static std::string ConvertDoubleToString(const double value,
                                           const int precision,
                                           const std::string &unit);
  static std::string FormatDoubleToString(const double value,
                                          const int precision);

  static void DrawTextInRect(PdfRect destRect, const PdfString &text,
                             PdfPainter &painter,
                             PoDoFo::EPdfAlignment alignment);

  static PdfRect ApplyPadding(const PdfRect &inputRect, double paddingX,
                              double paddingY);

  static void DrawRectangle(const PdfRect &destRect, const PdfColor &color,
                            PdfPainter &painter);

  static void DrawStrokingRectangle(const PdfRect &destRect,
                                    const double strokingWidth,
                                    const PdfColor &color, PdfPainter &painter);

  static void DrawCircle(const double x, const double y, const double radius,
                         const PdfColor &color, PdfPainter &painter);

  static void DrawTextInColoredRect(
      const PdfString &text, const PdfRect &rect, PdfPainter &painter,
      const PdfColor &textColor, const PdfColor &backColor,
      PoDoFo::EPdfAlignment alignment = PoDoFo::ePdfAlignment_Left);

  static std::string Truncate(const std::string &text, size_t length);
};