#!/usr/bin/env python3
"""
Script to download Mayan day sign hieroglyphs from various sources.
This downloads the 14 main Mayan day signs that our app uses.
"""

import os
import urllib.request
import ssl

# Create SSL context that doesn't verify certificates (for some older sites)
ssl_context = ssl.create_default_context()
ssl_context.check_hostname = False
ssl_context.verify_mode = ssl.CERT_NONE

# Directory to save images
output_dir = "bin/data/mayan_glyphs"
os.makedirs(output_dir, exist_ok=True)

# Mayan day signs and their corresponding Wikimedia Commons URLs
mayan_day_signs = {
    "ahau": "https://upload.wikimedia.org/wikipedia/commons/thumb/c/c6/Maya-g-log-cal-D01-Ahau.png/64px-Maya-g-log-cal-D01-Ahau.png",
    "kan": "https://upload.wikimedia.org/wikipedia/commons/thumb/a/a7/Maya-g-log-cal-D04-Kan.png/64px-Maya-g-log-cal-D04-Kan.png",
    "muluk": "https://upload.wikimedia.org/wikipedia/commons/thumb/9/9f/Maya-g-log-cal-D09-Muluc.png/64px-Maya-g-log-cal-D09-Muluc.png",
    "ok": "https://upload.wikimedia.org/wikipedia/commons/thumb/f/f3/Maya-g-log-cal-D10-Ok.png/64px-Maya-g-log-cal-D10-Ok.png",
    "chuen": "https://upload.wikimedia.org/wikipedia/commons/thumb/1/1f/Maya-g-log-cal-D11-Chuen.png/64px-Maya-g-log-cal-D11-Chuen.png",
    "eb": "https://upload.wikimedia.org/wikipedia/commons/thumb/8/82/Maya-g-log-cal-D12-Eb.png/64px-Maya-g-log-cal-D12-Eb.png",
    "ben": "https://upload.wikimedia.org/wikipedia/commons/thumb/a/a1/Maya-g-log-cal-D13-Ben.png/64px-Maya-g-log-cal-D13-Ben.png",
    "ix": "https://upload.wikimedia.org/wikipedia/commons/thumb/5/51/Maya-g-log-cal-D14-Ix.png/64px-Maya-g-log-cal-D14-Ix.png",
    "men": "https://upload.wikimedia.org/wikipedia/commons/thumb/d/d7/Maya-g-log-cal-D15-Men.png/64px-Maya-g-log-cal-D15-Men.png",
    "cib": "https://upload.wikimedia.org/wikipedia/commons/thumb/7/74/Maya-g-log-cal-D16-Cib.png/64px-Maya-g-log-cal-D16-Cib.png",
    "caban": "https://upload.wikimedia.org/wikipedia/commons/thumb/e/ec/Maya-g-log-cal-D17-Caban.png/64px-Maya-g-log-cal-D17-Caban.png",
    "etznab": "https://upload.wikimedia.org/wikipedia/commons/thumb/2/2a/Maya-g-log-cal-D18-Etznab.png/64px-Maya-g-log-cal-D18-Etznab.png",
    "cauac": "https://upload.wikimedia.org/wikipedia/commons/thumb/d/dc/Maya-g-log-cal-D19-Cauac.png/64px-Maya-g-log-cal-D19-Cauac.png",
    "imix": "https://upload.wikimedia.org/wikipedia/commons/thumb/f/f1/Maya-g-log-cal-D02-Imix.png/64px-Maya-g-log-cal-D02-Imix.png"
}

print("Mayan Hieroglyph Downloader")
print("===========================")
print()
print("Downloading real Mayan day sign images from Wikimedia Commons...")
print(f"Saving to: {output_dir}/")
print()

# Download each image
downloaded_count = 0
failed_count = 0

for name, url in mayan_day_signs.items():
    try:
        filename = os.path.join(output_dir, f"{name}.png")
        print(f"Downloading {name}... ", end="", flush=True)
        
        # Create request with user agent
        request = urllib.request.Request(url)
        request.add_header('User-Agent', 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36')
        
        # Download the image
        with urllib.request.urlopen(request, context=ssl_context) as response:
            image_data = response.read()
        
        # Save the image
        with open(filename, 'wb') as f:
            f.write(image_data)
        
        print("✓ Success")
        downloaded_count += 1
        
    except Exception as e:
        print(f"✗ Failed: {e}")
        failed_count += 1

print()
print("=" * 50)
print("DOWNLOAD SUMMARY")
print("=" * 50)
print(f"✓ Successfully downloaded: {downloaded_count} images")
print(f"✗ Failed downloads: {failed_count} images")
print(f"📁 Images saved to: {output_dir}/")
print()

if downloaded_count > 0:
    print("🎉 Success! You now have real Mayan hieroglyphs!")
    print()
    print("Next steps:")
    print("1. Compile your openFrameworks project: make")
    print("2. Run the app to see the real Mayan glyphs!")
    print("3. Press SPACE to cycle through the hieroglyphs")
    print()
    print("The app will automatically:")
    print("- Load real images where available")
    print("- Fall back to beautiful patterns for missing images")
else:
    print("⚠️ No images were downloaded successfully.")
    print("You can still run the app - it will show beautiful geometric patterns!")
    
print()
print("Mayan Day Signs Downloaded:")
for name in mayan_day_signs.keys():
    filepath = os.path.join(output_dir, f"{name}.png")
    status = "✓" if os.path.exists(filepath) else "✗"
    print(f"  {status} {name}.png")
