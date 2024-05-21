#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "opencv_world" for configuration "Release"
set_property(TARGET opencv_world APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(opencv_world PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "vtkRenderingOpenGL2;vtkCommonCore;vtksys;vtkCommonDataModel;vtkCommonMath;vtkCommonMisc;vtkCommonSystem;vtkCommonTransforms;vtkCommonExecutionModel;vtkRenderingCore;vtkCommonColor;vtkCommonComputationalGeometry;vtkFiltersCore;vtkFiltersGeneral;vtkFiltersGeometry;vtkFiltersSources;vtkglew;vtkInteractionStyle;vtkFiltersExtraction;vtkFiltersStatistics;vtkImagingFourier;vtkImagingCore;vtkRenderingLOD;vtkFiltersModeling;vtkIOPLY;vtkIOCore;vtkdoubleconversion;vtklz4;vtklzma;vtkzlib;vtkFiltersTexture;vtkRenderingFreeType;vtkfreetype;vtkIOExport;vtkIOImage;vtkDICOMParser;vtkmetaio;vtkjpeg;vtkpng;vtktiff;vtkIOXML;vtkIOXMLParser;vtkexpat;vtkRenderingContext2D;vtkRenderingGL2PSOpenGL2;vtkgl2ps;vtkIOGeometry;vtkIOLegacy"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libopencv_world.so.4.9.0"
  IMPORTED_SONAME_RELEASE "libopencv_world.so.409"
  )

list(APPEND _cmake_import_check_targets opencv_world )
list(APPEND _cmake_import_check_files_for_opencv_world "${_IMPORT_PREFIX}/lib/libopencv_world.so.4.9.0" )

# Import target "opencv_img_hash" for configuration "Release"
set_property(TARGET opencv_img_hash APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(opencv_img_hash PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libopencv_img_hash.so.4.9.0"
  IMPORTED_SONAME_RELEASE "libopencv_img_hash.so.409"
  )

list(APPEND _cmake_import_check_targets opencv_img_hash )
list(APPEND _cmake_import_check_files_for_opencv_img_hash "${_IMPORT_PREFIX}/lib/libopencv_img_hash.so.4.9.0" )

# Import target "opencv_sfm" for configuration "Release"
set_property(TARGET opencv_sfm APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(opencv_sfm PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "gflags_shared"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libopencv_sfm.so.4.9.0"
  IMPORTED_SONAME_RELEASE "libopencv_sfm.so.409"
  )

list(APPEND _cmake_import_check_targets opencv_sfm )
list(APPEND _cmake_import_check_files_for_opencv_sfm "${_IMPORT_PREFIX}/lib/libopencv_sfm.so.4.9.0" )

# Import target "correspondence" for configuration "Release"
set_property(TARGET correspondence APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(correspondence PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/opencv4/3rdparty/libcorrespondence.a"
  )

list(APPEND _cmake_import_check_targets correspondence )
list(APPEND _cmake_import_check_files_for_correspondence "${_IMPORT_PREFIX}/lib/opencv4/3rdparty/libcorrespondence.a" )

# Import target "multiview" for configuration "Release"
set_property(TARGET multiview APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(multiview PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/opencv4/3rdparty/libmultiview.a"
  )

list(APPEND _cmake_import_check_targets multiview )
list(APPEND _cmake_import_check_files_for_multiview "${_IMPORT_PREFIX}/lib/opencv4/3rdparty/libmultiview.a" )

# Import target "numeric" for configuration "Release"
set_property(TARGET numeric APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(numeric PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/opencv4/3rdparty/libnumeric.a"
  )

list(APPEND _cmake_import_check_targets numeric )
list(APPEND _cmake_import_check_files_for_numeric "${_IMPORT_PREFIX}/lib/opencv4/3rdparty/libnumeric.a" )

# Import target "simple_pipeline" for configuration "Release"
set_property(TARGET simple_pipeline APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(simple_pipeline PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/opencv4/3rdparty/libsimple_pipeline.a"
  )

list(APPEND _cmake_import_check_targets simple_pipeline )
list(APPEND _cmake_import_check_files_for_simple_pipeline "${_IMPORT_PREFIX}/lib/opencv4/3rdparty/libsimple_pipeline.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
