# Main tool of this project

set(BINARY_TARGET am64xx-reset-cause)
add_executable(${BINARY_TARGET} main.c am64xx/am64xx-reset-reg.c)
target_include_directories(am64xx-reset-cause PRIVATE am64xx-reset-reg)

set_target_properties(
  ${BINARY_TARGET}
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
             LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
             RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Use git to get version information
if(EXISTS "${PROJECT_SOURCE_DIR}/.git")
  set(GIT_DSC_CMD "git" describe --always --dirty --tags)
  execute_process(
    COMMAND ${GIT_DSC_CMD}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE CVS_GIT_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE)
else()
  set(CVS_GIT_VERSION "unset")
endif()

# Minimal compiler adjustments aligned to:
# https://developers.redhat.com/blog/2018/03/21/compiler-and-linker-flags-gcc
# Robert Seacords Effective C 2nd Edition
set(RECOMMENDED_CFLAGS
     -Wall
     -Wextra
     -Werror
     -Wformat-security
     -Wformat=2
     -Wconversion
     -Wstack-protector

     -pipe
     -pedantic

     -frecord-gcc-switches

     -mshstk
     -fsplit-stack
     -fstack-protector-all
     -fstack-clash-protection
     -D_FORTIFY_SOURCE=2

     -ftrapv
     -fanalyzer

     -fsanitize=address
     -fsanitize=undefined
     -fsanitize=bounds
)

set(RECOMMENDED_LDFLAGS
     -Wl,-z,defs
     -Wl,-z,now
     -Wl,-z,relro
     -Wl,-z,noexecstack
     -Wl,-pie
     -fsanitize=address
     -fsanitize=undefined
     -fsanitize=bounds
)

target_link_options(${BINARY_TARGET} PRIVATE
    ${RECOMMENDED_LDFLAGS}
)

target_compile_options(${BINARY_TARGET} PRIVATE
    -std=c23
    ${RECOMMENDED_CFLAGS}
    -DCVS_GIT_VERSION=\"${CVS_GIT_VERSION}\"

    #$<$<CONFIG:Debug>:>
    #$<$<CONFIG:Release>:>
)
