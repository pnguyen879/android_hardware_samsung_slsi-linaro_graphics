#include "ExynosVirtualDisplayModule.h"
#include "ExynosHWCUtils.h"

ExynosVirtualDisplayModule::ExynosVirtualDisplayModule(struct exynos5_hwc_composer_device_1_t *pdev)
    : ExynosVirtualDisplay(pdev)
{
    mGLESFormat = HAL_PIXEL_FORMAT_EXYNOS_YCbCr_420_SP_M;
    mExternalMPPDstFormat = HAL_PIXEL_FORMAT_RGBA_8888;
}

ExynosVirtualDisplayModule::~ExynosVirtualDisplayModule()
{
}

int32_t ExynosVirtualDisplayModule::getDisplayAttributes(const uint32_t attribute, uint32_t __unused config)
{
    switch(attribute) {
        case HWC_DISPLAY_COMPOSITION_TYPE:
            return mCompositionType;
        case HWC_DISPLAY_GLES_FORMAT:
            return mGLESFormat;
        case HWC_DISPLAY_SINK_BQ_FORMAT:
            if (mIsSecureDRM)
                return HAL_PIXEL_FORMAT_EXYNOS_YCbCr_420_SPN;
            else
                return mGLESFormat;
        case HWC_DISPLAY_SINK_BQ_USAGE:
            return mSinkUsage;
        case HWC_DISPLAY_SINK_BQ_WIDTH:
            if (mDisplayWidth == 0)
                return mWidth;
            return mDisplayWidth;
        case HWC_DISPLAY_SINK_BQ_HEIGHT:
            if (mDisplayHeight == 0)
                return mHeight;
            return mDisplayHeight;
        default:
            ALOGE("unknown display attribute %u", attribute);
            return -EINVAL;
    }
    return 0;
}