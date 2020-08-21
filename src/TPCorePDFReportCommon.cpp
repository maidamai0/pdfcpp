
#include "TPCorePDFReportCommon.h"
#include "TPCoreReportGeneratorHelper.h"

#include <string>

PDFReportCommon::PDFReportCommon(std::string file_name)
    : document(file_name.c_str()), pageCount(0) {
  if (!this->document.IsPrintAllowed())
    PODOFO_RAISE_ERROR(ePdfError_InvalidStream);
}

PDFReportCommon::~PDFReportCommon() { document.Close(); }

PDFReportPage::PDFReportPage(PdfStreamedDocument &document)
    : pDocument(&document) {
  // Create page
  pPage = document.CreatePage(
      PdfPage::CreateStandardPageSize(ePdfPageSize_A4, bLandscape));
  if (!pPage)
    PODOFO_RAISE_ERROR(ePdfError_InvalidHandle);
  painter.SetPage(pPage);

  // Create font
  pFont = InitFont(false, false);
  if (!pFont)
    PODOFO_RAISE_ERROR(ePdfError_InvalidHandle);
  painter.SetFont(pFont);

  // Define body rect
  const double footerHeight = 10;

  const double left = 2;
  const double bottom = footerHeight;
  const double width = pPage->GetPageSize().GetWidth() - 2 * 2;
  const double height = pPage->GetPageSize().GetHeight() - footerHeight - 2;
  bodyRect = PdfRect(left, bottom, width, height);

  // Init current bottom position for next element to write
  currentBottom = bodyRect.GetBottom() + bodyRect.GetHeight();
}

PDFReportPage::~PDFReportPage() { painter.FinishPage(); }

void PDFReportPage::SetFontSize(float size) const {
  if (!pFont)
    PODOFO_RAISE_ERROR(ePdfError_InvalidHandle);

  pFont->SetFontSize(size);
}

void PDFReportPage::SetFontStyle(bool bold, bool italic) {
  if (!pFont)
    PODOFO_RAISE_ERROR(ePdfError_InvalidHandle);

  // Save current font
  const auto pCurrentFont = pFont;

  // Create new font
  pFont = InitFont(bold, italic);
  if (!pFont)
    PODOFO_RAISE_ERROR(ePdfError_InvalidHandle);
  painter.SetFont(pFont);

  // Apply current font size
  pFont->SetFontSize(pCurrentFont->GetFontSize());
}

void PDFReportPage::SetColor(const PdfColor &color) { painter.SetColor(color); }

void PDFReportPage::WriteDocumentTitle(const std::string &title) {
  SetFontSize(20);
  SetFontStyle(true, false);
  WriteText(title, ePdfAlignment_Center);
}

void PDFReportPage::WriteText(const std::string &text, EPdfAlignment alignment,
                              const double leftPadding) {
  const double width = bodyRect.GetWidth() - leftPadding;
  const double height = painter.GetFont()->GetFontMetrics()->GetLineSpacing();
  const double left = bodyRect.GetLeft() + leftPadding;
  const double bottom = currentBottom - height;

  const PdfRect rect(left, bottom, width, height);

  ReportGeneratorHelper::DrawTextInRect(rect, text.c_str(), painter, alignment);

  // Update current bottom position
  currentBottom = bottom;
}

void PDFReportPage::WriteText(
    const std::string &text, const PdfRect &destRect,
    const EPdfAlignment &alignment /*=ePdfAlignment_Left*/,
    const double leftPadding /*=0.0*/) {
  PdfRect finalRect = destRect;
  finalRect.SetLeft(finalRect.GetLeft() + leftPadding);
  finalRect.SetWidth(finalRect.GetWidth() - leftPadding);

  ReportGeneratorHelper::DrawTextInRect(finalRect, text.c_str(), painter,
                                        alignment);
}

void PDFReportPage::WriteMultiLineText(
    const std::string &text, const PdfRect destRect,
    const EPdfAlignment alignment /*=ePdfAlignement_Left*/,
    const double leftPadding /*=0.0*/) {
  PdfRect finalRect = destRect;
  finalRect.SetLeft(finalRect.GetLeft() + leftPadding);
  finalRect.SetWidth(finalRect.GetWidth() - leftPadding);

  painter.DrawMultiLineText(finalRect, text.c_str(), alignment,
                            ePdfVerticalAlignment_Top, false);
}

void PDFReportPage::AddBlank(const double height) { currentBottom -= height; }

static std::vector<std::string> vFontNames;

int CALLBACK FontNameProc(ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme,
                          int FontType, LPARAM lParam) {
  // std::basic_string<WCHAR> string(lpelfe->elfFullName);
  // const std::string sName(string.begin(), string.end());
  // if (std::find(vFontNames.begin(), vFontNames.end(), sName) !=
  //     vFontNames.end())
  //   return 1;

  // vFontNames.push_back(sName);
  return 1;
}

int GetListFonts(const bool bBold, const bool bItalic) {
  vFontNames.clear();

  LOGFONT lf;
  ZeroMemory(&lf, sizeof lf);

  lf.lfHeight = 0;
  lf.lfWidth = 0;
  lf.lfEscapement = 0;
  lf.lfOrientation = 0;
  lf.lfWeight = bBold ? FW_BOLD : 0;
  lf.lfItalic = bItalic;
  lf.lfUnderline = 0;
  lf.lfStrikeOut = 0;
  lf.lfCharSet = DEFAULT_CHARSET;
  lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
  lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
  lf.lfQuality = DEFAULT_QUALITY;
  lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;

  const HDC hdc = GetDC(0);
  EnumFontFamiliesEx(hdc, &lf, (FONTENUMPROC)FontNameProc, 0, 0);
  ReleaseDC(0, hdc);
  return 0;
}

PdfFont *PDFReportPage::InitFont(const bool bBold, const bool bItalic) const {
  // GetListFonts(bBold, bItalic);
  static std::vector<std::string> vFonts;
  if (vFonts.empty()) {
    vFonts.push_back("Arial Unicode MS");
    vFonts.push_back("Batang Normal");
    vFonts.push_back("Batang Regular");
    vFonts.push_back("Batang");
    vFonts.push_back("BatangChe Normal");
    vFonts.push_back("BatangChe Regular");
    vFonts.push_back("BatangChe");
    vFonts.push_back("Gulim Normal");
    vFonts.push_back("Gulim Regular");
    vFonts.push_back("Gulim");
    vFonts.push_back("GulimChe Normal");
    vFonts.push_back("GulimChe Regular");
    vFonts.push_back("GulimChe");
    vFonts.push_back("Malgun Gothic");
    vFonts.push_back("Microsoft NeoGothic");
    vFonts.push_back("Unifont"); // free font to be added with installer
    vFonts.push_back("Arial");
  }

  for (const auto &font : vFonts) {
    // if (std::find(vFontNames.begin(), vFontNames.end(), font) !=
    //     vFontNames.end()) {
    PdfFont *pFont = pDocument->CreateFont(
        font.c_str(), bBold, bItalic, false,
        PoDoFo::PdfEncodingFactory::GlobalIdentityEncodingInstance());
    if (pFont) {
      return pFont;
    }
    // }
  }
  return nullptr;
}