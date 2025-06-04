from PIL import Image, ImageFilter #python image library

before = Image.open("bridg.bmp")
after = before.filter(ImageFilter.FIND_EDGES)
after.save("out.bmp")
