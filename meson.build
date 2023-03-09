project('3d-space', 'cpp')

sdl2_dep = dependency('sdl2')

include = include_directories('include')

subdir('src')

dep = declare_dependency(include_directories: include, sources: foo_sources, dependencies: [sdl2_dep])

executable('3d-space', 'main.cpp', dependencies: [dep])
