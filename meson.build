project('3d-space', 'cpp')

sfml_dep = dependency('sfml-all')

subdir('src')

pkg_mod = import('pkgconfig')
pkg_mod.generate(
  libraries: foolib,
  version: '1.0',
  name: 'libfoobar',
  filebase: 'foobar'
)

executable('3d-space', src, dependencies: [sfml_dep])
