#!/usr/bin/env python3
"""
Create sample Mayan glyph images for testing.
This creates simple vector-style images as placeholders.
"""

from PIL import Image, ImageDraw
import os

# Create output directory
output_dir = "bin/data/mayan_glyphs"
os.makedirs(output_dir, exist_ok=True)

def create_glyph_image(name, drawing_function, size=128):
    """Create a glyph image with the given drawing function."""
    # Create image with transparent background
    img = Image.new('RGBA', (size, size), (0, 0, 0, 0))
    draw = ImageDraw.Draw(img)
    
    # Call the drawing function
    drawing_function(draw, size)
    
    # Save image
    filename = os.path.join(output_dir, f"{name}.png")
    img.save(filename, "PNG")
    print(f"Created {filename}")

def draw_ahau(draw, size):
    """Draw Ahau (Lord) - face with distinctive features"""
    center = size // 2
    # Outer circle (face)
    draw.ellipse([size//4, size//4, 3*size//4, 3*size//4], outline='black', width=3, fill='black')
    # Inner features
    # Eyes
    draw.ellipse([center-20, center-15, center-10, center-5], fill='white')
    draw.ellipse([center+10, center-15, center+20, center-5], fill='white')
    # Nose
    draw.line([center, center-5, center, center+5], fill='white', width=2)
    # Mouth
    draw.arc([center-15, center+5, center+15, center+25], 0, 180, fill='white', width=2)

def draw_kan(draw, size):
    """Draw Kan (Corn) - corn kernel pattern"""
    center = size // 2
    # Draw corn shape
    draw.ellipse([center-25, size//4, center+25, 3*size//4], outline='black', width=3, fill='black')
    # Corn kernels (dots)
    for y in range(center-20, center+20, 8):
        for x in range(center-15, center+15, 8):
            if (x-center)**2 + (y-center)**2 < 400:  # Only inside oval
                draw.ellipse([x-2, y-2, x+2, y+2], fill='white')

def draw_muluk(draw, size):
    """Draw Muluk (Water) - water drop"""
    center = size // 2
    # Water drop shape
    points = [
        (center, size//4),
        (center-20, center),
        (center-15, center+20),
        (center, 3*size//4),
        (center+15, center+20),
        (center+20, center)
    ]
    draw.polygon(points, outline='black', width=3, fill='black')
    # Inner ripples
    draw.arc([center-10, center-5, center+10, center+15], 0, 180, fill='white', width=2)

def draw_ok(draw, size):
    """Draw Ok (Dog) - dog head"""
    center = size // 2
    # Head outline
    draw.ellipse([center-25, center-20, center+25, center+30], outline='black', width=3, fill='black')
    # Ears
    draw.ellipse([center-30, center-25, center-15, center-5], outline='black', width=2, fill='black')
    draw.ellipse([center+15, center-25, center+30, center-5], outline='black', width=2, fill='black')
    # Eyes and nose
    draw.ellipse([center-10, center-5, center-5, center+5], fill='white')
    draw.ellipse([center+5, center-5, center+10, center+5], fill='white')
    draw.ellipse([center-3, center+8, center+3, center+15], fill='white')

def draw_chuen(draw, size):
    """Draw Chuen (Monkey) - monkey face"""
    center = size // 2
    # Face
    draw.ellipse([center-25, center-25, center+25, center+25], outline='black', width=3, fill='black')
    # Large eyes
    draw.ellipse([center-15, center-10, center-5, center+5], fill='white')
    draw.ellipse([center+5, center-10, center+15, center+5], fill='white')
    # Small pupils
    draw.ellipse([center-8, center-3, center-7, center+2], fill='black')
    draw.ellipse([center+7, center-3, center+8, center+2], fill='black')

# Create all sample glyphs
glyphs = [
    ("ahau", draw_ahau),
    ("kan", draw_kan),
    ("muluk", draw_muluk),
    ("ok", draw_ok),
    ("chuen", draw_chuen),
]

print("Creating sample Mayan glyph images...")
for name, draw_func in glyphs:
    create_glyph_image(name, draw_func)

print(f"\nCreated {len(glyphs)} sample images in {output_dir}/")
print("These are simple examples - you can replace them with better images from:")
print("- Wikimedia Commons")
print("- Academic sources")
print("- Archaeological references")
print("\nRun your openFrameworks app to see the mixed real/pattern display!")
