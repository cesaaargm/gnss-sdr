// SPDX-FileCopyrightText: 2017 Google LLC
// SPDX-License-Identifier: Apache-2.0

#include "cpu_features_macros.h"

#ifdef CPU_FEATURES_ARCH_X86
#ifdef CPU_FEATURES_OS_WINDOWS

#include "impl_x86__base_implementation.inl"

static void OverrideOsPreserves(OsPreserves* os_preserves)
{
    (void)os_preserves;
    // No override
}

#include <windows.h>  // IsProcessorFeaturePresent

#if defined(CPU_FEATURES_MOCK_CPUID_X86)
extern bool GetWindowsIsProcessorFeaturePresent(DWORD);
#else  // CPU_FEATURES_MOCK_CPUID_X86
static bool GetWindowsIsProcessorFeaturePresent(DWORD ProcessorFeature)
{
    return IsProcessorFeaturePresent(ProcessorFeature);
}
#endif

static void DetectFeaturesFromOs(X86Features* features)
{
    // Handling Windows platform through IsProcessorFeaturePresent.
    // https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-isprocessorfeaturepresent
    features->sse =
        GetWindowsIsProcessorFeaturePresent(PF_XMMI_INSTRUCTIONS_AVAILABLE);
    features->sse2 =
        GetWindowsIsProcessorFeaturePresent(PF_XMMI64_INSTRUCTIONS_AVAILABLE);
    features->sse3 =
        GetWindowsIsProcessorFeaturePresent(PF_SSE3_INSTRUCTIONS_AVAILABLE);
}

#endif  // CPU_FEATURES_OS_WINDOWS
#endif  // CPU_FEATURES_ARCH_X86
