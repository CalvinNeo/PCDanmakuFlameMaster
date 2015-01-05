/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkImage_DEFINED
#define SkImage_DEFINED

#include "SkImageInfo.h"
#include "SkImageEncoder.h"
#include "SkRefCnt.h"
#include "SkScalar.h"
#include "SkShader.h"

class SkData;
class SkCanvas;
class SkImageGenerator;
class SkPaint;
class SkSurface;
class SkSurfaceProps;
class GrContext;
class GrTexture;

/**
 *  SkImage is an abstraction for drawing a rectagle of pixels, though the
 *  particular type of image could be actually storing its data on the GPU, or
 *  as drawing commands (picture or PDF or otherwise), ready to be played back
 *  into another canvas.
 *
 *  The content of SkImage is always immutable, though the actual storage may
 *  change, if for example that image can be re-created via encoded data or
 *  other means.
 */
class SK_API SkImage : public SkRefCnt {
public:
    SK_DECLARE_INST_COUNT(SkImage)

    typedef SkImageInfo Info;

    static SkImage* NewRasterCopy(const Info&, const void* pixels, size_t rowBytes);
    static SkImage* NewRasterData(const Info&, SkData* pixels, size_t rowBytes);

    /**
     * GrTexture is a more logical parameter for this factory, but its
     * interactions with scratch cache still has issues, so for now we take
     * SkBitmap instead. This will be changed in the future. skbug.com/1449
     */
    static SkImage* NewTexture(const SkBitmap&);

    virtual bool isOpaque() const { return false; }

    /**
     *  Construct a new SkImage based on the given ImageGenerator.
     *  This function will always take ownership of the passed
     *  ImageGenerator.  Returns NULL on error.
     */
    static SkImage* NewFromGenerator(SkImageGenerator*);

    int width() const { return fWidth; }
    int height() const { return fHeight; }
    uint32_t uniqueID() const { return fUniqueID; }

    /**
     * Return the GrTexture that stores the image pixels. Calling getTexture
     * does not affect the reference count of the GrTexture object.
     * Will return NULL if the image does not use a texture.
     */
    GrTexture* getTexture();

    virtual SkShader* newShader(SkShader::TileMode,
                                SkShader::TileMode,
                                const SkMatrix* localMatrix = NULL) const;

    /**
     *  If the image has direct access to its pixels (i.e. they are in local
     *  RAM) return the (const) address of those pixels, and if not null, return
     *  the ImageInfo and rowBytes. The returned address is only valid while
     *  the image object is in scope.
     *
     *  On failure, returns NULL and the info and rowBytes parameters are
     *  ignored.
     */
    const void* peekPixels(SkImageInfo* info, size_t* rowBytes) const;

    /**
     *  Copy the pixels from the image into the specified buffer (pixels + rowBytes),
     *  converting them into the requested format (dstInfo). The image pixels are read
     *  starting at the specified (srcX,srcY) location.
     *
     *  The specified ImageInfo and (srcX,srcY) offset specifies a source rectangle
     *
     *      srcR.setXYWH(srcX, srcY, dstInfo.width(), dstInfo.height());
     *
     *  srcR is intersected with the bounds of the image. If this intersection is not empty,
     *  then we have two sets of pixels (of equal size). Replace the dst pixels with the
     *  corresponding src pixels, performing any colortype/alphatype transformations needed
     *  (in the case where the src and dst have different colortypes or alphatypes).
     *
     *  This call can fail, returning false, for several reasons:
     *  - If srcR does not intersect the image bounds.
     *  - If the requested colortype/alphatype cannot be converted from the image's types.
     */
    bool readPixels(const SkImageInfo& dstInfo, void* dstPixels, size_t dstRowBytes,
                    int srcX, int srcY) const;

    /**
     *  Encode the image's pixels and return the result as a new SkData, which
     *  the caller must manage (i.e. call unref() when they are done).
     *
     *  If the image type cannot be encoded, or the requested encoder type is
     *  not supported, this will return NULL.
     */
    SkData* encode(SkImageEncoder::Type t = SkImageEncoder::kPNG_Type,
                   int quality = 80) const;

    /**
     *  Return a new surface that is compatible with this image's internal representation
     *  (e.g. raster or gpu).
     *
     *  If no surfaceprops are specified, the image will attempt to match the props of when it
     *  was created (if it came from a surface).
     */
    SkSurface* newSurface(const SkImageInfo&, const SkSurfaceProps* = NULL) const;

protected:
    SkImage(int width, int height) :
        fWidth(width),
        fHeight(height),
        fUniqueID(NextUniqueID()) {

        SkASSERT(width >= 0);
        SkASSERT(height >= 0);
    }

private:
    const int       fWidth;
    const int       fHeight;
    const uint32_t  fUniqueID;

    static uint32_t NextUniqueID();

    typedef SkRefCnt INHERITED;

    friend class SkCanvas;

    void draw(SkCanvas*, SkScalar x, SkScalar y, const SkPaint*) const;

    /**
     *  Draw the image, cropped to the src rect, to the dst rect of a canvas.
     *  If src is larger than the bounds of the image, the rest of the image is
     *  filled with transparent black pixels.
     *
     *  See SkCanvas::drawBitmapRectToRect for similar behavior.
     */
    void drawRect(SkCanvas*, const SkRect* src, const SkRect& dst, const SkPaint*) const;
};

#endif
