# Gruvbox Crisp Theme Demo

> A comprehensive demonstration of Markdown syntax highlighting with the Gruvbox Crisp theme.

## Table of Contents

1. [Introduction](#introduction)
2. [Text Formatting](#text-formatting)
3. [Lists](#lists)
4. [Links and Images](#links-and-images)
5. [Code](#code)
6. [Tables](#tables)
7. [Blockquotes](#blockquotes)
8. [Horizontal Rules](#horizontal-rules)
9. [Task Lists](#task-lists)
10. [Extended Syntax](#extended-syntax)

---

## Introduction

This document showcases various **Markdown** elements to demonstrate how they appear with the _Gruvbox Crisp_ theme. The theme provides excellent contrast and readability for all Markdown elements.

### Why Gruvbox Crisp?

The ***Gruvbox Crisp*** theme offers:
- **High contrast** for better visibility
- *Carefully selected* color palette
- ~~Reduced~~ **Enhanced** readability
- Support for `inline code` elements

## Text Formatting

### Basic Formatting

This is regular text. You can make text **bold** or *italic*. You can also combine them for ***bold and italic*** text.

Use ~~strikethrough~~ to indicate deleted content.

For keyboard shortcuts, use <kbd>Ctrl</kbd> + <kbd>C</kbd>.

### Special Characters

- Copyright: &copy; 2024
- Trademark: Gruvbox&trade;
- Registered: Theme&reg;
- Em dash: Text—more text
- En dash: Pages 1–10
- Ellipsis: Wait for it...

### Subscript and Superscript

- H<sub>2</sub>O (water)
- X<sup>2</sup> + Y<sup>2</sup> = Z<sup>2</sup>

## Lists

### Unordered Lists

* First level item
  * Second level item
    * Third level item
      * Fourth level item
* Another first level item
  - Can use different markers
  + They all work the same

### Ordered Lists

1. First item
2. Second item
   1. Nested item 2.1
   2. Nested item 2.2
      1. Deep nested 2.2.1
      2. Deep nested 2.2.2
3. Third item

### Mixed Lists

1. First ordered item
   - Unordered sub-item
   - Another unordered sub-item
     1. Ordered sub-sub-item
     2. Another ordered sub-sub-item
2. Second ordered item

## Links and Images

### Links

- [Basic link](https://example.com)
- [Link with title](https://example.com "Hover to see title")
- [Reference-style link][reference]
- [Relative link](../README.md)
- <https://auto-link.com>
- Email: <email@example.com>

[reference]: https://example.com "Reference Link"

### Images

![Alt text for image](https://via.placeholder.com/150 "Image title")

[![Clickable image](https://via.placeholder.com/100)](https://example.com)

### Image with Reference

![Reference image][img-ref]

[img-ref]: https://via.placeholder.com/200 "Reference Image"

## Code

### Inline Code

Use `const` instead of `var` in JavaScript. The `git status` command shows changes.

### Code Blocks

```javascript
// JavaScript example
const gruvbox = {
  name: 'Gruvbox Crisp',
  type: 'dark',
  colors: {
    background: '#1d2021',
    foreground: '#ebdbb2',
    keywords: '#fb4934',
    strings: '#b8bb26'
  }
};

function applyTheme(theme) {
  console.log(`Applying ${theme.name} theme...`);
  return theme.colors;
}
```

```python
# Python example
class ThemeManager:
    """Manages color themes for the editor"""
    
    def __init__(self, theme_name="gruvbox"):
        self.theme_name = theme_name
        self.colors = self._load_colors()
    
    def _load_colors(self):
        """Load color definitions"""
        return {
            'bg': '#1d2021',
            'fg': '#ebdbb2',
            'red': '#fb4934',
            'green': '#b8bb26'
        }
    
    @property
    def background(self):
        return self.colors.get('bg', '#000000')
```

```bash
#!/bin/bash
# Shell script example

# Install the theme
install_theme() {
    local theme_name="$1"
    echo "Installing ${theme_name}..."
    
    if [[ -z "$theme_name" ]]; then
        echo "Error: Theme name required" >&2
        return 1
    fi
    
    cp -r "./themes/${theme_name}" ~/.config/themes/
    echo "Theme installed successfully!"
}

# Apply theme
install_theme "gruvbox-crisp"
```

### Syntax Highlighting for Various Languages

```rust
// Rust example
#[derive(Debug, Clone)]
struct Theme {
    name: String,
    colors: HashMap<String, String>,
}

impl Theme {
    fn new(name: &str) -> Self {
        Self {
            name: name.to_string(),
            colors: HashMap::new(),
        }
    }
}
```

```go
// Go example
package main

import "fmt"

type Theme struct {
    Name   string
    Colors map[string]string
}

func main() {
    theme := Theme{
        Name: "Gruvbox Crisp",
        Colors: map[string]string{
            "bg": "#1d2021",
            "fg": "#ebdbb2",
        },
    }
    fmt.Printf("Using theme: %s\n", theme.Name)
}
```

## Tables

### Basic Table

| Feature | Gruvbox Crisp | Standard Theme |
|---------|---------------|----------------|
| Contrast Ratio | 21:1 | 7:1 |
| Color Count | 16 | 8 |
| Language Support | 50+ | 25 |

### Aligned Table

| Left Aligned | Center Aligned | Right Aligned |
|:-------------|:--------------:|--------------:|
| Text | Text | Text |
| More text | More text | More text |
| Even more | Even more | Even more |

### Complex Table

| Language | Syntax | Highlighting | Theme Support | Notes |
|----------|:------:|:------------:|:-------------:|-------|
| JavaScript | ✅ | ✅ | ✅ | Full ES2022 support |
| TypeScript | ✅ | ✅ | ✅ | Including decorators |
| Python | ✅ | ✅ | ✅ | Python 3.x syntax |
| Rust | ✅ | ✅ | ✅ | Latest stable |
| Go | ✅ | ✅ | ✅ | Generics supported |

## Blockquotes

> This is a simple blockquote. It can contain **formatted** text.

> Blockquotes can also be multi-line.
> 
> They can even contain multiple paragraphs.

### Nested Blockquotes

> Level 1 blockquote
>> Level 2 nested blockquote
>>> Level 3 deeply nested blockquote

### Blockquotes with Other Elements

> #### Blockquote with Header
> 
> - Can contain lists
> - With multiple items
> 
> ```javascript
> // And code blocks
> const quote = "Amazing!";
> ```

## Horizontal Rules

Three or more hyphens:

---

Three or more asterisks:

***

Three or more underscores:

___

## Task Lists

### Project Tasks

- [x] Create theme file
- [x] Define color palette
- [x] Test with multiple languages
- [ ] Write documentation
- [ ] Publish to marketplace
  - [x] Prepare metadata
  - [ ] Submit for review

### Feature Checklist

- [x] Syntax highlighting
- [x] High contrast mode
- [ ] Light theme variant
- [ ] Color customization
  - [ ] UI colors
  - [ ] Syntax colors

## Extended Syntax

### Definition Lists

Gruvbox
: A retro groove color scheme for Vim

High Contrast
: Maximum difference between foreground and background colors

Theme
: A collection of colors and styles for syntax highlighting

### Footnotes

Here's a sentence with a footnote[^1]. And another one[^2].

[^1]: This is the first footnote.
[^2]: This is the second footnote with more text.

### Abbreviations

The HTML specification is maintained by the W3C.

*[HTML]: HyperText Markup Language
*[W3C]: World Wide Web Consortium

### Emoji Support

:smile: :heart: :thumbsup: :sparkles: :rocket:

### Math (when supported)

Inline math: $E = mc^2$

Block math:

$$
\frac{n!}{k!(n-k)!} = \binom{n}{k}
$$

### Admonitions

!!! note "Important Note"
    This is an important note about the Gruvbox Crisp theme.

!!! warning "Warning"
    Make sure to test your color choices for accessibility.

!!! tip "Pro Tip"
    Use the high contrast variant for better readability in bright environments.

### Details/Summary

<details>
<summary>Click to expand more information</summary>

This is hidden content that can be revealed by clicking the summary. It's useful for:
- Additional documentation
- Optional configuration
- Extended examples

```json
{
  "theme": "gruvbox-crisp",
  "variant": "high-contrast"
}
```

</details>

## Raw HTML

<div align="center">
  <h3>Centered HTML Content</h3>
  <p>Sometimes you need <mark>highlighted text</mark> or <sup>superscript</sup> that Markdown doesn't support.</p>
</div>

<table>
  <tr>
    <th colspan="2">HTML Table</th>
  </tr>
  <tr>
    <td style="color: #fb4934;">Red Text</td>
    <td style="color: #b8bb26;">Green Text</td>
  </tr>
</table>

## Comments

<!-- This is an HTML comment that won't be rendered -->

[//]: # (This is also a comment using a different syntax)

## Escaping

\*Not italic\* but shows asterisks

\`Not code\` but shows backticks

\[Not a link\](just text)

Use backslash \\ to escape special characters.

---

## Conclusion

The **Gruvbox Crisp** theme provides excellent highlighting for all Markdown elements, making your documents both *beautiful* and ***highly readable***.

For more information, visit the [Gruvbox Crisp repository](https://github.com/VatsalSy/zed-gruvbox_custom_themes).

Happy writing! :pencil: