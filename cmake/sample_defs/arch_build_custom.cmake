#
# Example arch_build_custom.cmake
# -------------------------------
#
# This file will be automatically included in the arch-specific build scope
#
# Definitions and options specified here will be used when cross-compiling
# _all_ FSW code for _all_ targets defined in targets.cmake.
#
# Avoid machine-specific code generation options in this file (e.g. -f,-m options);
# such options should be localized to the toolchain file such that they will only be
# included on the machines where they apply.
#
# CAUTION: In heterogeneous environments where different cross compilers are
# used for different CPUs, particularly if from different vendors, it is likely
# that compile options will need to be different as well.
#
# In general, options in this file can only be used in cases where all CPUs use a
# compiler from the same vendor and/or are all GCC based such that they accept similar
# command line options.
#
# This file can alternatively be named as "arch_build_custom_${TARGETSYSTEM}.cmake"
# where ${TARGETSYSTEM} represents the system type, matching the toolchain.
#
# These example options assume a GCC-style toolchain is used for cross compilation,
# and uses the same warning options that are applied at the mission level.
#
# 1) For Clang-based toolchains (e.g., afl-clang-lto), strip any leftover
#    -Wno-stringop-truncation before compilation.
#    Also silence unknown-warning-option warnings and errors.
if(CMAKE_C_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # Remove stray GCC-only flag
  string(REPLACE "-Wno-stringop-truncation" "" CMAKE_C_FLAGS  "${CMAKE_C_FLAGS}")
  string(REPLACE "-Wno-stringop-truncation" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

  add_compile_options(
    -Wno-unknown-warning-option      # Silence warnings about unknown warning flags
    -Wno-error=unknown-warning-option # Never treat unknown-warning-option as an error
  )
endif()

# 2) Define common C compilation flags for all compilers
set(CFE_COMMON_FLAGS
    -std=c99                    # Target the C99 standard (without gcc extensions)
    -pedantic                   # Issue all the warnings demanded by strict ISO C
    -Wall                       # Warn about most questionable operations
    -Wstrict-prototypes         # Warn about missing prototypes
    -Wwrite-strings             # Warn if not treating string literals as "const"
    -Wpointer-arith             # Warn about suspicious pointer operations
    -Werror                     # Treat warnings as errors (code should be clean)
    -Wno-format-truncation      # Inhibit printf-style format-truncation warnings
)
add_compile_options(${CFE_COMMON_FLAGS})

# 3) Suppress stringop-truncation only under genuine GNU compilers
if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_compile_options(
    -Wno-stringop-truncation    # Inhibit string operation truncation warnings under GCC
  )
endif()
