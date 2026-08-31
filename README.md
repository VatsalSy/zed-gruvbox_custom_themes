# CoMPhy Crisp Themes for Zed Editor

A collection of jewel-toned Zed themes built around a deep plum (#68236D) accent, with syntax colors emerging against near-void backgrounds with subtle purple warmth.

## Theme Variants

This extension ships four themes:

1. **CoMPhy Crisp Velvet** — Standard dark with purple-tinted blacks and full jewel-tone syntax
2. **CoMPhy Crisp Velvet Light** — Lavender-white background with darkened syntax for WCAG AA contrast
3. **CoMPhy Crisp Velvet (Highest Contrast)** — Pure black editor with boosted syntax brightness and active line number accent
4. **CoMPhy Crisp Velvet (Warm)** — Warm near-black with coral keywords, amber types, and cream text

## Color Palette

- **Accent spectrum**: Deep plum `#68236D` through orchid `#C084C8` to pale `#E8C8EC`
- **Syntax**: Ruby keywords, jade strings, orchid functions, amber types, sapphire variables, aquamarine properties, amethyst numbers
- **Backgrounds**: Purple-tinted blacks (`#1A1822` standard, `#F4F0F5` light, `#000000` highest contrast, `#100E0D` warm)

## Installation

### From Zed's Extension Panel

1. Open Zed
2. Open the Extensions panel
3. Search for `CoMPhy Crisp Themes`
4. Click Install

### Manual Installation

1. Clone the repository: `git clone https://github.com/comphy-lab/comphy-zed-themes.git`
2. Open Zed
3. Open the Extensions panel
4. Click `Install Dev Extension`
5. Select the cloned repository directory

## Migration Notes (v0.3.0 to v0.4.0)

The v0.4.0 release replaces all previous theme variants with the new Velvet Abyss palette:

- Previous variants (`Anysphere Blend Dark`, `Anysphere Blend Light`, `Anysphere (Highest Contrast, pop)`, `Highest Contrast`) are removed
- New variants: `Velvet`, `Velvet Light`, `Velvet (Highest Contrast)`, `Velvet (Warm)`
- After updating, re-select your preferred theme from the theme picker

## Release Workflow

Releases are tag-driven:

- Workflow: `.github/workflows/release.yml`
- Trigger: push tags matching `v*`
- Publisher action: `huacnlee/zed-extension-action@v1.0.0`
- Extension name for publishing: `comphy-crisp-themes`

## Language Support

Enhanced syntax highlighting for:

- Python
- JavaScript and TypeScript
- Rust
- Go
- HTML and CSS
- JSON
- Markdown
- LaTeX
- Shell scripts
- And more

## License

MIT License. See `LICENSE`.
