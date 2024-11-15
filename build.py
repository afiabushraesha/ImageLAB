import subprocess as sp
import os
import sys

# --------- CONFIG DATA --------- #

cpp_dirs = [
    "src/",
    "src/g_engine/",
    "vendor/cross_platform/"
]

cpp_compiler = "g++"

cpp_include_dirs = ["-Ivendor/include/", "-Isrc/g_engine/include/"]

cpp_lib_dirs = ""
cpp_libs = ["-lglfw3", "-lglm", "-limago"]

if sys.platform == "win32":
    cpp_lib_dirs = "-Lvendor/win32/"
    cpp_libs.extend(["-lopengl32", "-lUser32", "-lGdi32", "-lShell32"])
else:
    cpp_lib_dirs = "-Lvendor/linux_x86_64/"
    cpp_libs.extend(["-lGL", "-ldl"])

# ------------------------------- #


def getFilesWithExtension(_dirs, extensions):
    files = []

    for _dir in _dirs:
        items = os.listdir(_dir)

        for item in items:
            full_path = os.path.join(_dir, item)

            for extension in extensions:
                if os.path.isfile(full_path) and item.endswith(extension):
                    files.append(full_path)

    return files


def genObj(compiler, cpp_file_path, store_dir):
    cpp_file = os.path.basename(cpp_file_path)
    obj_file_path = os.path.join(store_dir, cpp_file + ".o")

    sp.run([compiler, "-c", cpp_file_path, "-o", obj_file_path],
           capture_output=False, text=False)

    return obj_file_path


def genBin(compiler, obj_files, bin_path, include_dirs, lib_dirs, libs):
    run_command = [compiler]
    run_command.extend(obj_files)
    run_command.extend(["-o", bin_path])
    run_command.extend(include_dirs)
    run_command.extend([lib_dirs])
    run_command.extend(libs)

    sp.run(run_command, capture_output=False, text=False)


if os.path.basename(__file__) == "build.py":
    compile_files = getFilesWithExtension(cpp_dirs, [".cpp", ".c"])
    os.makedirs("build/objs/", exist_ok=True)
    os.makedirs("build/bin/", exist_ok=True)

    obj_files = []

    print("Generating Objects:")

    for file in compile_files:
        print("    " + file + " => " + os.path.join("build/objs/",
              os.path.basename(file) + ".o"))

        obj_files.append(genObj(cpp_compiler, file, "build/objs/"))

    print("\nCompiling:")
    print("    Files       : ", end='')
    print(obj_files)
    print("    Include Dirs: ", end='')
    print(cpp_include_dirs)
    print("    Lib Dirs    : ", end='')
    print(cpp_lib_dirs)
    print("    Libs        : ", end='')
    print(cpp_libs)

    genBin(cpp_compiler, obj_files, "build/bin/ImageLab",
           cpp_include_dirs, cpp_lib_dirs, cpp_libs)
