set(PODOFO_FOUND TRUE)

find_library(PODOFO_LIB podofo)
if(PODOFO_LIB STREQUAL "PODOFO_LIB-NOTFOUND")
    message(WARNING "podofo library not found")
    set(PODOFO_FOUND FALSE)
endif()

find_path(PODOFO_INCLUDE_DIR podofo/podofo.h)
if(PODOFO_INCLUDE_DIR STREQUAL "PODOFO_INCLUDE_DIR-NOTFOUND")
    message(WARNING "podofo/podofo.h not found")
    set(PODOFO_FOUND FALSE)
else()
    include_directories(${PODOFO_INCLUDE_DIR})
endif()

find_package(freetype CONFIG REQUIRED)
find_package(JPEG REQUIRED)
find_library(TIFF_LIB tiff)
find_package(LibLZMA CONFIG REQUIRED)

set(PODOFO_LIB ${PODOFO_LIB} freetype ${JPEG_LIBRARIES} ${TIFF_LIB} LibLZMA::LibLZMA Ws2_32)