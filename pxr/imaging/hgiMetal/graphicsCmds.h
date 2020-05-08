//
// Copyright 2020 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#ifndef PXR_IMAGING_HGI_METAL_GRAPHICS_ENCODER_H
#define PXR_IMAGING_HGI_METAL_GRAPHICS_ENCODER_H

#include "pxr/pxr.h"
#include "pxr/base/gf/vec4i.h"
#include "pxr/imaging/hgiMetal/api.h"
#include "pxr/imaging/hgi/graphicsCmds.h"
#include <cstdint>

#include <Metal/Metal.h>

PXR_NAMESPACE_OPEN_SCOPE

struct HgiGraphicsCmdsDesc;


/// \class HgiMetalGraphicsCmds
///
/// Metalk implementation of HgiGraphicsEncoder.
///
class HgiMetalGraphicsCmds final : public HgiGraphicsCmds
{
public:
    HGIMETAL_API
    ~HgiMetalGraphicsCmds() override;

    HGIMETAL_API
    void SetViewport(GfVec4i const& vp) override;

    HGIMETAL_API
    void SetScissor(GfVec4i const& sc) override;

    HGIMETAL_API
    void BindPipeline(HgiPipelineHandle pipeline) override;

    HGIMETAL_API
    void BindResources(HgiResourceBindingsHandle resources) override;

    HGIMETAL_API
    void BindVertexBuffers(
        uint32_t firstBinding,
        HgiBufferHandleVector const& buffers,
        std::vector<uint32_t> const& byteOffsets) override;

    HGIMETAL_API
    void DrawIndexed(
        HgiBufferHandle const& indexBuffer,
        uint32_t indexCount,
        uint32_t indexBufferByteOffset,
        uint32_t firstIndex,
        uint32_t vertexOffset,
        uint32_t instanceCount) override;

    HGIMETAL_API
    void PushDebugGroup(const char* label) override;

    HGIMETAL_API
    void PopDebugGroup() override;

protected:
    friend class HgiMetal;

    HGIMETAL_API
    HgiMetalGraphicsCmds(
        HgiMetal* hgi,
        HgiGraphicsCmdsDesc const& desc);
    
    HGIMETAL_API
    bool Commit();
    
private:
    HgiMetalGraphicsCmds() = delete;
    HgiMetalGraphicsCmds & operator=(const HgiMetalGraphicsCmds&) = delete;
    HgiMetalGraphicsCmds(const HgiMetalGraphicsCmds&) = delete;

    HgiMetal* _hgi;
    id<MTLRenderCommandEncoder> _encoder;
    HgiGraphicsCmdsDesc _descriptor;
    bool _hasWork;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif