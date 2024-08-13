import os
import subprocess
import sys

def find_cpp_files(directory):
    cpp_files = []
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith('.cpp'):
                cpp_files.append(os.path.join(root, file))
    return cpp_files

def compile_cpp_files(cpp_files, output_dir, compiler='x86_64-w64-mingw32-g++', flags=None):
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    if flags is None:
        flags = []

    object_files = []
    for cpp_file in cpp_files:
        object_file = os.path.join(output_dir, os.path.basename(cpp_file).replace('.cpp', '.o'))
        object_files.append(object_file)

        cmd = [compiler, '-c', cpp_file, '-o', object_file] + flags
        print(f"Compiling {cpp_file} -> {object_file} with flags: {' '.join(flags)}")
        result = subprocess.run(cmd, capture_output=True)
        if result.returncode != 0:
            print(f"Error compiling {cpp_file}: {result.stderr.decode('utf-8')}")
            sys.exit(1)
        else:
            print(f"Compiled {cpp_file} successfully.")
    
    return object_files

def link_object_files(object_files, output_file, linker='x86_64-w64-mingw32-g++', link_flags=None):
    if link_flags is None:
        link_flags = []

    cmd = [linker, '-o', output_file] + object_files + link_flags
    print(f"Linking {' '.join(object_files)} -> {output_file} with flags: {' '.join(link_flags)}")
    result = subprocess.run(cmd, capture_output=True)

    if result.returncode != 0:
        print(f"Error linking: {result.stderr.decode('utf-8')}")
        sys.exit(1)
    else:
        print(f"Linked successfully into {output_file}")

def main():
    src_dir = 'src'
    build_dir = 'build'
    output_file = os.path.join(build_dir, 'main.exe')

    cpp_files = find_cpp_files(src_dir)
    if not cpp_files:
        print(f"No .cpp files found in {src_dir}")
        return

    compile_flags = ['-O2', '-mwindows', '-Wall', '-Wextra', '--static', '-static-libgcc', '-static-libstdc++', '-v']
    link_flags = ['-lgdi32']

    object_files = compile_cpp_files(cpp_files, build_dir, flags=compile_flags)
    link_object_files(object_files, output_file, link_flags=link_flags)

if __name__ == '__main__':
    main()