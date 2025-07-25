#!/bin/bash
set -e

echo "🔨 Building GScript..."
make

echo "⬆️  Installing binaries (may ask for sudo password)..."
sudo cp build/gscript /usr/local/bin/gscript
sudo cp gscript-run /usr/local/bin/gsc

# Check for nasm
if ! command -v nasm &> /dev/null
then
    echo "⚠️ WARNING: 'nasm' not found. Please install nasm:"
    echo "  Ubuntu: sudo apt install nasm"
    echo "  macOS (with Homebrew): brew install nasm"
fi

# Check for ld
if ! command -v ld &> /dev/null
then
    echo "⚠️ WARNING: 'ld' not found. Please install binutils or build-essential."
fi

echo "✅ Installed as:"
echo "   /usr/local/bin/gscript"
echo "   /usr/local/bin/gsc"

echo
echo "Try creating a file anywhere and running: gsc file.gscript"
