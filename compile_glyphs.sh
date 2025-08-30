#!/bin/bash
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
