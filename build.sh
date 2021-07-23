#!/bin/bash

# This is a script to build and install Turtle
# Assume dependencies are installed!

set -e

VERSION=0.1.0
NAME=Turtle
REPO_DIR=${PWD}

# Build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .

# Create .desktop file
DESKTOP_FILE=turtle.desktop
echo "[Desktop Entry]" > $DESKTOP_FILE
{
  echo "Version=${VERSION}"
  echo "Type=Application"
  echo "Name=${NAME}"
  echo "Comment=A simple LOGO implementation"
  echo "TryExec=${PWD}/turtle"
  echo "Exec=${PWD}/turtle"
  echo "Icon=${REPO_DIR}/assets/logo.svg"
} >> $DESKTOP_FILE

# Copy .desktop file
if [[ ! -e ~/.local/share/applications ]]; then
  mkdir ~/.local/share/applications
fi
cp $DESKTOP_FILE ~/.local/share/applications