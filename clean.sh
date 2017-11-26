echo "Started Cleaning Kernel Sources from AzurE Nougat" 
export CROSS_COMPILE=/home/panchajanya/Kernel/Toolchains/aarch64-linux-android-7.2.1-uber/bin/aarch64-linux-android-
export ARCH=arm64
export SUBARCH=arm64
make clean && make mrproper
echo "Started Cleaning Anykernel Sources for AzurE Nougat"
rm -rf ../anykernel/dt.img
rm -rf ../anykernel/modules/wlan.ko
rm -rf ../anykernel/zImage
