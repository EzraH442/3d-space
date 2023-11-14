project('3d-space', 'cpp')

include = include_directories('include')

subdir('src')

if meson.is_cross_build()
  dep = declare_dependency(include_directories: include, sources: src_sources, dependencies: [])
  executable('3d-space', 'main.cpp', dependencies: [dep], link_args: ['-o','out.html'])
else
  glew_dep = dependency('glew')
  sdl2_dep = dependency('sdl2')
  dep = declare_dependency(include_directories: include, sources: src_sources, dependencies: [sdl2_dep, glew_dep])
  executable('3d-space', 'main.cpp', dependencies: [dep])
endif
