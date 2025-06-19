# Yeep Language VSCode Extension

This directory contains a Visual Studio Code extension that provides syntax highlighting and language support for the Yeep programming language.

## Features

- **Syntax Highlighting**: Proper colorization of Yeep code
- **Language Recognition**: VSCode recognizes `.yeep` files
- **Auto-closing Brackets**: Automatic bracket and quote completion
- **Comment Support**: Line comments with `#`

## Installation

### From Source
1. Copy this entire `vscode-extension` folder
2. Install `vsce` (Visual Studio Code Extension manager):
   ```bash
   npm install -g vsce
   ```
3. Build the extension:
   ```bash
   cd vscode-extension
   vsce package
   ```
4. Install in VSCode:
   ```bash
   code --install-extension yeep-language-1.0.0.vsix
   ```

### Manual Installation
1. Copy the `vscode-extension` folder to your VSCode extensions directory:
   - **Windows**: `%USERPROFILE%\.vscode\extensions\yeep-language`
   - **macOS**: `~/.vscode/extensions/yeep-language`
   - **Linux**: `~/.vscode/extensions/yeep-language`
2. Restart VSCode

## Usage

Once installed:
1. Open any `.yeep` file in VSCode
2. The file will automatically be recognized as a Yeep file
3. Syntax highlighting will be applied
4. Language-specific features will be available

## Publishing to VSCode Marketplace

To publish this extension to the VSCode Marketplace:

1. **Create Publisher Account**: Register at https://marketplace.visualstudio.com/
2. **Get Access Token**: Create a Personal Access Token
3. **Login with vsce**:
   ```bash
   vsce login your-publisher-name
   ```
4. **Publish**:
   ```bash
   vsce publish
   ```

## Features Included

### Syntax Highlighting
- **Keywords**: `if`, `else`, `while`, `for`, `function`, `return`, `print`, `and`, `or`, `not`, `true`, `false`
- **Operators**: `+`, `-`, `*`, `/`, `%`, `==`, `!=`, `<=`, `>=`, `<`, `>`, `=`
- **Strings**: Double-quoted strings with escape sequence support
- **Numbers**: Integer and decimal number literals
- **Comments**: Line comments starting with `#`
- **Variables**: Variable name recognition

### Language Configuration
- **Auto-closing Pairs**: Brackets `{}`, `[]`, `()` and quotes `""`
- **Comment Toggle**: Ctrl+/ to toggle line comments
- **Bracket Matching**: Highlight matching brackets

## Future Enhancements

Potential additions to the extension:
- **IntelliSense**: Code completion and suggestions
- **Error Detection**: Real-time syntax error highlighting
- **Debugging Support**: Integration with Yeep debugger
- **Code Formatting**: Automatic code formatting
- **Symbol Navigation**: Go to definition, find references
- **Snippets**: Code snippets for common patterns

## Contributing

To improve this extension:
1. Fork the main Yeep repository
2. Make changes in the `vscode-extension/` directory
3. Test the extension locally
4. Submit a pull request

This extension helps establish Yeep as a recognized programming language in the developer ecosystem!
