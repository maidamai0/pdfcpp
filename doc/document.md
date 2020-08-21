# Document class diagram

```plantuml
PdfVariant <|-- PdfObject

class PdfObject {
    PdfStream*     m_pStream;
    PdfVecObjects* m_pOwner;
}

class PdfElement{
    PdfObject* m_pObject;
}
PdfElement o--PdfObject

class PdfDocument {
}
PdfDocument ... PdfElement

PdfDocument <|-- PdfMemDocument

PdfElement <|-- PdfFont
PdfElement <|-- PdfInfo

PdfCanvas <|-- PdfXObject
PdfElement <|-- PdfXObject
PdfXObject <|-- PdfImage
```
