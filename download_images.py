import urllib
import os


root_dir = 'example-images/bin/data/images'
num_images_per_category = 30
categories = [ [2, "american-flag"], [63, "electric-guitar-101"], [56, "dog"], [24, "butterfly"], [15, "bonsai"], [25, "cactus"], [38, "chimp"], [60, "duck"], [53, "desk-globe"], [95, "hamburger"], [195, "soda-can"], [187, "skyscraper"], [150, "octopus"], [152, "owl"], [136, "mandolin"], [127, "laptop-101"], [80, "frog"], [29, "cannon"], [37, "chess-board"], [10, "beer-mug"], [246, "wine-bottle"], [250, "zebra"], [221, "tomato"], [113, "hummingbird"], [91, "grand-piano-101"], [87, "goldfish"], [86, "golden-gate-bridge"], [81, "frying-pan"], [57, "dolphin-101"], [46, "computer-monitor"], [22, "buddha-101"] ]




cmd = 'mkdir %s' % root_dir
os.system(cmd)

url_root = 'http://www.vision.caltech.edu/Image_Datasets/Caltech256/images/'
for c in categories:
	for i in range(21,31):#range(1,num_images_per_category+1):
		path = 'http://www.vision.caltech.edu/Image_Datasets/Caltech256/images/%03d.%s/%03d_%04d.jpg' % (c[0], c[1], c[0], i)
		print "download %s"%path
		urllib.urlretrieve(path, "%s/%s-%04d.jpg " % (root_dir, c[1], i))






