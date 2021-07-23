#!/bin/bash

# This is a script to build and install Turtle
# Assume dependencies are installed!

set -e

VERSION=0.1.0
NAME=Turtle

# Build
[ -e build ] || mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make

# Copy files to their locations
echo "Copying turtle ..."
sudo cp turtle /usr/bin
echo "Copying icon ..."
sudo cp ../assets/logo.svg /usr/share/pixmaps/turtle.svg

# Create .desktop file
DESKTOP_FILE=turtle.desktop
echo "Creating desktop file ..."
echo "[Desktop Entry]" > $DESKTOP_FILE
{
  echo "Version=${VERSION}"
  echo "Type=Application"
  echo "Name=${NAME}"
  echo "Comment=A simple LOGO implementation"
  echo "Exec=env GTK_THEME=Adwaita:light /usr/bin/turtle"
  echo "Icon=/usr/share/pixmaps/turtle.svg"
} >> $DESKTOP_FILE

# Copy .desktop file
echo "Copying desktop file to /usr/share/applications ..."
sudo cp $DESKTOP_FILE /usr/share/applications
