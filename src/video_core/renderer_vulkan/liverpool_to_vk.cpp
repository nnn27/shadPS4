// SPDX-FileCopyrightText: Copyright 2024 shadPS4 Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "common/assert.h"
#include "video_core/amdgpu/pixel_format.h"
#include "video_core/renderer_vulkan/liverpool_to_vk.h"

#include <magic_enum.hpp>

namespace Vulkan::LiverpoolToVK {

using DepthBuffer = Liverpool::DepthBuffer;

vk::StencilOp StencilOp(Liverpool::StencilFunc op) {
    switch (op) {
    case Liverpool::StencilFunc::Keep:
        return vk::StencilOp::eKeep;
    case Liverpool::StencilFunc::Zero:
        return vk::StencilOp::eZero;
    case Liverpool::StencilFunc::ReplaceTest:
        return vk::StencilOp::eReplace;
    case Liverpool::StencilFunc::AddClamp:
        return vk::StencilOp::eIncrementAndClamp;
    case Liverpool::StencilFunc::SubClamp:
        return vk::StencilOp::eDecrementAndClamp;
    case Liverpool::StencilFunc::Invert:
        return vk::StencilOp::eInvert;
    case Liverpool::StencilFunc::AddWrap:
        return vk::StencilOp::eIncrementAndWrap;
    case Liverpool::StencilFunc::SubWrap:
        return vk::StencilOp::eDecrementAndWrap;
    case Liverpool::StencilFunc::ReplaceOp:
        return vk::StencilOp::eReplace;
    default:
        UNREACHABLE();
        return vk::StencilOp::eKeep;
    }
}

vk::CompareOp CompareOp(Liverpool::CompareFunc func) {
    switch (func) {
    case Liverpool::CompareFunc::Always:
        return vk::CompareOp::eAlways;
    case Liverpool::CompareFunc::Equal:
        return vk::CompareOp::eEqual;
    case Liverpool::CompareFunc::GreaterEqual:
        return vk::CompareOp::eGreaterOrEqual;
    case Liverpool::CompareFunc::Greater:
        return vk::CompareOp::eGreater;
    case Liverpool::CompareFunc::LessEqual:
        return vk::CompareOp::eLessOrEqual;
    case Liverpool::CompareFunc::Less:
        return vk::CompareOp::eLess;
    case Liverpool::CompareFunc::NotEqual:
        return vk::CompareOp::eNotEqual;
    case Liverpool::CompareFunc::Never:
        return vk::CompareOp::eNever;
    default:
        UNREACHABLE();
        return vk::CompareOp::eAlways;
    }
}

vk::PrimitiveTopology PrimitiveType(Liverpool::PrimitiveType type) {
    switch (type) {
    case Liverpool::PrimitiveType::PointList:
        return vk::PrimitiveTopology::ePointList;
    case Liverpool::PrimitiveType::LineList:
        return vk::PrimitiveTopology::eLineList;
    case Liverpool::PrimitiveType::LineStrip:
        return vk::PrimitiveTopology::eLineStrip;
    case Liverpool::PrimitiveType::TriangleList:
        return vk::PrimitiveTopology::eTriangleList;
    case Liverpool::PrimitiveType::TriangleFan:
        return vk::PrimitiveTopology::eTriangleFan;
    case Liverpool::PrimitiveType::TriangleStrip:
        return vk::PrimitiveTopology::eTriangleStrip;
    case Liverpool::PrimitiveType::AdjLineList:
        return vk::PrimitiveTopology::eLineListWithAdjacency;
    case Liverpool::PrimitiveType::AdjLineStrip:
        return vk::PrimitiveTopology::eLineStripWithAdjacency;
    case Liverpool::PrimitiveType::AdjTriangleList:
        return vk::PrimitiveTopology::eTriangleListWithAdjacency;
    case Liverpool::PrimitiveType::AdjTriangleStrip:
        return vk::PrimitiveTopology::eTriangleStripWithAdjacency;
    case Liverpool::PrimitiveType::PatchPrimitive:
        return vk::PrimitiveTopology::ePatchList;
    case Liverpool::PrimitiveType::QuadList:
        // Needs to generate index buffer on the fly.
        return vk::PrimitiveTopology::eTriangleList;
    case Liverpool::PrimitiveType::RectList:
        return vk::PrimitiveTopology::eTriangleStrip;
    default:
        UNREACHABLE();
        return vk::PrimitiveTopology::eTriangleList;
    }
}

vk::PolygonMode PolygonMode(Liverpool::PolygonMode mode) {
    switch (mode) {
    case Liverpool::PolygonMode::Point:
        return vk::PolygonMode::ePoint;
    case Liverpool::PolygonMode::Line:
        return vk::PolygonMode::eLine;
    case Liverpool::PolygonMode::Fill:
        return vk::PolygonMode::eFill;
    default:
        UNREACHABLE();
        return vk::PolygonMode::eFill;
    }
}

vk::CullModeFlags CullMode(Liverpool::CullMode mode) {
    switch (mode) {
    case Liverpool::CullMode::None:
        return vk::CullModeFlagBits::eNone;
    case Liverpool::CullMode::Front:
        return vk::CullModeFlagBits::eFront;
    case Liverpool::CullMode::Back:
        return vk::CullModeFlagBits::eBack;
    case Liverpool::CullMode::FrontAndBack:
        return vk::CullModeFlagBits::eFrontAndBack;
    default:
        UNREACHABLE();
        return vk::CullModeFlagBits::eNone;
    }
}

vk::BlendFactor BlendFactor(Liverpool::BlendControl::BlendFactor factor) {
    using BlendFactor = Liverpool::BlendControl::BlendFactor;
    switch (factor) {
    case BlendFactor::Zero:
        return vk::BlendFactor::eZero;
    case BlendFactor::One:
        return vk::BlendFactor::eOne;
    case BlendFactor::SrcColor:
        return vk::BlendFactor::eSrcColor;
    case BlendFactor::OneMinusSrcColor:
        return vk::BlendFactor::eOneMinusSrcColor;
    case BlendFactor::SrcAlpha:
        return vk::BlendFactor::eSrcAlpha;
    case BlendFactor::OneMinusSrcAlpha:
        return vk::BlendFactor::eOneMinusSrcAlpha;
    case BlendFactor::DstAlpha:
        return vk::BlendFactor::eDstAlpha;
    case BlendFactor::OneMinusDstAlpha:
        return vk::BlendFactor::eOneMinusDstAlpha;
    case BlendFactor::DstColor:
        return vk::BlendFactor::eDstColor;
    case BlendFactor::OneMinusDstColor:
        return vk::BlendFactor::eOneMinusDstColor;
    case BlendFactor::SrcAlphaSaturate:
        return vk::BlendFactor::eSrcAlphaSaturate;
    case BlendFactor::ConstantColor:
        return vk::BlendFactor::eConstantColor;
    case BlendFactor::OneMinusConstantColor:
        return vk::BlendFactor::eOneMinusConstantColor;
    case BlendFactor::Src1Color:
        return vk::BlendFactor::eSrc1Color;
    case BlendFactor::InvSrc1Color:
        return vk::BlendFactor::eOneMinusSrc1Color;
    case BlendFactor::Src1Alpha:
        return vk::BlendFactor::eSrc1Alpha;
    case BlendFactor::InvSrc1Alpha:
        return vk::BlendFactor::eOneMinusSrc1Alpha;
    case BlendFactor::ConstantAlpha:
        return vk::BlendFactor::eConstantAlpha;
    case BlendFactor::OneMinusConstantAlpha:
        return vk::BlendFactor::eOneMinusConstantAlpha;
    default:
        UNREACHABLE();
    }
}

vk::BlendOp BlendOp(Liverpool::BlendControl::BlendFunc func) {
    using BlendFunc = Liverpool::BlendControl::BlendFunc;
    switch (func) {
    case BlendFunc::Add:
        return vk::BlendOp::eAdd;
    case BlendFunc::Subtract:
        return vk::BlendOp::eSubtract;
    case BlendFunc::Min:
        return vk::BlendOp::eMin;
    case BlendFunc::Max:
        return vk::BlendOp::eMax;
    case BlendFunc::ReverseSubtract:
        return vk::BlendOp::eReverseSubtract;
    default:
        UNREACHABLE();
    }
}

// https://github.com/chaotic-cx/mesa-mirror/blob/0954afff5/src/amd/vulkan/radv_sampler.c#L21
vk::SamplerAddressMode ClampMode(AmdGpu::ClampMode mode) {
    switch (mode) {
    case AmdGpu::ClampMode::Wrap:
        return vk::SamplerAddressMode::eRepeat;
    case AmdGpu::ClampMode::Mirror:
        return vk::SamplerAddressMode::eMirroredRepeat;
    case AmdGpu::ClampMode::ClampLastTexel:
        return vk::SamplerAddressMode::eClampToEdge;
    case AmdGpu::ClampMode::MirrorOnceHalfBorder:
    case AmdGpu::ClampMode::MirrorOnceBorder:
        LOG_WARNING(Render_Vulkan, "Unimplemented clamp mode {}, using closest equivalent.",
                    static_cast<u32>(mode));
        [[fallthrough]];
    case AmdGpu::ClampMode::MirrorOnceLastTexel:
        return vk::SamplerAddressMode::eMirrorClampToEdge;
    case AmdGpu::ClampMode::ClampHalfBorder:
        LOG_WARNING(Render_Vulkan, "Unimplemented clamp mode {}, using closest equivalent.",
                    static_cast<u32>(mode));
        [[fallthrough]];
    case AmdGpu::ClampMode::ClampBorder:
        return vk::SamplerAddressMode::eClampToBorder;
    default:
        UNREACHABLE();
    }
}

vk::CompareOp DepthCompare(AmdGpu::DepthCompare comp) {
    switch (comp) {
    case AmdGpu::DepthCompare::Never:
        return vk::CompareOp::eNever;
    case AmdGpu::DepthCompare::Less:
        return vk::CompareOp::eLess;
    case AmdGpu::DepthCompare::Equal:
        return vk::CompareOp::eEqual;
    case AmdGpu::DepthCompare::LessEqual:
        return vk::CompareOp::eLessOrEqual;
    case AmdGpu::DepthCompare::Greater:
        return vk::CompareOp::eGreater;
    case AmdGpu::DepthCompare::NotEqual:
        return vk::CompareOp::eNotEqual;
    case AmdGpu::DepthCompare::GreaterEqual:
        return vk::CompareOp::eGreaterOrEqual;
    case AmdGpu::DepthCompare::Always:
        return vk::CompareOp::eAlways;
    default:
        UNREACHABLE();
    }
}

vk::Filter Filter(AmdGpu::Filter filter) {
    switch (filter) {
    case AmdGpu::Filter::Point:
    case AmdGpu::Filter::AnisoPoint:
        return vk::Filter::eNearest;
    case AmdGpu::Filter::Bilinear:
    case AmdGpu::Filter::AnisoLinear:
        return vk::Filter::eLinear;
    default:
        UNREACHABLE();
    }
}

vk::SamplerReductionMode FilterMode(AmdGpu::FilterMode mode) {
    switch (mode) {
    case AmdGpu::FilterMode::Blend:
        return vk::SamplerReductionMode::eWeightedAverage;
    case AmdGpu::FilterMode::Min:
        return vk::SamplerReductionMode::eMin;
    case AmdGpu::FilterMode::Max:
        return vk::SamplerReductionMode::eMax;
    default:
        UNREACHABLE();
    }
}

vk::SamplerMipmapMode MipFilter(AmdGpu::MipFilter filter) {
    switch (filter) {
    case AmdGpu::MipFilter::Point:
        return vk::SamplerMipmapMode::eNearest;
    case AmdGpu::MipFilter::Linear:
        return vk::SamplerMipmapMode::eLinear;
    case AmdGpu::MipFilter::None:
        return vk::SamplerMipmapMode::eNearest;
    default:
        UNREACHABLE();
    }
}

vk::BorderColor BorderColor(AmdGpu::BorderColor color) {
    switch (color) {
    case AmdGpu::BorderColor::OpaqueBlack:
        return vk::BorderColor::eFloatOpaqueBlack;
    case AmdGpu::BorderColor::TransparentBlack:
        return vk::BorderColor::eFloatTransparentBlack;
    case AmdGpu::BorderColor::White:
        return vk::BorderColor::eFloatOpaqueWhite;
    case AmdGpu::BorderColor::Custom:
        return vk::BorderColor::eFloatCustomEXT;
    default:
        UNREACHABLE();
    }
}

static constexpr vk::FormatFeatureFlags2 BufferRead =
    vk::FormatFeatureFlagBits2::eUniformTexelBuffer | vk::FormatFeatureFlagBits2::eVertexBuffer;
static constexpr vk::FormatFeatureFlags2 BufferWrite =
    vk::FormatFeatureFlagBits2::eStorageTexelBuffer |
    vk::FormatFeatureFlagBits2::eStorageReadWithoutFormat |
    vk::FormatFeatureFlagBits2::eStorageWriteWithoutFormat;
static constexpr vk::FormatFeatureFlags2 ImageRead = vk::FormatFeatureFlagBits2::eTransferSrc |
                                                     vk::FormatFeatureFlagBits2::eTransferDst |
                                                     vk::FormatFeatureFlagBits2::eSampledImage;
static constexpr vk::FormatFeatureFlags2 ImageWrite =
    vk::FormatFeatureFlagBits2::eStorageImage |
    vk::FormatFeatureFlagBits2::eStorageReadWithoutFormat |
    vk::FormatFeatureFlagBits2::eStorageWriteWithoutFormat;
static constexpr vk::FormatFeatureFlags2 Mrt = vk::FormatFeatureFlagBits2::eColorAttachment;

// Table 8.13 Data and Image Formats [Sea Islands Series Instruction Set Architecture]
static constexpr vk::FormatFeatureFlags2 GetDataFormatFeatureFlags(
    const AmdGpu::DataFormat data_format) {
    switch (data_format) {
    case AmdGpu::DataFormat::FormatInvalid:
    case AmdGpu::DataFormat::Format8:
    case AmdGpu::DataFormat::Format16:
    case AmdGpu::DataFormat::Format8_8:
    case AmdGpu::DataFormat::Format32:
    case AmdGpu::DataFormat::Format16_16:
    case AmdGpu::DataFormat::Format10_11_11:
    case AmdGpu::DataFormat::Format11_11_10:
    case AmdGpu::DataFormat::Format10_10_10_2:
    case AmdGpu::DataFormat::Format2_10_10_10:
    case AmdGpu::DataFormat::Format8_8_8_8:
    case AmdGpu::DataFormat::Format32_32:
    case AmdGpu::DataFormat::Format16_16_16_16:
    case AmdGpu::DataFormat::Format32_32_32_32:
        return BufferRead | BufferWrite | ImageRead | ImageWrite | Mrt;
    case AmdGpu::DataFormat::Format32_32_32:
        return BufferRead | BufferWrite | ImageRead;
    case AmdGpu::DataFormat::Format5_6_5:
    case AmdGpu::DataFormat::Format1_5_5_5:
    case AmdGpu::DataFormat::Format5_5_5_1:
    case AmdGpu::DataFormat::Format4_4_4_4:
        return ImageRead | ImageWrite | Mrt;
    case AmdGpu::DataFormat::Format8_24:
    case AmdGpu::DataFormat::Format24_8:
    case AmdGpu::DataFormat::FormatX24_8_32:
        return ImageRead | Mrt;
    case AmdGpu::DataFormat::FormatGB_GR:
    case AmdGpu::DataFormat::FormatBG_RG:
    case AmdGpu::DataFormat::Format5_9_9_9:
    case AmdGpu::DataFormat::FormatBc1:
    case AmdGpu::DataFormat::FormatBc2:
    case AmdGpu::DataFormat::FormatBc3:
    case AmdGpu::DataFormat::FormatBc4:
    case AmdGpu::DataFormat::FormatBc5:
    case AmdGpu::DataFormat::FormatBc6:
    case AmdGpu::DataFormat::FormatBc7:
    case AmdGpu::DataFormat::Format4_4:
    case AmdGpu::DataFormat::Format6_5_5:
    case AmdGpu::DataFormat::Format1:
    case AmdGpu::DataFormat::Format1_Reversed:
    case AmdGpu::DataFormat::Format32_As_8:
    case AmdGpu::DataFormat::Format32_As_8_8:
    case AmdGpu::DataFormat::Format32_As_32_32_32_32:
        return ImageRead;
    case AmdGpu::DataFormat::FormatFmask8_1:
    case AmdGpu::DataFormat::FormatFmask8_2:
    case AmdGpu::DataFormat::FormatFmask8_4:
    case AmdGpu::DataFormat::FormatFmask16_1:
    case AmdGpu::DataFormat::FormatFmask16_2:
    case AmdGpu::DataFormat::FormatFmask32_2:
    case AmdGpu::DataFormat::FormatFmask32_4:
    case AmdGpu::DataFormat::FormatFmask32_8:
    case AmdGpu::DataFormat::FormatFmask64_4:
    case AmdGpu::DataFormat::FormatFmask64_8:
        return ImageRead | ImageWrite;
    }
    UNREACHABLE_MSG("Missing feature flags for data format {}", static_cast<u32>(data_format));
}

// Table 8.13 Data and Image Formats [Sea Islands Series Instruction Set Architecture]
static constexpr vk::FormatFeatureFlags2 GetNumberFormatFeatureFlags(
    const AmdGpu::NumberFormat number_format) {
    switch (number_format) {
    case AmdGpu::NumberFormat::Unorm:
    case AmdGpu::NumberFormat::Snorm:
    case AmdGpu::NumberFormat::Uint:
    case AmdGpu::NumberFormat::Sint:
    case AmdGpu::NumberFormat::Float:
        return BufferRead | BufferWrite | ImageRead | ImageWrite | Mrt;
    case AmdGpu::NumberFormat::Uscaled:
    case AmdGpu::NumberFormat::Sscaled:
    case AmdGpu::NumberFormat::SnormNz:
        return BufferRead | ImageRead;
    case AmdGpu::NumberFormat::Srgb:
        return ImageRead | Mrt;
    case AmdGpu::NumberFormat::Ubnorm:
    case AmdGpu::NumberFormat::UbnromNz:
    case AmdGpu::NumberFormat::Ubint:
    case AmdGpu::NumberFormat::Ubscaled:
        return ImageRead;
    }
    UNREACHABLE_MSG("Missing feature flags for number format {}", static_cast<u32>(number_format));
}

static constexpr SurfaceFormatInfo CreateSurfaceFormatInfo(const AmdGpu::DataFormat data_format,
                                                           const AmdGpu::NumberFormat number_format,
                                                           const vk::Format vk_format) {
    return {
        .data_format = data_format,
        .number_format = number_format,
        .vk_format = vk_format,
        .flags =
            GetDataFormatFeatureFlags(data_format) & GetNumberFormatFeatureFlags(number_format),
    };
}

std::span<const SurfaceFormatInfo> SurfaceFormats() {
    static constexpr std::array formats{
        // Invalid
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatInvalid, AmdGpu::NumberFormat::Unorm,
                                vk::Format::eUndefined),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatInvalid, AmdGpu::NumberFormat::Snorm,
                                vk::Format::eUndefined),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatInvalid, AmdGpu::NumberFormat::Uscaled,
                                vk::Format::eUndefined),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatInvalid, AmdGpu::NumberFormat::Sscaled,
                                vk::Format::eUndefined),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatInvalid, AmdGpu::NumberFormat::Uint,
                                vk::Format::eUndefined),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatInvalid, AmdGpu::NumberFormat::Sint,
                                vk::Format::eUndefined),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatInvalid, AmdGpu::NumberFormat::SnormNz,
                                vk::Format::eUndefined),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatInvalid, AmdGpu::NumberFormat::Float,
                                vk::Format::eUndefined),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatInvalid, AmdGpu::NumberFormat::Srgb,
                                vk::Format::eUndefined),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatInvalid, AmdGpu::NumberFormat::Ubnorm,
                                vk::Format::eUndefined),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatInvalid, AmdGpu::NumberFormat::UbnromNz,
                                vk::Format::eUndefined),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatInvalid, AmdGpu::NumberFormat::Ubint,
                                vk::Format::eUndefined),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatInvalid, AmdGpu::NumberFormat::Ubscaled,
                                vk::Format::eUndefined),
        // 8
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format8, AmdGpu::NumberFormat::Unorm,
                                vk::Format::eR8Unorm),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format8, AmdGpu::NumberFormat::Snorm,
                                vk::Format::eR8Snorm),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format8, AmdGpu::NumberFormat::Uint,
                                vk::Format::eR8Uint),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format8, AmdGpu::NumberFormat::Sint,
                                vk::Format::eR8Sint),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format8, AmdGpu::NumberFormat::Srgb,
                                vk::Format::eR8Srgb),
        // 16
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format16, AmdGpu::NumberFormat::Unorm,
                                vk::Format::eR16Unorm),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format16, AmdGpu::NumberFormat::Snorm,
                                vk::Format::eR16Snorm),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format16, AmdGpu::NumberFormat::Uint,
                                vk::Format::eR16Uint),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format16, AmdGpu::NumberFormat::Sint,
                                vk::Format::eR16Sint),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format16, AmdGpu::NumberFormat::Float,
                                vk::Format::eR16Sfloat),
        // 8_8
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format8_8, AmdGpu::NumberFormat::Unorm,
                                vk::Format::eR8G8Unorm),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format8_8, AmdGpu::NumberFormat::Snorm,
                                vk::Format::eR8G8Snorm),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format8_8, AmdGpu::NumberFormat::Uint,
                                vk::Format::eR8G8Uint),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format8_8, AmdGpu::NumberFormat::Sint,
                                vk::Format::eR8G8Sint),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format8_8, AmdGpu::NumberFormat::Srgb,
                                vk::Format::eR8G8Srgb),
        // 32
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format32, AmdGpu::NumberFormat::Uint,
                                vk::Format::eR32Uint),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format32, AmdGpu::NumberFormat::Sint,
                                vk::Format::eR32Sint),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format32, AmdGpu::NumberFormat::Float,
                                vk::Format::eR32Sfloat),
        // 16_16
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format16_16, AmdGpu::NumberFormat::Unorm,
                                vk::Format::eR16G16Unorm),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format16_16, AmdGpu::NumberFormat::Snorm,
                                vk::Format::eR16G16Snorm),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format16_16, AmdGpu::NumberFormat::Uscaled,
                                vk::Format::eR16G16Uscaled),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format16_16, AmdGpu::NumberFormat::Sscaled,
                                vk::Format::eR16G16Sscaled),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format16_16, AmdGpu::NumberFormat::Uint,
                                vk::Format::eR16G16Uint),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format16_16, AmdGpu::NumberFormat::Sint,
                                vk::Format::eR16G16Sint),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format16_16, AmdGpu::NumberFormat::Float,
                                vk::Format::eR16G16Sfloat),
        // 10_11_11
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format10_11_11, AmdGpu::NumberFormat::Float,
                                vk::Format::eB10G11R11UfloatPack32),
        // 11_11_10
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format11_11_10, AmdGpu::NumberFormat::Float,
                                vk::Format::eB10G11R11UfloatPack32),
        // 10_10_10_2
        // 2_10_10_10
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format2_10_10_10, AmdGpu::NumberFormat::Unorm,
                                vk::Format::eA2B10G10R10UnormPack32),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format2_10_10_10, AmdGpu::NumberFormat::Snorm,
                                vk::Format::eA2B10G10R10SnormPack32),
        // 8_8_8_8
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format8_8_8_8, AmdGpu::NumberFormat::Unorm,
                                vk::Format::eR8G8B8A8Unorm),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format8_8_8_8, AmdGpu::NumberFormat::Snorm,
                                vk::Format::eR8G8B8A8Snorm),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format8_8_8_8, AmdGpu::NumberFormat::Uscaled,
                                vk::Format::eR8G8B8A8Uscaled),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format8_8_8_8, AmdGpu::NumberFormat::Sscaled,
                                vk::Format::eR8G8B8A8Sscaled),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format8_8_8_8, AmdGpu::NumberFormat::Uint,
                                vk::Format::eR8G8B8A8Uint),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format8_8_8_8, AmdGpu::NumberFormat::Sint,
                                vk::Format::eR8G8B8A8Sint),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format8_8_8_8, AmdGpu::NumberFormat::Srgb,
                                vk::Format::eR8G8B8A8Srgb),
        // 32_32
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format32_32, AmdGpu::NumberFormat::Uint,
                                vk::Format::eR32G32Uint),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format32_32, AmdGpu::NumberFormat::Sint,
                                vk::Format::eR32G32Sint),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format32_32, AmdGpu::NumberFormat::Float,
                                vk::Format::eR32G32Sfloat),
        // 16_16_16_16
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format16_16_16_16, AmdGpu::NumberFormat::Unorm,
                                vk::Format::eR16G16B16A16Unorm),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format16_16_16_16, AmdGpu::NumberFormat::Snorm,
                                vk::Format::eR16G16B16A16Snorm),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format16_16_16_16,
                                AmdGpu::NumberFormat::Uscaled, vk::Format::eR16G16B16A16Uscaled),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format16_16_16_16,
                                AmdGpu::NumberFormat::Sscaled, vk::Format::eR16G16B16A16Sscaled),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format16_16_16_16, AmdGpu::NumberFormat::Uint,
                                vk::Format::eR16G16B16A16Uint),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format16_16_16_16, AmdGpu::NumberFormat::Sint,
                                vk::Format::eR16G16B16A16Sint),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format16_16_16_16,
                                AmdGpu::NumberFormat::SnormNz, vk::Format::eR16G16B16A16Snorm),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format16_16_16_16, AmdGpu::NumberFormat::Float,
                                vk::Format::eR16G16B16A16Sfloat),
        // 32_32_32
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format32_32_32, AmdGpu::NumberFormat::Uint,
                                vk::Format::eR32G32B32Uint),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format32_32_32, AmdGpu::NumberFormat::Sint,
                                vk::Format::eR32G32B32Sint),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format32_32_32, AmdGpu::NumberFormat::Float,
                                vk::Format::eR32G32B32Sfloat),
        // 32_32_32_32
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format32_32_32_32, AmdGpu::NumberFormat::Uint,
                                vk::Format::eR32G32B32A32Uint),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format32_32_32_32, AmdGpu::NumberFormat::Sint,
                                vk::Format::eR32G32B32A32Sint),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format32_32_32_32, AmdGpu::NumberFormat::Float,
                                vk::Format::eR32G32B32A32Sfloat),
        // 5_6_5
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format5_6_5, AmdGpu::NumberFormat::Unorm,
                                vk::Format::eB5G6R5UnormPack16),
        // 1_5_5_5
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format1_5_5_5, AmdGpu::NumberFormat::Unorm,
                                vk::Format::eR5G5B5A1UnormPack16),
        // 5_5_5_1
        // 4_4_4_4
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format4_4_4_4, AmdGpu::NumberFormat::Unorm,
                                vk::Format::eR4G4B4A4UnormPack16),
        // 8_24
        // 24_8
        // X24_8_32
        // GB_GR
        // BG_RG
        // 5_9_9_9
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::Format5_9_9_9, AmdGpu::NumberFormat::Float,
                                vk::Format::eE5B9G9R9UfloatPack32),
        // BC1
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatBc1, AmdGpu::NumberFormat::Unorm,
                                vk::Format::eBc1RgbaUnormBlock),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatBc1, AmdGpu::NumberFormat::Srgb,
                                vk::Format::eBc1RgbaSrgbBlock),
        // BC2
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatBc2, AmdGpu::NumberFormat::Unorm,
                                vk::Format::eBc2UnormBlock),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatBc2, AmdGpu::NumberFormat::Srgb,
                                vk::Format::eBc2SrgbBlock),
        // BC3
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatBc3, AmdGpu::NumberFormat::Unorm,
                                vk::Format::eBc3UnormBlock),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatBc3, AmdGpu::NumberFormat::Srgb,
                                vk::Format::eBc3SrgbBlock),
        // BC4
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatBc4, AmdGpu::NumberFormat::Unorm,
                                vk::Format::eBc4UnormBlock),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatBc4, AmdGpu::NumberFormat::Snorm,
                                vk::Format::eBc4SnormBlock),
        // BC5
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatBc5, AmdGpu::NumberFormat::Unorm,
                                vk::Format::eBc5UnormBlock),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatBc5, AmdGpu::NumberFormat::Snorm,
                                vk::Format::eBc5SnormBlock),
        // BC6
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatBc6, AmdGpu::NumberFormat::Unorm,
                                vk::Format::eBc6HUfloatBlock),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatBc6, AmdGpu::NumberFormat::Snorm,
                                vk::Format::eBc6HSfloatBlock),
        // BC7
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatBc7, AmdGpu::NumberFormat::Unorm,
                                vk::Format::eBc7UnormBlock),
        CreateSurfaceFormatInfo(AmdGpu::DataFormat::FormatBc7, AmdGpu::NumberFormat::Srgb,
                                vk::Format::eBc7SrgbBlock),
    };
    return formats;
}

