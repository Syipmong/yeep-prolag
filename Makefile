CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -I include
TARGET=build/yeep
SRCDIR=src
INCDIR=include
BUILDDIR=build
SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS=$(SOURCES:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

# Installation directories
PREFIX?=/usr/local
BINDIR=$(PREFIX)/bin
LIBDIR=$(PREFIX)/lib/yeep

.PHONY: all clean install uninstall test help

all: $(TARGET)

# Create build directory
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Build the main executable
$(TARGET): $(BUILDDIR) $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Compile object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILDDIR)

# Install system-wide
install: $(TARGET)
	install -d $(BINDIR)
	install -d $(LIBDIR)
	install -d $(LIBDIR)/examples
	install -m 755 $(TARGET) $(BINDIR)/yeep
	install -m 644 README.md $(LIBDIR)/
	install -m 644 LANGUAGE_SPEC.md $(LIBDIR)/
	install -m 644 examples/* $(LIBDIR)/examples/
	@echo "Yeep installed to $(BINDIR)/yeep"
	@echo "Documentation and examples in $(LIBDIR)/"

# Uninstall
uninstall:
	rm -f $(BINDIR)/yeep
	rm -rf $(LIBDIR)
	@echo "Yeep uninstalled"

# Run tests
test: $(TARGET)
	@echo "Running Yeep tests..."
	./$(TARGET) examples/hello.yeep
	./$(TARGET) examples/simple.yeep
	@echo "All tests passed!"

# Show help
help:
	@echo "Yeep Programming Language Build System"
	@echo ""
	@echo "Targets:"
	@echo "  all       Build yeep executable (default)"
	@echo "  clean     Remove build artifacts"
	@echo "  install   Install yeep system-wide (requires sudo)"
	@echo "  uninstall Remove yeep from system"
	@echo "  test      Run example scripts"
	@echo "  help      Show this help message"
	@echo ""
	@echo "Variables:"
	@echo "  PREFIX    Installation prefix (default: /usr/local)"
	@echo "  CC        Compiler (default: gcc)"
