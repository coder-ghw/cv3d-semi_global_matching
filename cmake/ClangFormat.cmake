# Find Clang format
if(NOT CLANG_FORMAT_BIN_NAME)
    set(CLANG_FORMAT_BIN_NAME clang-format)
endif()

if(NOT GIT_CLANG_FORMAT_BIN_NAME)
    set(GIT_CLANG_FORMAT_BIN_NAME git-clang-format)
endif()

# if custom path check there first
if(CLANG_FORMAT_ROOT_DIR)
    find_program(CLANG_FORMAT_BIN 
        NAMES
        ${CLANG_FORMAT_BIN_NAME}
        PATHS
        "${CLANG_FORMAT_ROOT_DIR}"
        NO_DEFAULT_PATH)
endif()
if(GIT_CLANG_FORMAT_ROOT_DIR)
    find_program(GIT_CLANG_FORMAT_BIN 
        NAMES
        ${GIT_CLANG_FORMAT_BIN_NAME}
        PATHS
        "${GIT_CLANG_FORMAT_ROOT_DIR}"
        NO_DEFAULT_PATH)
endif()

find_program(CLANG_FORMAT_BIN NAMES ${CLANG_FORMAT_BIN_NAME})
find_program(GIT_CLANG_FORMAT_BIN NAMES ${GIT_CLANG_FORMAT_BIN_NAME})

# It also sets the <PackageName>_FOUND variable. 
# The package is considered found if all variables listed contain valid results, e.g. valid filepaths.
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(
    CLANG_FORMAT
    DEFAULT_MSG 
    CLANG_FORMAT_BIN
    GIT_CLANG_FORMAT_BIN
    )

mark_as_advanced(
    CLANG_FORMAT_BIN)

if(CLANG_FORMAT_FOUND)
    message(STATUS "Found clang-format: ${CLANG_FORMAT_BIN}")
    message(STATUS "Found git-clang-format: ${GIT_CLANG_FORMAT_BIN}")
else()
    message("clang-format not found. Not setting up format targets")
endif()

add_custom_target(format
    COMMAND git add -u
    COMMAND python ${GIT_CLANG_FORMAT_BIN} --binary ${CLANG_FORMAT_BIN} `git rev-parse --verify origin/main`
    COMMAND git add -u
    COMMAND git commit -m "[format code]Formatting"
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)
