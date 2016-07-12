# file: config.cmake
# author: Sho Ikeda
#
# Copyright (c) 2015 Sho Ikeda
# This software is released under the MIT License.
# http://opensource.org/licenses/mit-license.php
#

cmake_minimum_required(VERSION 3.4)

set(__nanairo_common_root__ ${CMAKE_CURRENT_LIST_DIR})


function(makeNanairoCommonKeywordFile keyword_dir)
  configure_file(${__nanairo_common_root__}/keyword.hpp.in ${keyword_dir}/keyword.hpp)

  set(keyword_list ${ARGN})
  list(LENGTH keyword_list list_size)
  math(EXPR length "${list_size} / 2")
  foreach(number RANGE 1 ${length})
    math(EXPR variable_index "(${number} - 1) * 2")
    math(EXPR keyword_index "${variable_index} + 1")
    list(GET keyword_list ${variable_index} variable)
    list(GET keyword_list ${keyword_index} keyword)
    file(APPEND ${keyword_dir}/keyword.hpp "constexpr char ${variable}[] = \"${keyword}\";\n")
  endforeach()
  file(APPEND ${keyword_dir}/keyword.hpp "\n} // namespace keyword\n")
  file(APPEND ${keyword_dir}/keyword.hpp "\n//! \\} Common\n")
  file(APPEND ${keyword_dir}/keyword.hpp "\n} // namespace nanairo\n")
  file(APPEND ${keyword_dir}/keyword.hpp "\n#endif // NANAIRO_KEYWORD_HPP\n")
endfunction()


# Load nanairo common files
function(getNanairoCommon)
  set(common_config_dir ${PROJECT_BINARY_DIR}/include/NanairoCommon)
  configure_file(${__nanairo_common_root__}/keyword.hpp.in
                 ${common_config_dir}/keyword.hpp)
  makeNanairoCommonKeywordFile(${common_config_dir} ${nanairo_keyword_list})
  configure_file(${__nanairo_common_root__}/nanairo_common_config.hpp.in
                 ${common_config_dir}/nanairo_common_config.hpp)
  source_group(NanairoCommon FILES 
               ${common_config_dir}/keyword.hpp
               ${common_config_dir}/nanairo_common_config.hpp)
endfunction(getNanairoCommon)