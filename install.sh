# #!/bin/bash
# set -e

# echo "🔨 Building GScript..."
# make

# echo "⬆️  Installing binaries (may ask for sudo password)..."
# sudo cp build/gscript /usr/local/bin/gscript
# sudo cp gscript-run /usr/local/bin/gsc

# # Check for nasm
# if ! command -v nasm &> /dev/null
# then
#     echo "⚠️ WARNING: 'nasm' not found. Please install nasm:"
#     echo "  Ubuntu: sudo apt install nasm"
#     echo "  macOS (with Homebrew): brew install nasm"
# fi

# # Check for ld
# if ! command -v ld &> /dev/null
# then
#     echo "⚠️ WARNING: 'ld' not found. Please install binutils or build-essential."
# fi

# echo "✅ Installed as:"
# echo "   /usr/local/bin/gscript"
# echo "   /usr/local/bin/gsc"

# echo
# echo "Try creating a file anywhere and running: gsc file.gscript"

#!/bin/bash
set -e

# Function to try installing a package, fallback to message
try_install() {
    local pkg=$1
    echo "Checking for $pkg..."

    if ! command -v $pkg &> /dev/null; then
        echo "$pkg not found. Trying to install..."

        if [[ "$OSTYPE" == "linux-gnu"* ]]; then
            if command -v apt-get &> /dev/null; then
                sudo apt-get update
                sudo apt-get install -y $pkg || {
                    echo "Failed to install $pkg automatically."
                    echo "Please install $pkg manually, e.g. sudo apt-get install $pkg"
                    exit 1
                }
            elif command -v yum &> /dev/null; then
                sudo yum install -y $pkg || {
                    echo "Failed to install $pkg automatically."
                    echo "Please install $pkg manually, e.g. sudo yum install $pkg"
                    exit 1
                }
            else
                echo "Unsupported Linux package manager. Please install $pkg manually."
                exit 1
            fi
        elif [[ "$OSTYPE" == "darwin"* ]]; then
            if command -v brew &> /dev/null; then
                brew install $pkg || {
                    echo "Failed to install $pkg automatically."
                    echo "Please install $pkg manually, e.g. brew install $pkg"
                    exit 1
                }
            else
                echo "Homebrew not detected. Please install Homebrew and then install $pkg."
                exit 1
            fi
        else
            echo "Unsupported OS. Please install $pkg manually."
            exit 1
        fi

    else
        echo "$pkg is already installed."
    fi
}

try_install nasm
try_install ld # Note: ld usually bundled; you might want to check build tools instead.

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

