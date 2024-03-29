# Makefile for compatibility with both Serial and OTA uploads

SRC_DIR = ${PWD}/src
BUILD_DIR = ${PWD}/build
MAIN_FILE = main.ino
TOOLS = ${PWD}/tools

PACKAGE = esp32
ARCH = esp32
BOARD = esp32doit-devkit-v1
PARAMETER = FlashFreq=80,UploadSpeed=921600

ARG = --board ${PACKAGE}:${ARCH}:${BOARD}:${PARAMETER} --verbose-build --pref build.path=${BUILD_DIR}

# Define default serial port
SERIAL ?= /dev/ttyUSB0

# Define default OTA  parameters
IP ?= 192.168.4.1
PORT ?= 5222

all:
	arduino --verify ${ARG} ${SRC_DIR}/${MAIN_FILE}

flash:
	arduino --upload ${ARG} ${SRC_DIR}/${MAIN_FILE} --port ${SERIAL}

clean:
	rm -rf ${BUILD_DIR}

upload: all
	${TOOLS}/espota.py --debug --progress -i ${IP} -p ${PORT} -f ${BUILD_DIR}/*.bin

run: all upload


# Make examples:
# make flash SERIAL=/dev/ttyUSBx
# make upload IP=192.168.0.103
