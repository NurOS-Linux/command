# Contributing to Aether Command

Thank you for your interest in contributing to Aether Command! This document provides guidelines and instructions for contributing to the project.

## Table of Contents

- [Code of Conduct](#code-of-conduct)
- [Getting Started](#getting-started)
- [Development Setup](#development-setup)
- [How to Contribute](#how-to-contribute)
- [Coding Standards](#coding-standards)
- [Commit Guidelines](#commit-guidelines)
- [Pull Request Process](#pull-request-process)
- [Reporting Bugs](#reporting-bugs)
- [Suggesting Features](#suggesting-features)

## Code of Conduct

Be respectful and professional in all interactions. We aim to create a welcoming environment for all contributors.

## Getting Started

1. Fork the repository on GitHub
2. Clone your fork locally
3. Set up the development environment
4. Create a new branch for your changes
5. Make your changes
6. Test your changes
7. Submit a pull request

## Development Setup

### Prerequisites

Make sure you have all dependencies installed. See [README.md](README.md#installing-dependencies) for distribution-specific instructions.

### Building the Project

```bash
git clone https://github.com/NurOS-Linux/command.git
cd command
meson setup builddir
ninja -C builddir
```

### Running Tests

```bash
ninja -C builddir test
```

### Running the Development Build

```bash
./builddir/aether-command
```

## How to Contribute

### Working on Existing Issues

1. Browse the [Issues](https://github.com/NurOS-Linux/command/issues) page
2. Comment on an issue you'd like to work on
3. Wait for approval from maintainers
4. Fork and create a branch
5. Work on the issue
6. Submit a pull request

### Proposing New Features

1. Check the [ROADMAP.md](ROADMAP.md) to see if it's already planned
2. Open a new issue describing the feature
3. Discuss the implementation with maintainers
4. Once approved, follow the standard contribution workflow

## Coding Standards

### Vala Code Style

- Use 4 spaces for indentation (no tabs)
- Use snake_case for methods and variables
- Use PascalCase for classes and namespaces
- Maximum line length: 120 characters
- Always use explicit access modifiers (public, private, protected)

### Example

```vala
namespace AetherCommand {
    public class ExampleClass : Gtk.Box {
        private string example_variable;
        
        public ExampleClass () {
            Object (
                orientation: Gtk.Orientation.VERTICAL,
                spacing: 0
            );
            
            setup_example ();
        }
        
        private void setup_example () {
            // Implementation
        }
    }
}
```

### File Headers

All source files must include the GPL-3.0 license header:

```vala
/*
 * Aether Command - Modern Terminal Emulator
 * Copyright (C) 2026 NurOS
 * Developer: AnmiTaliDev
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */
```

### Code Quality

- Code must compile without warnings
- Follow existing code patterns in the project
- Add comments for complex logic
- Keep methods focused and concise
- Avoid deep nesting (max 3-4 levels)

## Commit Guidelines

### Commit Message Format

```
<type>: <subject>

<body>

<footer>
```

### Types

- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation changes
- `style`: Code style changes (formatting, no code change)
- `refactor`: Code refactoring
- `test`: Adding or updating tests
- `chore`: Build process or auxiliary tool changes

### Examples

```
feat: add color scheme customization

Implemented color scheme selection in preferences dialog.
Users can now choose from predefined themes or create custom ones.

Closes #42
```

```
fix: correct window title update on directory change

The window title now properly updates when changing directories
in the terminal.

Fixes #38
```

### Commit Best Practices

- Write clear, descriptive commit messages
- Keep commits focused on a single change
- Reference issues in commit messages
- Use present tense ("add feature" not "added feature")
- Keep subject line under 50 characters
- Wrap body at 72 characters

## Pull Request Process

### Before Submitting

1. Ensure code compiles without warnings
2. Test your changes thoroughly
3. Update documentation if needed
4. Add yourself to contributors list if it exists

### PR Description

Include in your pull request:

- Summary of changes
- Related issue numbers
- Testing performed
- Screenshots (for UI changes)
- Breaking changes (if any)

### PR Template

```markdown
## Description
Brief description of changes

## Related Issue
Closes #(issue number)

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Breaking change
- [ ] Documentation update

## Testing
Describe testing performed

## Screenshots
(if applicable)

## Checklist
- [ ] Code compiles without warnings
- [ ] Code follows project style guidelines
- [ ] License header included in new files
- [ ] Documentation updated
- [ ] Tested on my system
```

### Review Process

1. Maintainers will review your PR
2. Address any feedback or requested changes
3. Once approved, maintainers will merge your PR
4. Your contribution will be included in the next release

## Reporting Bugs

### Before Reporting

- Check if the bug is already reported
- Try to reproduce with latest version
- Gather relevant information

### Bug Report Template

```markdown
**Description**
Clear description of the bug

**Steps to Reproduce**
1. Step one
2. Step two
3. Step three

**Expected Behavior**
What should happen

**Actual Behavior**
What actually happens

**Environment**
- OS: [e.g., Arch Linux]
- Aether Command version: [e.g., 0.0.1]
- GTK version: [run `pkg-config --modversion gtk4`]
- VTE version: [run `pkg-config --modversion vte-2.91-gtk4`]

**Additional Context**
Any other relevant information
```

## Suggesting Features

### Feature Request Template

```markdown
**Feature Description**
Clear description of the feature

**Use Case**
Why this feature would be useful

**Proposed Implementation**
(Optional) Ideas for implementation

**Alternatives Considered**
(Optional) Other solutions you've considered

**Additional Context**
Any mockups, examples, or references
```

## Getting Help

- Open an issue for questions
- Check existing documentation
- Review closed issues for similar problems
- Contact: anmitali198@gmail.com

## License

By contributing to Aether Command, you agree that your contributions will be licensed under the GNU General Public License v3.0.

---

Thank you for contributing to Aether Command!
