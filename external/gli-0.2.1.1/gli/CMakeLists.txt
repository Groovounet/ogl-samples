set(NAME gli)

file(GLOB ROOT_SOURCE *.cpp)
file(GLOB ROOT_INLINE *.inl)
file(GLOB ROOT_HEADER *.hpp)

file(GLOB_RECURSE CORE_SOURCE ./core/*.cpp)
file(GLOB_RECURSE CORE_INLINE ./core/*.inl)
file(GLOB_RECURSE CORE_HEADER ./core/*.hpp)

source_group("Inline Files" FILES ${CORE_INLINE})

include_directories(..)

add_executable(${NAME} 
	${ROOT_SOURCE}    ${ROOT_INLINE}    ${ROOT_HEADER} 
	${CORE_SOURCE}    ${CORE_INLINE}    ${CORE_HEADER})
