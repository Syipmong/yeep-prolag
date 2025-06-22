# Yeep Release Structure

## 📁 Release Directory Organization

### Current Structure (v2.0.4+)
```
releases/
├── v2.0.4/                           # Current release
│   ├── yeep-v2.0.4-windows-x64/      # Extracted package
│   ├── yeep-v2.0.4-windows-x64.zip   # Release package
│   └── yeep-v2.0.4-windows-x64.zip.sha256  # Checksum
├── archive/                          # Historical releases
│   ├── v2.0.3/
│   ├── v2.0.2/
│   └── v2.0.1/
└── README.md                         # This file
```

### Legacy Cleanup
The following inconsistent directories have been consolidated:
- `release/` → moved to `releases/archive/`
- `dist/` → moved to `releases/archive/`
- `release-v2.0.2/` → moved to `releases/archive/`

## 🚀 Release Process

### 1. Build Release Package
```cmd
# Windows
create-release-v2.0.4.bat

# Linux/macOS (when implemented)
./create-release-v2.0.4.sh
```

### 2. Package Contents
Each release package contains:
- ✅ **yeep.exe** (or `yeep` binary) - Main interpreter
- ✅ **install.bat** - Windows installer
- ✅ **install.sh** - Linux/macOS installer
- ✅ **uninstall.bat** - Windows uninstaller
- ✅ **README.md** - Main documentation
- ✅ **LICENSE** - Software license
- ✅ **INSTALLATION-GUIDE.md** - Installation instructions
- ✅ **RELEASE-NOTES.md** - Version-specific release notes
- ✅ **examples/** - Sample Yeep scripts
- ✅ **vscode-extension/** - VSCode syntax highlighting
- ✅ **BUILD_INFO.txt** - Build metadata

### 3. Version Naming Convention
- **Package:** `yeep-v{version}-{platform}-{arch}`
- **Example:** `yeep-v2.0.4-windows-x64`
- **Archive:** `yeep-v2.0.4-windows-x64.zip`

### 4. Checksum Generation
Each release includes SHA256 checksum:
```
yeep-v2.0.4-windows-x64.zip.sha256
```

## 📋 Release Checklist

### Pre-Release
- [ ] Update version strings in source code
- [ ] Update documentation and release notes
- [ ] Build and test all features
- [ ] Run complete test suite
- [ ] Update installation scripts

### Release Build
- [ ] Run `create-release-v2.0.4.bat`
- [ ] Verify package contents
- [ ] Test installation on clean system
- [ ] Verify checksum

### Post-Release
- [ ] Upload to GitHub releases
- [ ] Update README download links
- [ ] Tag Git repository
- [ ] Announce release
- [ ] Archive old releases

## 🗂️ Archive Management

### Moving Old Releases
```cmd
# Move completed releases to archive
move releases\v2.0.3 releases\archive\v2.0.3
```

### Cleanup Commands
```cmd
# Clean old build artifacts
build-clean.bat

# Remove legacy release directories
rmdir /s /q release
rmdir /s /q dist
rmdir /s /q release-v2.0.2
```

## 🎯 Benefits of New Structure

1. **Consistency** - All releases in `releases/` directory
2. **Version Organization** - Each version has its own folder
3. **Archive System** - Historical releases preserved
4. **Clean Workspace** - No scattered release folders
5. **Automation Ready** - Scripts know where to find/create releases
6. **GitHub Integration** - Easy to upload organized packages

## 📤 Distribution

### GitHub Releases
1. Create new release on GitHub
2. Upload `yeep-v2.0.4-windows-x64.zip`
3. Upload checksum file
4. Add release notes from `RELEASE-NOTES-v2.0.4.md`

### Package Managers (Future)
- Chocolatey (Windows) - `chocolatey/` directory ready
- Homebrew (macOS) - `homebrew/` directory ready
- APT/RPM (Linux) - Future implementation

---

**This structure ensures consistent, organized, and professional release management for Yeep v2.0.4+**
