#!/bin/bash

# This is a script to build and install Turtle
# Assume dependencies are installed!

set -e

VERSION=0.1.0
NAME=Turtle
REPO_DIR=${PWD}

# Build
[ -e build ] || mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .

# Create .desktop file
DESKTOP_FILE=turtle.desktop
echo "Creating desktop file ..."
echo "[Desktop Entry]" > $DESKTOP_FILE
{
  echo "Version=${VERSION}"
  echo "Type=Application"
  echo "Name=${NAME}"
  echo "Comment=A simple LOGO implementation"
  echo "TryExec=\"GTK_THEME=Adwaita:light ${PWD}/turtle\""
  echo "Exec=\"GTK_THEME=Adwaita:light ${PWD}/turtle\""
  echo "Icon=${REPO_DIR}/assets/logo.svg"
} >> $DESKTOP_FILE

# Copy .desktop file
echo "Copying desktop file to /usr/share/applications"
sudo cp $DESKTOP_FILE /usr/share/applications