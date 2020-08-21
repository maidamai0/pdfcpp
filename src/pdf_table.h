#pragma once

/**
 * @file pdf_table.h
 * @author tonghao.yuan (tonghao.yuan@csdental.com)
 * @brief   A table in pdf file
 * @version 0.1
 * @date 2020-05-27
 *
 * @copyright Copyright (c) 2020 Carestream Dental,LLC. All Rights Reserved
 *
 */

#include <map>
#include <memory>
#include <string>

namespace PoDoFo {
class PdfSimpleTableModel;
class PdfStreamedDocument;
}  // namespace PoDoFo

class PdfTable {
 public:
  static std::shared_ptr<PdfTable> Create(unsigned col, unsigned row, PoDoFo::PdfStreamedDocument *doc) {
    return std::shared_ptr<PdfTable>(new PdfTable(col, row, doc));
  }
  ~PdfTable();
  void                         SetImage(int col, int row, const std::string &path);
  PoDoFo::PdfSimpleTableModel *GetModel();

  /**
   * @brief get column and row number
   * @return <col, row>
   */
  std::pair<int, int> GetSize() const;

 private:
  PdfTable(unsigned col, unsigned row, PoDoFo::PdfStreamedDocument *doc);

 private:
  class PdfTableModelData;
  PdfTableModelData *data_ = nullptr;
};

using PdfTablePtr = std::shared_ptr<PdfTable>;
