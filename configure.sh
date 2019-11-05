#!/bin/bash

PKGS_DIR=$SPC_PKGS_DIR
RES_DIR=$SPC_RES_DEST_DIR
SRC_DEST_DIR=$SPC_J_DEST_DIR

copied_java="false"

pushd $PKGS_DIR >/dev/null
for pkg_dir in $(ls); do
  pushd $pkg_dir >/dev/null
  tar -xzf JNISpice.tar.Z
  if [ $? -ne 0 ]; then
    echo "Failed to extract JNISpice archive for ${PKGS_DIR}/${pkg_dir}"
    exit 1
  fi
  if [ "$copied_java" == "false" ]; then
    echo "Copying java source to ${SRC_DEST_DIR}"
    cp JNISpice/src/JNISpice/spice/basic/*.java $SRC_DEST_DIR
    if [ $? -ne 0 ]; then
      echo "Failed to copy Java source files to $SRC_DEST_DIR"
      exit 1
    fi
    copied_java="true"
  fi
  res_dest="${RES_DIR}/${pkg_dir}"
  mkdir -p $res_dest
  available_libs=$(ls JNISpice/lib/libJNISpice.*)
  echo "Copying ${available_libs} to ${res_dest}"
  cp JNISpice/lib/libJNISpice.* $res_dest
  if [ $? -ne 0 ]; then
    echo "Failed to copy libs ${available_libs} to ${res_dest}"
    exit 1
  fi
  rm -rf JNISpice
  popd >/dev/null
done

popd >/dev/null
