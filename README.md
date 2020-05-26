# pdfcpp

pdf manipulate library

## Build

* PODOFO_BUILD_LIB_ONLY build podofo without tools,test...
* PODOFO_BUILD_STATIC build static verison
* PODOFO_BUILD_SHARED build shared verison

## dependency

### Required

pdfcpp use `podofo` as its backend, most denpendency is for `podofo`.

* [podofo](http://podofo.sourceforge.net/)
* [ZLIB](https://github.com/madler/zlib)
* [Bzip2](https://www.sourceware.org/bzip2/)
* [FreeType](https://www.freetype.org/)

### Optional

* [libcrypto/OpenSSL](https://www.openssl.org/)
* [libidn](https://www.gnu.org/software/libidn/)
* [libjpeg](http://libjpeg.sourceforge.net/)
* [tiff](http://www.libtiff.org/)
* [png](http://www.libpng.org/pub/png/libpng.html)
* [unistring](https://www.gnu.org/software/libunistring/)
* [cppunit](https://sourceforge.net/projects/cppunit/)
* [stlport](http://www.stlport.org/)