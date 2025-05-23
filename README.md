# Gruvbox Crisp Themes for Zed Editor

A collection of high-contrast Zed themes based on the Gruvbox color scheme, optimized for clarity, readability, and visual comfort.

## Acknowledgment

This theme collection is based on the excellent [Gruvbox Theme by jdinhify](https://github.com/jdinhify/vscode-theme-gruvbox) and my previous work on [Gruvbox Crisp for VSCode](https://github.com/VatsalSy/gruvbox_custom_themes). The Zed version maintains the same design principles and color palettes while adapting to Zed's UI architecture.

## Features

- High contrast themes based on Gruvbox Dark
- Clear, non-hazy foreground colors
- Optimized syntax highlighting for multiple languages
- Consistent UI elements
- Multiple contrast levels to fit your environment

## Installation

### From Zed's Extension Panel

1. Open Zed
2. Open the Extensions panel
3. Search for "Gruvbox Crisp"
4. Click Install

### Manual Installation

1. Clone the repository: `git clone https://github.com/VatsalSy/zed-gruvbox_custom_themes.git`
2. Open Zed
3. Open the Extensions panel
4. Click "Install Dev Extension"
5. Select the cloned repository directory

### Continuous Integration

This repository includes a GitHub workflow using the
`bump-zed-extension` action. The workflow automatically bumps the
version in `extension.toml` when changes are pushed to the `main`
branch, ensuring the package stays up to date for publishing on
[zed.dev](https://zed.dev).

## Theme Variants

This collection includes multiple variants of the Gruvbox Dark theme:

1. **High Contrast** - Uses the darkest background (#1d2021) for maximum contrast
2. **High Contrast Purple** - Uses the dark background with purple accents
3. **Medium** - Uses a balanced background (#282828) for comfortable viewing
4. **Soft** - Uses a softer background (#32302f) for reduced eye strain

All variants maintain the same high-quality syntax highlighting, differing in their background intensity.

## Color Palette

The themes use the following Gruvbox colors:

- Background (Hard): #1d2021 
- Background (Medium): #282828
- Background (Soft): #32302f
- Foreground: #ebdbb2
- Red: #fb4934
- Green: #b8bb26
- Yellow: #fabd2f
- Blue: #83a598
- Purple: #d3869b
- Aqua: #8ec07c
- Orange: #fe8019

## Language Support

Enhanced syntax highlighting for:
- Python
- JavaScript/TypeScript
- Rust
- Go
- HTML/CSS
- JSON
- Markdown
- Shell scripts
- And many more...

## Recent Updates

### Version 0.1.1
- Fixed issue with text disappearing in popup hover menucards when selected
- Improved visibility of selected elements with proper text contrast

## Contributing

Feel free to open issues or submit pull requests on GitHub.

## License

MIT License - see LICENSE file for details.