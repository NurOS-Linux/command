Name:           aether-command
Version:        0.1.0~alpha
Release:        1%{?dist}
Summary:        Modern terminal emulator for AetherDE desktop environment

License:        GPL-3.0-or-later
URL:            https://github.com/NurOS-Linux/command
Source0:        https://github.com/NurOS-Linux/command/archive/v%{version}.tar.gz

BuildRequires:  meson
BuildRequires:  ninja-build
BuildRequires:  vala
BuildRequires:  gcc
BuildRequires:  pkgconfig(gtk4)
BuildRequires:  pkgconfig(libadwaita-1)
BuildRequires:  pkgconfig(vte-2.91-gtk4)

Requires:       gtk4
Requires:       libadwaita
Requires:       vte291-gtk4

%description
Aether Command is a modern terminal emulator designed for the AetherDE desktop
environment. Built with GTK4 and LibAdwaita, it provides a clean and intuitive
interface that seamlessly integrates with GNOME-based desktops while working
on any Linux distribution with GTK4 support.

Features:
- Dynamic window title showing current command or shell prompt
- Multiple terminal tabs support
- Copy/paste with keyboard shortcuts (Ctrl+Shift+C/V)
- Full VTE terminal emulation
- Native LibAdwaita design

%prep
%autosetup -n command-%{version}

%build
%meson
%meson_build

%install
%meson_install

%check
%meson_test || true

%files
%license LICENSE
%doc README.md
%{_bindir}/aether-command
%{_datadir}/applications/org.aether.command.desktop
%{_datadir}/metainfo/org.aether.command.metainfo.xml

%changelog
* Sat Feb 01 2026 AnmiTaliDev <anmitali198@gmail.com> - 0.1.0~alpha-1
- Initial alpha release
- Dynamic window title tracking
- Tab support for multiple terminals
- Copy/paste keyboard shortcuts
- Right-click context menu
- GTK4 and LibAdwaita integration