vk::Format SurfaceFormat(AmdGpu::DataFormat data_format, AmdGpu::NumberFormat num_format) {
    const auto& formats = SurfaceFormats();
    const auto format =
        std::find_if(formats.begin(), formats.end(), [&](const SurfaceFormatInfo& format_info) {
            return format_info.data_format == data_format &&
                   format_info.number_format == num_format;
        });
    ASSERT_MSG(format != formats.end(), "Unknown data_format={} and num_format={}",
               static_cast<u32>(data_format), static_cast<u32>(num_format));
    return format->vk_format;
}

vk::Format AdjustColorBufferFormat(vk::Format base_format,
                                   Liverpool::ColorBuffer::SwapMode comp_swap, bool is_vo_surface) {
    const bool comp_swap_alt = comp_swap == Liverpool::ColorBuffer::SwapMode::Alternate;
    const bool comp_swap_reverse = comp_swap == Liverpool::ColorBuffer::SwapMode::StandardReverse;
    const bool comp_swap_alt_reverse =
        comp_swap == Liverpool::ColorBuffer::SwapMode::AlternateReverse;
    if (comp_swap_alt) {
        switch (base_format) {
        case vk::Format::eR8G8B8A8Unorm:
            return vk::Format::eB8G8R8A8Unorm;
        case vk::Format::eB8G8R8A8Unorm:
            return vk::Format::eR8G8B8A8Unorm;
        case vk::Format::eR8G8B8A8Srgb:
            return is_vo_surface ? vk::Format::eB8G8R8A8Unorm : vk::Format::eB8G8R8A8Srgb;
        case vk::Format::eB8G8R8A8Srgb:
            return is_vo_surface ? vk::Format::eR8G8B8A8Unorm : vk::Format::eR8G8B8A8Srgb;
        case vk::Format::eA2B10G10R10UnormPack32:
            return vk::Format::eA2R10G10B10UnormPack32;
        default:
            break;
        }
    } else if (comp_swap_reverse) {
        switch (base_format) {
        case vk::Format::eR8G8B8A8Unorm:
            return vk::Format::eA8B8G8R8UnormPack32;
        case vk::Format::eR8G8B8A8Srgb:
            return is_vo_surface ? vk::Format::eA8B8G8R8UnormPack32
                                 : vk::Format::eA8B8G8R8SrgbPack32;
        default:
            break;
        }
    } else if (comp_swap_alt_reverse) {
        return base_format;
    } else {
        if (is_vo_surface && base_format == vk::Format::eR8G8B8A8Srgb) {
            return vk::Format::eR8G8B8A8Unorm;
        }
        if (is_vo_surface && base_format == vk::Format::eB8G8R8A8Srgb) {
            return vk::Format::eB8G8R8A8Unorm;
        }
    }
    return base_format;
}

