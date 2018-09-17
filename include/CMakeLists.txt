#   add headers

file(GLOB SUB_HEADERS "*.hpp")

set(LIBRARY_SOURCES
    ${LIBRARY_SOURCES}
    ${SUB_HEADERS}
    PARENT_SCOPE)

