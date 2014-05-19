DebuggingAssistant
==================

Android Debug Assistant

![image](https://raw.githubusercontent.com/kangear/DebuggingAssistant/master/images-folde/preview.png)

Like this command: http://wiki.cyanogenmod.org/w/Doc:_Building_Basics

source build/envsetup.sh

adb remount

adb sync

待添加功能
=================

1. Sync system

adb sync -p ${android_product_out} system

2. Sync data

adb sync -p ${android_product_out} data
