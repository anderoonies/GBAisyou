import sys
import os
from PIL import Image
import jinja2

templateLoader = jinja2.FileSystemLoader(searchpath="./")
templateEnv = jinja2.Environment(loader=templateLoader)
TEMPLATE_FILE = "sprite.s.template"
template = templateEnv.get_template(TEMPLATE_FILE)

def rgb_to_hword(rgb):
    print(rgb)
    red = int(rgb[0] / 255 * 31)
    green = int(rgb[1] / 255 * 31)
    blue = int(rgb[2] / 255 * 31)
    # xbbbbbgggggrrrrr
    binary = (
        '0' +
        '{0:05b}'.format(blue) +
        '{0:05b}'.format(green) +
        '{0:05b}'.format(red)
    )
    return '{0:#06x}'.format(int(binary, 2))

def crop(infile, chunk_height, chunk_width):
    im = Image.open(infile)
    imgwidth, imgheight = im.size
    # hardcoding 2x2. 8x8 tiles for 16x16 images
    for i in range(imgheight//chunk_height):
        for j in range(imgwidth//chunk_width):
            box = (j*chunk_width, i*chunk_height, (j+1)*chunk_width, (i+1)*chunk_height)
            yield im.crop(box)

def convert(file):
    sprite_name = file.split('.')[0]

    colors = []
    word_chunks = []

    for i, chunk in enumerate(crop(file,8,8)):
        words = []
        for row in range(chunk.height):
            word = ''
            for col in range(chunk.width):
                color = chunk.getpixel((col, row))
                if color in colors:
                    index = colors.index(color)
                    word += str(index)
                else:
                    colors.append(color)
                    word += str(len(colors) - 1)
            words.append('0x' + word[::-1])
        word_chunks.append(words)


    with open('{}.s'.format(sprite_name), 'w') as sfile:
        try:
            sfile.write(
                template.render({
                    'name': sprite_name,
                    'chunks': word_chunks,
                    'palette': [rgb_to_hword(c) for c in sorted(colors)]
                })
            )
        except:
            print(sprite_name)

if len(sys.argv) == 1:
    for root, dirs, files in os.walk('./'):
        _ = [convert(f) for f in files if f.endswith('.png')]
else:
    convert(sys.argv[1])