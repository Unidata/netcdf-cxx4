################################################
# CMakeLists.txt: CMake Configuration file
# for the netcdf-cxx4 `examples` directory.
################################################

IF(NCXX_ENABLE_TESTS)

  add_bin_test(examples simple_xy_wr)
  add_bin_test(examples sfc_pres_temp_wr)
  add_bin_test(examples pres_temp_4D_wr)
  add_bin_test(examples pres_temp_4D_rd)
  add_bin_test(examples simple_xy_rd)
  add_bin_test(examples sfc_pres_temp_rd)
  add_bin_test(examples simple_xy_wr_formats)

  IF(NC_HAS_DEF_VAR_FILTER)
    build_bin_test(pres_temp_4D_plugin_wr)
    build_bin_test(pres_temp_4D_plugin_rd)
    add_sh_test(examples tst_filter)
  ENDIF(NC_HAS_DEF_VAR_FILTER)

  FILE(GLOB COPY_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.sh)
  FILE(COPY ${COPY_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

ENDIF()