static constexpr DepthFormatInfo CreateDepthFormatInfo(
    const DepthBuffer::ZFormat z_format, const DepthBuffer::StencilFormat stencil_format,
    const vk::Format vk_format) {
    return {
        .z_format = z_format,
        .stencil_format = stencil_format,
        .vk_format = vk_format,
        .flags = vk::FormatFeatureFlagBits2::eDepthStencilAttachment,
    };
}

std::span<const DepthFormatInfo> DepthFormats() {
    using ZFormat = DepthBuffer::ZFormat;
    using StencilFormat = DepthBuffer::StencilFormat;
    static constexpr std::array formats{
        // Invalid
        CreateDepthFormatInfo(ZFormat::Invalid, StencilFormat::Invalid, vk::Format::eUndefined),
        CreateDepthFormatInfo(ZFormat::Invalid, StencilFormat::Stencil8,
                              vk::Format::eD32SfloatS8Uint),
        // 16
        CreateDepthFormatInfo(ZFormat::Z16, StencilFormat::Invalid, vk::Format::eD16Unorm),
        CreateDepthFormatInfo(ZFormat::Z16, StencilFormat::Stencil8, vk::Format::eD16UnormS8Uint),
        // 32_Float
        CreateDepthFormatInfo(ZFormat::Z32Float, StencilFormat::Invalid, vk::Format::eD32Sfloat),
        CreateDepthFormatInfo(ZFormat::Z32Float, StencilFormat::Stencil8,
                              vk::Format::eD32SfloatS8Uint),
    };
    return formats;
}

