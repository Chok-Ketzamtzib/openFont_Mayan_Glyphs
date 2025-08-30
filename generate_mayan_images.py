#!/usr/bin/env python3
"""
Script to help generate Mayan glyph images from the MayaPS TeX package.
This creates sample LaTeX files that you can compile to generate PNG images.
"""

import os

# Create the LaTeX files directory
os.makedirs("latex_glyphs", exist_ok=True)

# Sample Mayan day signs that might be available in the MayaPS fonts
mayan_glyphs = [
    ("ahau", "\\textmaya{A}"),       # Ahau - Lord/Ruler
    ("kan", "\\textmaya{K}"),        # Kan - Corn/Yellow
    ("muluk", "\\textmaya{M}"),      # Muluk - Water
    ("ok", "\\textmaya{O}"),         # Ok - Dog
    ("chuen", "\\textmaya{C}"),      # Chuen - Monkey
    ("eb", "\\textmaya{E}"),         # Eb - Road
    ("ben", "\\textmaya{B}"),        # Ben - Reed
    ("ix", "\\textmaya{I}"),         # Ix - Jaguar
    ("men", "\\textmaya{N}"),        # Men - Eagle
    ("cib", "\\textmaya{V}"),        # Cib - Vulture
    ("caban", "\\textmaya{H}"),      # Caban - Earth
    ("etznab", "\\textmaya{Z}"),     # Etznab - Flint
    ("cauac", "\\textmaya{U}"),      # Cauac - Storm
    ("imix", "\\textmaya{X}"),       # Imix - Earth Monster
]

# Base LaTeX template for MayaPS system
latex_template = """\\documentclass{{article}}
\\input{{mayaps.tex}}
\\begin{{document}}
\\pagestyle{{empty}}
{glyph_command}
\\end{{document}}
"""

# Generate individual LaTeX files for each glyph
for name, command in mayan_glyphs:
    filename = f"latex_glyphs/{name}.tex"
    with open(filename, 'w') as f:
        f.write(latex_template.format(glyph_command=command))
    print(f"Created {filename}")

# Create a compilation script

"""

compile_script = #!/bin/bash
# Script to compile LaTeX files to PNG images
# Make sure you have pdflatex and ImageMagick (convert) installed

echo "Compiling Mayan glyphs to images..."

cd latex_glyphs

for tex_file in *.tex; do
    base_name=$(basename "$tex_file" .tex)
    echo "Processing $base_name..."
    
    # Compile LaTeX to PDF
    pdflatex -interaction=nonstopmode "$tex_file" > /dev/null 2>&1
    
    # Convert PDF to PNG
    if [ -f "${base_name}.pdf" ]; then
        convert -density 300 "${base_name}.pdf" -quality 90 -background white -alpha remove "${base_name}.png"
        echo "Created ${base_name}.png"
        
        # Clean up intermediate files
        rm -f "${base_name}.pdf" "${base_name}.aux" "${base_name}.log"
    else
        echo "Failed to create PDF for $base_name"
    fi
done

echo "Done! PNG files created in latex_glyphs directory."
echo "Copy the PNG files to your openFrameworks bin/data/mayan_glyphs/ directory."


with open("compile_glyphs.sh", 'w') as f:
    f.write(compile_script)

os.chmod("compile_glyphs.sh", 0o755)

print("\nFiles created:")
print("- latex_glyphs/ directory with individual .tex files")
print("- compile_glyphs.sh script to generate PNG images")
print("\nTo generate actual Mayan glyph images:")
print("1. Make sure you have LaTeX and ImageMagick installed")
print("2. Copy your mayaps.sty file to the latex_glyphs directory")
print("3. Run: ./compile_glyphs.sh")
print("4. Copy the generated PNG files to bin/data/mayan_glyphs/")

"""