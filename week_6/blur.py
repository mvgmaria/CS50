from PIL import Image, ImageFilter #python image library

before = Image.open("bridg.bmp")
after = before.filter(ImageFilter.BoxBlur(10))
after.save("out.bmp")
