#!/bin/bash

rm -fr build imgui.ini ./ImageLab

git add .
git commit -m "$1"
