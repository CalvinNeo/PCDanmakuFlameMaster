
/*
 * Copyright 2011 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef GrPaint_DEFINED
#define GrPaint_DEFINED

#include "GrColor.h"
#include "GrFragmentStage.h"
#include "GrXferProcessor.h"
#include "effects/GrPorterDuffXferProcessor.h"

#include "SkXfermode.h"

/**
 * The paint describes how color and coverage are computed at each pixel by GrContext draw
 * functions and the how color is blended with the destination pixel.
 *
 * The paint allows installation of custom color and coverage stages. New types of stages are
 * created by subclassing GrProcessor.
 *
 * The primitive color computation starts with the color specified by setColor(). This color is the
 * input to the first color stage. Each color stage feeds its output to the next color stage. The
 * final color stage's output color is input to the color filter specified by
 * setXfermodeColorFilter which produces the final source color, S.
 *
 * Fractional pixel coverage follows a similar flow. The coverage is initially the value specified
 * by setCoverage(). This is input to the first coverage stage. Coverage stages are chained
 * together in the same manner as color stages. The output of the last stage is modulated by any
 * fractional coverage produced by anti-aliasing. This last step produces the final coverage, C.
 *
 * setBlendFunc() specifies blending coefficients for S (described above) and D, the initial value
 * of the destination pixel, labeled Bs and Bd respectively. The final value of the destination
 * pixel is then D' = (1-C)*D + C*(Bd*D + Bs*S).
 *
 * Note that the coverage is applied after the blend. This is why they are computed as distinct
 * values.
 *
 * TODO: Encapsulate setXfermodeColorFilter in a GrProcessor and remove from GrPaint.
 */
class GrPaint {
public:
    GrPaint() { this->reset(); }

    GrPaint(const GrPaint& paint) { *this = paint; }

    ~GrPaint() {}

    /**
     * The initial color of the drawn primitive. Defaults to solid white.
     */
    void setColor(GrColor color) { fColor = color; }
    GrColor getColor() const { return fColor; }

    /**
     * Should primitives be anti-aliased or not. Defaults to false.
     */
    void setAntiAlias(bool aa) { fAntiAlias = aa; }
    bool isAntiAlias() const { return fAntiAlias; }

    /**
     * Should dithering be applied. Defaults to false.
     */
    void setDither(bool dither) { fDither = dither; }
    bool isDither() const { return fDither; }

    const GrXPFactory* setXPFactory(const GrXPFactory* xpFactory) {
        fXPFactory.reset(SkRef(xpFactory));
        return xpFactory;
    }

    void setPorterDuffXPFactory(SkXfermode::Mode mode) {
        fXPFactory.reset(GrPorterDuffXPFactory::Create(mode));
    }

    void setPorterDuffXPFactory(GrBlendCoeff src, GrBlendCoeff dst) {
        fXPFactory.reset(GrPorterDuffXPFactory::Create(src, dst));
    }

    /**
     * Appends an additional color processor to the color computation.
     */
    const GrFragmentProcessor* addColorProcessor(const GrFragmentProcessor* fp) {
        SkASSERT(fp);
        SkNEW_APPEND_TO_TARRAY(&fColorStages, GrFragmentStage, (fp));
        return fp;
    }

    /**
     * Appends an additional coverage processor to the coverage computation.
     */
    const GrFragmentProcessor* addCoverageProcessor(const GrFragmentProcessor* fp) {
        SkASSERT(fp);
        SkNEW_APPEND_TO_TARRAY(&fCoverageStages, GrFragmentStage, (fp));
        return fp;
    }

    /**
     * Helpers for adding color or coverage effects that sample a texture. The matrix is applied
     * to the src space position to compute texture coordinates.
     */
    void addColorTextureProcessor(GrTexture*, const SkMatrix&);
    void addCoverageTextureProcessor(GrTexture*, const SkMatrix&);
    void addColorTextureProcessor(GrTexture*, const SkMatrix&, const GrTextureParams&);
    void addCoverageTextureProcessor(GrTexture*, const SkMatrix&, const GrTextureParams&);

    int numColorStages() const { return fColorStages.count(); }
    int numCoverageStages() const { return fCoverageStages.count(); }
    int numTotalStages() const { return this->numColorStages() + this->numCoverageStages(); }

    const GrXPFactory* getXPFactory() const { return fXPFactory.get(); }

    const GrFragmentStage& getColorStage(int s) const { return fColorStages[s]; }
    const GrFragmentStage& getCoverageStage(int s) const { return fCoverageStages[s]; }

    GrPaint& operator=(const GrPaint& paint) {
        fAntiAlias = paint.fAntiAlias;
        fDither = paint.fDither;

        fColor = paint.fColor;

        fColorStages = paint.fColorStages;
        fCoverageStages = paint.fCoverageStages;

        fXPFactory.reset(SkRef(paint.getXPFactory()));

        return *this;
    }

    /**
     * Resets the paint to the defaults.
     */
    void reset() {
        this->resetOptions();
        this->resetColor();
        this->resetStages();
    }

    /**
     * Returns true if isOpaque would return true and the paint represents a solid constant color
     * draw. If the result is true, constantColor will be updated to contain the constant color.
     */
    bool isOpaqueAndConstantColor(GrColor* constantColor) const;

    /**
     * DO NOT USE THESE
     * TODO Remove remaining use cases and delete these
     */
    void localCoordChange(const SkMatrix& oldToNew) {
        for (int i = 0; i < fColorStages.count(); ++i) {
            fColorStages[i].localCoordChange(oldToNew);
        }
        for (int i = 0; i < fCoverageStages.count(); ++i) {
            fCoverageStages[i].localCoordChange(oldToNew);
        }
    }

    bool localCoordChangeInverse(const SkMatrix& newToOld) {
        SkMatrix oldToNew;
        bool computed = false;
        for (int i = 0; i < fColorStages.count(); ++i) {
            if (!computed && !newToOld.invert(&oldToNew)) {
                return false;
            } else {
                computed = true;
            }
            fColorStages[i].localCoordChange(oldToNew);
        }
        for (int i = 0; i < fCoverageStages.count(); ++i) {
            if (!computed && !newToOld.invert(&oldToNew)) {
                return false;
            } else {
                computed = true;
            }
            fCoverageStages[i].localCoordChange(oldToNew);
        }
        return true;
    }

private:
    friend class GrContext; // To access above two functions
    friend class GrStencilAndCoverTextContext;  // To access above two functions

    SkAutoTUnref<const GrXPFactory> fXPFactory;
    SkSTArray<4, GrFragmentStage>   fColorStages;
    SkSTArray<2, GrFragmentStage>   fCoverageStages;

    bool                            fAntiAlias;
    bool                            fDither;

    GrColor                         fColor;

    void resetOptions() {
        fAntiAlias = false;
        fDither = false;
    }

    void resetColor() {
        fColor = GrColorPackRGBA(0xff, 0xff, 0xff, 0xff);
    }

    void resetStages();
};

#endif
