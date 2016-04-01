import urllib.request
import os
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("-s", "--dataset", type=str, default="random", help="random, animals, or both")
parser.add_argument("-d", "--dir", type=str, help="add directory (inside bin/data/images/)")
parser.add_argument("-n", "--num", type=int, help="number of images to download for each category")
args = parser.parse_args()



categories_random = [ [2, "american-flag"], [63, "electric-guitar-101"], [56, "dog"], [24, "butterfly"], [15, "bonsai-101"], [25, "cactus"], [38, "chimp"], [60, "duck"], [53, "desk-globe"], [95, "hamburger"], [195, "soda-can"], [187, "skyscraper"], [150, "octopus"], [152, "owl"], [136, "mandolin"], [127, "laptop-101"], [80, "frog"], [29, "cannon"], [37, "chess-board"], [10, "beer-mug"], [246, "wine-bottle"], [250, "zebra"], [221, "tomato"], [113, "hummingbird"], [91, "grand-piano-101"], [87, "goldfish"], [86, "golden-gate-bridge"], [81, "frying-pan"], [57, "dolphin-101"], [46, "computer-monitor"], [22, "buddha-101"] ]

categories_animals = [ [7, "bat"], [9, "bear"], [15, "bonsai-101"], [24, "butterfly"], [25, "cactus"], [28, "camel"], [34, "centipede"], [38, "chimp"], [40, "cockroach"], [48, "conch"], [52, "crab-101"], [56, "dog"], [57, "dolphin-101"], [60, "duck"], [64, "elephant-101"], [65, "elk"], [68, "fern"], [80, "frog"], [84, "giraffe"], [85, "goat"], [89, "goose"], [90, "gorilla"], [93, "grasshopper"], [100, "hawksbill-101"], [103, "hibiscus"], [105, "horse"], [106, "horseshoe-crab"], [111, "house-fly"], [116, "iguana"], [113, "hummingbird"], [114, "ibis-101"], [118, "iris"], [124, "killer-whale"], [121, "kangaroo-101"], [134, "llama-101"], [147, "mushroom"], [150, "octopus"], [151, "ostrich"], [152, "owl"], [158, "penguin"], [164, "porcupine"], [166, "praying-mantis"], [168, "raccoon"], [179, "scorpion-101"], [186, "skunk"], [190, "snake"], [189, "snail"], [198, "spider"], [201, "starfish-101"], [204, "sunflower-101"], [207, "swan"], [254, "greyhound"], [230, "trilobite-101"], [236, "unicorn"], [250, "zebra"], [256, "toad"], [228, "triceratops"] ]



# set parameters manually

categories = categories_random
num_images_per_category = 40
root_dir = 'example-images/bin/data/images'

# or use command line arguments
if args.dataset == "random":
	categories = categories_random
elif args.dataset == "animals":
	categories = categories_animals
elif args.dataset == "both":
	categories = categories_random + categories_animals

if args.num:
	num_images_per_category = args.num

if args.dir:
	os.system('mkdir %s' % root_dir)
	root_dir += '/' + args.dir


#run
cmd = 'mkdir %s' % root_dir
os.system(cmd)
url_root = 'http://www.vision.caltech.edu/Image_Datasets/Caltech256/images/'
for c in categories:
	for i in range(1,num_images_per_category+1):
		path = 'http://www.vision.caltech.edu/Image_Datasets/Caltech256/images/%03d.%s/%03d_%04d.jpg' % (c[0], c[1], c[0], i)
		print ("download %s" % path)
		try: urllib.request.urlretrieve(path, "%s/%s-%04d.jpg " % (root_dir, c[1], i))
		except urllib.error.URLError as e:
			print(e.reason)


