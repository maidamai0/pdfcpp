#include "pdf_table.h"

#include "podofo/podofo.h"

class PdfTable::PdfTableModelData : public PoDoFo::PdfSimpleTableModel {
 public:
  PdfTableModelData(unsigned col, unsigned row, PoDoFo::PdfStreamedDocument* doc)
    : PoDoFo::PdfSimpleTableModel(col, row), doc_(doc), column_num_(col), row_num_(row) {}

  ~PdfTableModelData() {
    for (auto& kv : images_) {
      delete kv.second;
    }
  }

  bool HasImage(int col, int row) const override {
    return images_.find(encode(col, row)) != images_.end();
  }

  PoDoFo::PdfImage* GetImage(int col, int row) const override {
    auto it = images_.find(encode(col, row));
    if (it == images_.end()) {
      return nullptr;
    } else {
      return it->second;
    }
  }

  void SetImage(int col, int row, const std::string& path) {
    auto pair = images_.insert(std::make_pair(encode(col, row), new PoDoFo::PdfImage(doc_)));
    if (pair.second) {
      pair.first->second->LoadFromFile(path.c_str());
    } else {
      // TODO log here
    }
  }

 private:
  // encode (col, row) to an unsigned
  unsigned int encode(unsigned col, unsigned row) const {
    return col * 10 + row;
  }

 public:
  // key is encode(col,row), value is image path
  std::map<unsigned, PoDoFo::PdfImage*> images_;
  PoDoFo::PdfStreamedDocument*          doc_ = nullptr;  //  no ownership

  // these two is private in PoDoFo::SimpleTableModel
  const unsigned column_num_ = 0;
  const unsigned row_num_    = 0;
};

PdfTable::PdfTable(unsigned col, unsigned row, PoDoFo::PdfStreamedDocument* doc) : data_(new PdfTableModelData(col, row, doc)) {}

PdfTable::~PdfTable() {
  delete data_;
}

void PdfTable::SetImage(int col, int row, const std::string& path) {
  data_->SetImage(col, row, path);
}

PoDoFo::PdfSimpleTableModel* PdfTable::GetModel() {
  return data_;
}

std::pair<int, int> PdfTable::GetSize() const {
  return std::make_pair(data_->column_num_, data_->row_num_);
}
