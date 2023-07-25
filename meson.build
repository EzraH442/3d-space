project('3d-space', 'cpp')

include = include_directories('include')

cmake = import('cmake')
sdl2_gfx_subproj = cmake.subproject('sdl2_gfx')

sdl2_gfx_dep = sdl2_gfx_subproj.dependency('SDL2_gfx')
subdir('src')

if meson.is_cross_build()
  dep = declare_dependency(include_directories: include, sources: src_sources, dependencies: [sdl2_gfx_dep])
  executable('3d-space', 'main.cpp', dependencies: [dep], link_args: ['-o','out.html'])
else
  sdl2_dep = dependency('sdl2')
  dep = declare_dependency(include_directories: include, sources: src_sources, dependencies: [sdl2_dep, sdl2_gfx_dep])
  executable('3d-space', 'main.cpp', dependencies: [dep])
endif
