#!/bin/bash
set -e

echo "🔨 Building GScript..."
make

echo "⬆️  Installing binaries (may ask for sudo password)..."
sudo cp build/gscript /usr/local/bin/gscript
sudo cp gscript-run /usr/local/bin/gsc

echo "✅ Installed as:"
echo "   /usr/local/bin/gscript"
echo "   /usr/local/bin/gsc"

echo
echo "Try creating a file anywhere and running: gsc file.gscript"
