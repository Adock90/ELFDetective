#!/usr/bin/env python3

import platform
import subprocess
import sys
import os
import shutil


BUILD_DIR = "./build/"
BUILD_FILENAME = "ELFDetective"
BUILD_FILES_STRING = "elfdetective/ELFDetective.c elfdetective/ELFError.c elfdetective/ELFFiles.c elfdetective/ELFHeader.c elfdetective/ELFProgramHeader.c elfdetective/ELFSection.c elfdetective/ELFUtils.c"
HEADER_PATH = "./include/"
SOURCE_PATH = "elfdetective/"
COMPILER = "gcc"
MAIN_FILE = "main.c"
COMPILER_LOG_PATH = "./build/build_log.log"


def DetectCompatiblePlatform():
    OS = platform.platform()
    if OS[:6] == "Windows":
        return 1
    else:
        return 0

def RaiseBuildError(msg):
    print(f"[ELFDetectiveBUILD] ERROR: {msg}")
    sys.exit(1)

def RaiseBuildWarn(msg):
    print(f"[ELFDetectiveBUILD] WARNING: {msg}")

if __name__ == "__main__":
    if DetectCompatiblePlatform() == 1:
        RaiseBuildError("Incompatible Operating System: Windows")
    else:
        if os.path.exists(HEADER_PATH) and os.path.exists(SOURCE_PATH):
            if os.path.exists(BUILD_DIR):
                shutil.rmtree(BUILD_DIR)
            os.mkdir(BUILD_DIR)
            if os.path.exists(BUILD_DIR) == False:
                RaiseBuildError("Cannot Create Build Path")
            
            cmd_args = [COMPILER, f"-I{HEADER_PATH}", MAIN_FILE] + BUILD_FILES_STRING.split() + ["-o", f"{BUILD_DIR}{BUILD_FILENAME}"]
            with open(COMPILER_LOG_PATH, "w") as log:
                subprocess.run(cmd_args, stdout=log, stderr=log)
        else:
            RaiseBuildError("Cannot find Critical Directory")
