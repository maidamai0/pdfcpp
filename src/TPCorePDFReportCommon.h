#pragma once

#include <podofo/podofo.h>
#include <string>

using namespace PoDoFo;

class PDFReportPage;
struct PDFGridCell;
struct ThumbnailGeneratorData;

class PDFReportCommon {
public:
  explicit PDFReportCommon(std::string file_name);
  virtual ~PDFReportCommon();
  virtual bool WriteFirstPage() { return true; };
  virtual bool WriteIndexOfComplexity() { return true; };

protected:
  PdfStreamedDocument document;

private:
  unsigned int pageCount;
};

class PDFReportPage {
public:
  explicit PDFReportPage(PdfStreamedDocument &document);
  ~PDFReportPage();
  void SetFontSize(float size) const;

  void SetFontStyle(bool bold, bool italic);

  void SetColor(const PdfColor &color);

  void WritePageNumber(unsigned int pageNumber);

  void WriteDocumentTitle(const std::string &title);

  void WriteTitle1(const std::string &title);

  void WriteTitle2(const std::string &title);

  void WriteTitle2(const std::string &title, const PdfRect &destRect);

  void WriteText(const std::string &text,
                 const EPdfAlignment alignment = ePdfAlignment_Left,
                 const double leftPadding = 0.0);

  void WriteText(const std::string &text, const PdfRect &destRect,
                 const EPdfAlignment &alignment = ePdfAlignment_Left,
                 const double leftPadding = 0.0);

  void WriteMultiLineText(const std::string &text,
                          const EPdfAlignment alignment = ePdfAlignment_Left,
                          const double leftPadding = 0.0);

  void WriteMultiLineText(const std::string &text, const PdfRect destRect,
                          const EPdfAlignment alignment = ePdfAlignment_Left,
                          const double leftPadding = 0.0);

  void WriteTextWithColoredBackground(
      const std::string &text,
      const EPdfAlignment alignment = ePdfAlignment_Left,
      double leftPadding = 0.0, double widthRatio = 1.0);

  void DrawRectangle(const PdfRect &destRect, const PdfColor &color);

  void DrawStrokingRectangle(const PdfRect &destRect, const double strokeWidth,
                             const PdfColor &color);

  void DrawCircle(const double x, const double y, const double radius,
                  const PdfColor &color);

  void DrawLine(const double xStart, const double yStart, const double xEnd,
                const double yEnd);
  void AddBlank(double height);

protected:
private:
  PDFReportPage(const PDFReportPage &) = delete;
  PDFReportPage &operator=(const PDFReportPage &) = delete;
  PdfFont *InitFont(bool bBold, bool bItalic) const;
  PdfStreamedDocument *pDocument = nullptr;
  bool bLandscape;
  PdfPage *pPage = nullptr;
  PdfFont *pFont = nullptr;
  PdfPainter painter;
  PdfRect bodyRect;
  double currentBottom;
};
