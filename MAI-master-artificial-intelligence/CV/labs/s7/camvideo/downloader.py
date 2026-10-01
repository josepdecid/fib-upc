import os

frames = 150
frames_digits = len(str(frames))

for i in range(frames):
    idx = '0' * (frames_digits - len(str(i))) + str(i)
    url = f'https://im2.ezgif.com/tmp/ezgif-2-1d6342d3f3de-gif-jpg/frame_{idx}_delay-0.1s.jpg'
    os.system(f'wget -O frame_{idx}.jpg {url} -q')
    print(f'Downloaded frame {idx}')