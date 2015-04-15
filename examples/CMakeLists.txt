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

ENDIF()