vk::Format DepthFormat(DepthBuffer::ZFormat z_format, DepthBuffer::StencilFormat stencil_format) {
    const auto& formats = DepthFormats();
    const auto format =
        std::find_if(formats.begin(), formats.end(), [&](const DepthFormatInfo& format_info) {
            return format_info.z_format == z_format && format_info.stencil_format == stencil_format;
        });
    ASSERT_MSG(format != formats.end(), "Unknown z_format={} and stencil_format={}",
               static_cast<u32>(z_format), static_cast<u32>(stencil_format));
    return format->vk_format;
}

void EmitQuadToTriangleListIndices(u8* out_ptr, u32 num_vertices) {
    static constexpr u16 NumVerticesPerQuad = 4;
    u16* out_data = reinterpret_cast<u16*>(out_ptr);
    for (u16 i = 0; i < num_vertices; i += NumVerticesPerQuad) {
        *out_data++ = i;
        *out_data++ = i + 1;
        *out_data++ = i + 2;
        *out_data++ = i;
        *out_data++ = i + 2;
        *out_data++ = i + 3;
    }
}

static constexpr float U8ToUnorm(u8 v) {
    static constexpr auto c = 1.0f / 255.0f;
    return float(v * c);
}

vk::ClearValue ColorBufferClearValue(const AmdGpu::Liverpool::ColorBuffer& color_buffer) {
    const auto comp_swap = color_buffer.info.comp_swap.Value();
    ASSERT_MSG(comp_swap == Liverpool::ColorBuffer::SwapMode::Standard ||
                   comp_swap == Liverpool::ColorBuffer::SwapMode::Alternate,
               "Unsupported component swap mode {}", static_cast<u32>(comp_swap));

    const bool comp_swap_alt = comp_swap == Liverpool::ColorBuffer::SwapMode::Alternate;

    const auto& c0 = color_buffer.clear_word0;
    const auto& c1 = color_buffer.clear_word1;
    const auto num_bits = AmdGpu::NumBits(color_buffer.info.format);

    vk::ClearColorValue color{};
    switch (color_buffer.info.number_type) {
    case AmdGpu::NumberFormat::Snorm:
        [[fallthrough]];
    case AmdGpu::NumberFormat::SnormNz:
        [[fallthrough]];
    case AmdGpu::NumberFormat::Unorm:
        [[fallthrough]];
    case AmdGpu::NumberFormat::Srgb: {
        switch (num_bits) {
        case 32: {
            color.float32 = std::array{
                U8ToUnorm((c0 >> (comp_swap_alt ? 16 : 0)) & 0xff),
                U8ToUnorm((c0 >> 8) & 0xff),
                U8ToUnorm((c0 >> (comp_swap_alt ? 0 : 16)) & 0xff),
                U8ToUnorm((c0 >> 24) & 0xff),
            };
            break;
        }
        default: {
            LOG_ERROR(Render_Vulkan, "Missing clear color conversion for bits {}", num_bits);
            break;
        }
        }
        break;
    }
    default: {
        LOG_ERROR(Render_Vulkan, "Missing clear color conversion for type {}",
                  color_buffer.info.number_type.Value());
        break;
    }
    }
    return {.color = color};
}

vk::SampleCountFlagBits RawNumSamples(u32 num_samples) {
    switch (num_samples) {
    case 1:
        return vk::SampleCountFlagBits::e1;
    case 2:
        return vk::SampleCountFlagBits::e2;
    case 4:
        return vk::SampleCountFlagBits::e4;
    case 8:
        return vk::SampleCountFlagBits::e8;
    case 16:
        return vk::SampleCountFlagBits::e16;
    default:
        UNREACHABLE();
    }
}

vk::SampleCountFlagBits NumSamples(u32 num_samples, vk::SampleCountFlags supported_flags) {
    vk::SampleCountFlagBits flags = RawNumSamples(num_samples);
    // Half sample counts until supported, with a minimum of 1.
    while (!(supported_flags & flags) && num_samples > 1) {
        num_samples /= 2;
        flags = RawNumSamples(num_samples);
    }
    return flags;
}

} // namespace Vulkan::LiverpoolToVK
