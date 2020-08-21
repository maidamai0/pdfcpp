#include "pdf_report.h"

#include "podofo/podofo.h"

#include <cassert>
#include <memory>

namespace {

// A4 page size in points
// see podofo/src/doc/PdfPage.cpp::CreateStandardPageSize for detail
constexpr auto a4_page_width = 595.0;
constexpr auto a4_page_height = 842.0;

// report meta info
constexpr auto creator = "Carestream Dental";
constexpr auto author = "Carestream Dental";

} // namespace

class PdfReport::PdfReportPodofo {
public:
  PdfReportPodofo(std::string file_name);
  ~PdfReportPodofo();
  std::unique_ptr<PoDoFo::PdfStreamedDocument> doc_;
  PoDoFo::PdfPainter painter_;
  PoDoFo::PdfFont *normal_font_; // managed by doc_
  PoDoFo::PdfFont *bold_font_;   // managed by doc_
  std::unique_ptr<PoDoFo::PdfIdentityEncoding> font_encoding_; // for utf-8
  std::string font_name_;
  PoDoFo::EPdfPageSize page_size_ = PoDoFo::ePdfPageSize_A4;
};

PdfReport::PdfReportPodofo::PdfReportPodofo(std::string file_name)
    : doc_{new PoDoFo::PdfStreamedDocument(file_name.c_str())},
      font_encoding_(
          std::make_unique<PoDoFo::PdfIdentityEncoding>(0, 0xffff, false)) {
  painter_.SetPage(
      doc_->CreatePage(PoDoFo::PdfPage::CreateStandardPageSize(page_size_)));
}

PdfReport::PdfReportPodofo::~PdfReportPodofo() {
  painter_.FinishPage();
  doc_->Close();
}

PdfReport::PdfReport(std::string file_name) {
  impl_ = new PdfReportPodofo(file_name);
}

PdfReport::~PdfReport() { delete impl_; }

void PdfReport::Generate() {
  impl_->painter_.FinishPage();
  impl_->doc_->GetInfo()->SetCreator(creator);
  impl_->doc_->GetInfo()->SetAuthor(author);
  impl_->doc_->Close();
}

void PdfReport::UseFont(std::string font_name) {
  impl_->font_name_ = font_name;
  impl_->normal_font_ =
      impl_->doc_->CreateFont(font_name.c_str(), false,
                              new PoDoFo::PdfIdentityEncoding(0, 0xffff, true));
  impl_->painter_.SetFont(impl_->normal_font_);
}

void PdfReport::BoldFont(bool bold) {
  if (bold && !impl_->bold_font_) {
    assert(!impl_->font_name_.empty() && "Call UseFont to load a font first！");
    impl_->bold_font_ = impl_->doc_->CreateFont(
        impl_->font_name_.c_str(), true, false, false,
        new PoDoFo::PdfIdentityEncoding(0, 0xffff, true),
        PoDoFo::PdfFontCache::eFontCreationFlags_AutoSelectBase14, true);
  }

  if (bold) {
    impl_->painter_.SetFont(impl_->bold_font_);
  } else {
    impl_->painter_.SetFont(impl_->normal_font_);
  }
}

void PdfReport::FontSize(float font_size) {
  impl_->painter_.GetFont()->SetFontSize(font_size);
}

void PdfReport::AddText(unsigned x, unsigned y, std::string text) {
  const auto text_heiht =
      impl_->painter_.GetFont()->GetFontMetrics()->GetLineSpacing();
  const auto podofo_y = a4_page_height - y - text_heiht;

  impl_->painter_.DrawText(
      x, podofo_y, reinterpret_cast<const PoDoFo::pdf_utf8 *>(text.c_str()));
}

PdfTablePtr PdfReport::CreateTable(unsigned column, unsigned row) {
  return PdfTable::Create(column, row, impl_->doc_.get());
}

void PdfReport::DrawTable(unsigned int x, unsigned int y, PdfTablePtr table) {
  auto size = table->GetSize();
  PoDoFo::PdfTable podofo_table(size.first, size.second);

  auto model = table->GetModel();
  model->SetAlignment(PoDoFo::ePdfAlignment_Left);
  model->SetForegroundColor(PoDoFo::PdfColor(0, 0, 0));
  model->SetText(0, 0, "empty table");
  podofo_table.SetModel(model);

  podofo_table.SetTableWidth(400);
  podofo_table.SetTableHeight(200);
  podofo_table.Draw(x, y, &impl_->painter_);
}

void PdfReport::AddImage(unsigned int x, unsigned int y,
                         const std::string &path) {
  PoDoFo::PdfImage image(impl_->doc_.get());
  image.LoadFromFile(path.c_str());
  //  const auto image_width  = image.GetWidth();
  const auto image_height = image.GetHeight();
  // image may be bigger than a4 page size

  const auto podofo_y = std::max(a4_page_height - y - image_height, 0.0);
  impl_->painter_.DrawImage(x, podofo_y, &image);
}
