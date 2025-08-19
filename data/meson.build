desktop_file = configure_file(
    input: 'org.aether.command.desktop.in',
    output: 'org.aether.command.desktop',
    configuration: {
        'bindir': get_option('prefix') / get_option('bindir')
    }
)

install_data(desktop_file,
    install_dir: get_option('datadir') / 'applications'
)

appstream_file = configure_file(
    input: 'org.aether.command.metainfo.xml.in',
    output: 'org.aether.command.metainfo.xml',
    configuration: {
        'version': meson.project_version()
    }
)

install_data(appstream_file,
    install_dir: get_option('datadir') / 'metainfo'
)