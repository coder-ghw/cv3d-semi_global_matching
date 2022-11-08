if [[ $1 > 0 ]]; then
  rm -rf build
  mkdir build
  cd build
  
  # opencv install path: can install it use conda env create -f ${PROJJECT_SOURCE_DIR}/envirenment.yml
  # defalt: no set
  cmake -DCMAKE_BUILD_TYPE=Debug\
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON\
        -DEnableTest=ON\
        -DOpencvInstallPath=/home/guohw/miniconda3/envs/algo-v1 ..

else
  cd build
fi

make -j8
