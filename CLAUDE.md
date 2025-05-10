# Zed Theme Development Guide

## Extension Structure
- `extension.toml`: Main extension configuration file
- `themes/`: Directory containing theme JSON files

## Code Style Guidelines
- JSON formatting: 2-space indentation
- Theme file organization:
  - UI colors (editor, panels, etc.)
  - Syntax highlighting (token colors)
  - Terminal colors
- Use descriptive comments to delineate sections
- Theme naming convention: "Gruvbox Crisp ([Contrast Level], [Special Feature])"
- Color declarations should reference Gruvbox palette names in comments
- New theme variants should maintain consistent token coloring patterns

## Workflow
- Theme modifications should be tested in multiple languages
- Update README.md when adding new theme variants
- Update version in extension.toml for all changes
- Testing: Install the extension as a dev extension in Zed

## Color Consistency
- Maintain contrast ratios for accessibility
- Keep syntax highlighting colors consistent across theme variants
- Terminal colors should match editor theme colors

## Publishing
1. Fork the official Zed extensions repository
2. Add your extension as a Git submodule
3. Update the extensions.toml file
4. Submit a pull request to the zed-industries/extensions repository