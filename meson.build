project('aether-command', 'vala', 'c',
    version: '0.0.1',
    license: 'GPL-3.0-or-later'
)

gnome = import('gnome')

add_project_arguments([
    '--pkg=gtk4',
    '--pkg=libadwaita-1',
    '--pkg=vte-2.91-gtk4',
    '--gresources', join_paths(meson.current_source_dir(), 'data', 'org.aether.command.gresource.xml')
], language: 'vala')

dependencies = [
    dependency('gtk4'),
    dependency('libadwaita-1'),
    dependency('vte-2.91-gtk4')
]

gresource = gnome.compile_resources(
    'aether-command-resources',
    'data' / 'org.aether.command.gresource.xml',
    source_dir: 'data'
)

sources = files(
    'src/main.vala',
    'src/window.vala',
    'src/terminal.vala'
)

executable('aether-command',
    sources,
    gresource,
    dependencies: dependencies,
    install: true
)

subdir('data')