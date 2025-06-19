class Yeep < Formula
  desc "Yeep Programming Language - A simple, interpreted programming language"
  homepage "https://github.com/Syipmong/yeep-prolag"
  url "https://github.com/Syipmong/yeep-prolag/archive/v2.0.0.tar.gz"
  sha256 "PLACEHOLDER_SHA256"  # This will be updated when creating the actual release
  license "MIT"
  version "2.0.0"

  depends_on "gcc"

  def install
    # Build from source
    system "mkdir", "-p", "build/core"
    
    # Compile core components
    system "g++", "-Wall", "-Wextra", "-std=c++17", "-I", "include",
           "-c", "src/main.cpp", "-o", "build/main.o"
    system "g++", "-Wall", "-Wextra", "-std=c++17", "-I", "include",
           "-c", "src/core/YeepEngine.cpp", "-o", "build/core/YeepEngine.o"
    system "g++", "-Wall", "-Wextra", "-std=c++17", "-I", "include",
           "-c", "src/core/Token.cpp", "-o", "build/core/Token.o"
    system "g++", "-Wall", "-Wextra", "-std=c++17", "-I", "include",
           "-c", "src/core/Lexer.cpp", "-o", "build/core/Lexer.o"
    
    # Link executable
    system "g++", "build/main.o", "build/core/YeepEngine.o",
           "build/core/Token.o", "build/core/Lexer.o", "-o", "build/yeep"
    
    # Install binary
    bin.install "build/yeep"
    
    # Install documentation
    doc.install "README.md", "CHANGELOG.md", "INSTALLATION.md"
    
    # Install examples
    (share/"yeep").install "demo_v2.yeep"
  end

  test do
    # Test basic functionality
    (testpath/"test.yeep").write('print("Hello, Homebrew!");')
    assert_match "Hello, Homebrew!", shell_output("#{bin}/yeep #{testpath}/test.yeep")
  end
end
