#!/bin/bash

rm -fr build imgui.ini

git add .
git commit -m "$1"
