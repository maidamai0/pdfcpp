#pragma once

/**
 * @file pdf_report.h
 * @author tonghao.yuan (tonghao.yuan@csdental.com)
 * @brief wrap and extend podofo for writing pdf files.
 * @version 0.1
 * @date 2020-05-26
 *
 * @copyright Copyright (c) 2020 Carestream Dental,LLC. All Rights Reserved
 *
 */

#include <memory>
#include <string>

#include "pdf_table.h"

/**
 * @brief The PdfReport class
 *
 * Many functions require a position parameter, the origin is top-left
 */
class PdfReport {
 public:
  PdfReport(std::string file_name);
  ~PdfReport();

  /**
   * @brief Generate report
   *
   * call this only after you have done all the drawings.
   */
  void Generate();

  /**
   * @brief Create an empty table at position [x,y]
   *
   * @param x       position,x
   * @param y       position, y, origion is top-left
   * @param column  number of columns of table
   * @param row     number of rows of table
   */
  PdfTablePtr CreateTable(unsigned column, unsigned row);

  /**
   * @brief draw table at specified position
   * @param x       positon, x
   * @param y       position,y
   * @param table   table to be drawed
   */
  void DrawTable(unsigned x, unsigned y, PdfTablePtr table);

  /**
   * @brief Insert a image to pdf at the positoin[x,y]
   *
   * @param x       position,x
   * @param y       position, y, origion is top-left
   * @param path    full path to image file
   *
   * @note supported image types are png,jpeg,tiff
   */
  void AddImage(unsigned x, unsigned y, const std::string &path);

  /**
   * @brief AddImage    Insert a image to the cell[row, column] of table
   * @param table       table the image will be inserted into, you can get a table by calling @ref AddTable
   * @param column      the column of table cell image will be inserted into, indexed from 0.
   * @param row         the row of table cell image will be inserted into, indexed from 0.
   * @param full_path   full path of image file.
   */
  //  void AddImage(PdfTablePtr table, unsigned column, unsigned row, const std::string &full_path);

  /**
   * @brief use specified font for text
   * @param font_name
   */
  void UseFont(std::string font_name);

  /**
   * @brief use bold font or not
   * @param bold    true for bold font fasle for not.
   */
  void BoldFont(bool bold);

  void FontSize(float font_size);

  /**
   * @brief add text
   * @param x       x of positon
   * @param y       y of potion
   * @param text    string
   */
  void AddText(unsigned x, unsigned y, std::string text);

  /**
   * @brief use a new page
   */
  void NextPage();

 private:
  class PdfReportPodofo;
  PdfReportPodofo *impl_         = nullptr;
  bool             is_bold_font_ = false;
};
