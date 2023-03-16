if [[ $1 > 0 ]]; then
  rm -rf build
  mkdir build
  cd build
  
  # opencv install path: can install it use conda env create -f ${PROJJECT_SOURCE_DIR}/envirenment.yml
  # defalt: no set
  cmake -DCMAKE_BUILD_TYPE=Debug\
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON\
        -DEnableTest=ON\
        -DGtestInstallPath=/home/guohw/data/projects/third_party/linux-x86_64/gtest-1.10.0-ef502364e45b4af7dd7e608b441fadef \
        -DOpencvInstallPath=/home/guohw/miniconda3/envs/algo-v1 .. || exit 1

else
  cd build
fi

make -j8 || exit 1

make test
