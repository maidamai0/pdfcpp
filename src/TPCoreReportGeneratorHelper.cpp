
#include "TPCoreReportGeneratorHelper.h"

void ReportGeneratorHelper::DrawTextInRect(PdfRect destRect,
                                           const PdfString &text,
                                           PdfPainter &painter,
                                           PoDoFo::EPdfAlignment alignment) {
  const double y = destRect.GetBottom() + (destRect.GetHeight() / 2.0) -
                   (painter.GetFont()->GetFontMetrics()->GetLineSpacing() / 4);
  painter.DrawTextAligned(destRect.GetLeft(), y, destRect.GetWidth(), text,
                          alignment); // todo draw multilinetext
}

PdfRect ReportGeneratorHelper::ApplyPadding(const PdfRect &inputRect,
                                            double paddingX, double paddingY) {
  PdfRect outputRect(inputRect.GetLeft() + paddingX,
                     inputRect.GetBottom() + paddingY,
                     inputRect.GetWidth() - 2.0 * paddingX,
                     inputRect.GetHeight() - 2.0 * paddingY);
  return outputRect;
}

void ReportGeneratorHelper::DrawRectangle(const PdfRect &destRect,
                                          const PdfColor &color,
                                          PdfPainter &painter) {
  painter.SetColor(color);
  painter.Rectangle(destRect);
  painter.Fill();
}

void ReportGeneratorHelper::DrawStrokingRectangle(const PdfRect &destRect,
                                                  const double strokingWidth,
                                                  const PdfColor &color,
                                                  PdfPainter &painter) {
  painter.SetStrokingColor(color);
  painter.SetStrokeWidth(strokingWidth);
  painter.Rectangle(destRect);
  painter.Stroke();
}

void ReportGeneratorHelper::DrawCircle(const double x, const double y,
                                       const double radius,
                                       const PdfColor &color,
                                       PdfPainter &painter) {
  painter.SetColor(color);
  painter.Circle(x, y, radius);
  painter.Fill();
}

void ReportGeneratorHelper::DrawTextInColoredRect(
    const PdfString &text, const PdfRect &rect, PdfPainter &painter,
    const PdfColor &textColor, const PdfColor &backColor,
    PoDoFo::EPdfAlignment alignment) {
  if (text.GetLength() > 0) {
    DrawRectangle(rect, backColor, painter);

    painter.SetColor(textColor);
    DrawTextInRect(rect, text, painter, alignment);
  }
}