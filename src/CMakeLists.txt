file(GLOB_RECURSE SOURCE_FILES ./*.cpp)

add_executable(babyfoot ${SOURCE_FILES})

include(FetchContent)

#glfw
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.6
)

set(GLFW_BUILD_EXAMPLES false)
set(GLFW_BUILD_TESTS false)
set(GLFW_BUILD_DOCS false)
set(GLFW_INSTALL false)

FetchContent_MakeAvailable(glfw)

#glad
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v0.1.36
)

FetchContent_MakeAvailable(glad)

#glm
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8
)

FetchContent_MakeAvailable(glm)

#stb
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG af1a5bc352164740c1cc1354942b1c6b72eacb8a
)

FetchContent_MakeAvailable(stb)

#assimp
FetchContent_Declare(
    assimp
    GIT_REPOSITORY https://github.com/assimp/assimp.git
    GIT_TAG v5.1.0
)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(BUILD_SHARED_LIBS OFF)
set(ASSIMP_BUILD_3DS_IMPORTER OFF)
set(ASSIMP_BUILD_AMF_IMPORTER OFF)
set(ASSIMP_BUILD_AC_IMPORTER OFF)
set(ASSIMP_BUILD_ASE_IMPORTER OFF)
set(ASSIMP_BUILD_ASSBIN_IMPORTER OFF)
set(ASSIMP_BUILD_B3D_IMPORTER OFF)
set(ASSIMP_BUILD_BVH_IMPORTER OFF)
set(ASSIMP_BUILD_COLLADA_IMPORTER OFF)
set(ASSIMP_BUILD_DXF_IMPORTER OFF)
set(ASSIMP_BUILD_CSM_IMPORTER OFF)
set(ASSIMP_BUILD_HMP_IMPORTER OFF)
set(ASSIMP_BUILD_IRRMESH_IMPORTER OFF)
set(ASSIMP_BUILD_IRR_IMPORTER OFF)
set(ASSIMP_BUILD_LWO_IMPORTER OFF)
set(ASSIMP_BUILD_LWS_IMPORTER OFF)
set(ASSIMP_BUILD_M3D_IMPORTER OFF)
set(ASSIMP_BUILD_MD2_IMPORTER OFF)
set(ASSIMP_BUILD_MD3_IMPORTER OFF)
set(ASSIMP_BUILD_MD5_IMPORTER OFF)
set(ASSIMP_BUILD_MDC_IMPORTER OFF)
set(ASSIMP_BUILD_MDL_IMPORTER OFF)
set(ASSIMP_BUILD_NFF_IMPORTER OFF)
set(ASSIMP_BUILD_NDO_IMPORTER OFF)
set(ASSIMP_BUILD_OFF_IMPORTER OFF)
set(ASSIMP_BUILD_OBJ_IMPORTER ON)
set(ASSIMP_BUILD_OGRE_IMPORTER OFF)
set(ASSIMP_BUILD_OPENGEX_IMPORTER OFF)
set(ASSIMP_BUILD_PLY_IMPORTER OFF)
set(ASSIMP_BUILD_MS3D_IMPORTER OFF)
set(ASSIMP_BUILD_COB_IMPORTER OFF)
set(ASSIMP_BUILD_BLEND_IMPORTER OFF)
set(ASSIMP_BUILD_IFC_IMPORTER OFF)
set(ASSIMP_BUILD_XGL_IMPORTER OFF)
set(ASSIMP_BUILD_FBX_IMPORTER OFF)
set(ASSIMP_BUILD_Q3D_IMPORTER OFF)
set(ASSIMP_BUILD_Q3BSP_IMPORTER OFF)
set(ASSIMP_BUILD_RAW_IMPORTER OFF)
set(ASSIMP_BUILD_SIB_IMPORTER OFF)
set(ASSIMP_BUILD_SMD_IMPORTER OFF)
set(ASSIMP_BUILD_STL_IMPORTER OFF)
set(ASSIMP_BUILD_TERRAGEN_IMPORTER OFF)
set(ASSIMP_BUILD_3D_IMPORTER OFF)
set(ASSIMP_BUILD_X_IMPORTER OFF)
set(ASSIMP_BUILD_X3D_IMPORTER OFF)
set(ASSIMP_BUILD_GLTF_IMPORTER OFF)
set(ASSIMP_BUILD_3MF_IMPORTER OFF)
set(ASSIMP_BUILD_MMD_IMPORTER OFF)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_NO_EXPORT ON)
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_BUILD_ZLIB ON)
set(ASSIMP_INSTALL_PDB OFF)

FetchContent_MakeAvailable(assimp)

target_link_libraries(babyfoot glfw)
target_link_libraries(babyfoot glad)
target_link_libraries(babyfoot assimp)
include_directories(babyfoot PUBLIC "${stb_SOURCE_DIR}" "${glm_SOURCE_DIR}")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    target_link_libraries(babyfoot -static-libgcc)
    target_link_libraries(babyfoot -static-libstdc++)
    file(COPY /usr/x86_64-w64-mingw32/lib/libwinpthread-1.dll DESTINATION .)
    file(COPY /usr/lib/gcc/x86_64-w64-mingw32/10-posix/libgomp-1.dll DESTINATION .)
    file(COPY /usr/lib/gcc/x86_64-w64-mingw32/10-posix/libgcc_s_seh-1.dll DESTINATION .)
else()
    target_link_libraries(babyfoot dl)
    target_link_libraries(babyfoot X11)
    target_link_libraries(babyfoot pthread)
endif()

find_package(OpenMP)
if (OPENMP_FOUND)
    target_link_libraries(babyfoot OpenMP::OpenMP_CXX)
endif()

file(COPY /home/babyfoot/src/ressources/ DESTINATION ./ressources)