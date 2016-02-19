# ofxTSNE

ofxTSNE is an [addon](https://www.ofxaddons.com) for [openframeworks](https://www.openframeworks.cc) which wraps the [t-SNE](https://lvdmaaten.github.io/tsne/) (t-Distributed Stochastic Neighbor Embedding) algorithm by [Laurens van der Maaten](https://lvdmaaten.github.io). 

t-SNE is a technique for reducing the dimensionality of large, high-dimension datasets, typically to 2 or 3 dimensions. It has a similar function to [Principal Component Analysis](https://en.wikipedia.org/wiki/Principal_component_analysis) (see [ofxPCA](https://github.com/atduskgreg/ofxPCA)) which reduces a dataset's dimensionality by reorienting it along its principal axes, but differs in that it tends to better preserve point-wise distances, making it more suitable for visualization of high-dimensional data.

ofxTSNE is very simple to run, containing only one function. The harder part is getting data.

### Examples

#### basic example

![t-SNE toy data](http://www.genekogan.com/images/misc/ofxTsne1.jpg)

`example` demonstrates how to use ofxTSNE by constructing a toy 100-dim dataset. It contains comments explaining what the parameters do and how to set them.

**clever hack**: try setting D=3 and instead of making points clustered around 10 centers, make the points random 3d points and map the point's color linearly from its 3d position. 

#### clustering images

![t-SNE images from Caltech-256](http://www.genekogan.com/images/misc/ofxTsne2.jpg)

`example-images` applies t-SNE to a directory of images. It uses [ofxCcv](https://www.github.com/kylemcdonald/ofxCcv) to encode each image as a compact (4096-dim) feature vector derived from a trained convolutional neural network. The resulting representation captures high-level similarities among images, enabling ofxTSNE to group them effectively according more to content (e.g. images of cats get clustered together), relatively invariant to changes in color, lighting, position, etc. 

To run this example, you need to take a few extra steps.

1) Get [ofxCcv](https://www.github.com/kylemcdonald/ofxCcv)
	
2) run the setup_ccv script to download the trained convnet.

	sh setup_ccv.sh

3) Then you need to populate a folder called 'images' inside your data folder. Be careful to use small-sized images because the entire directory will be loaded into memory. I've provided a script which downloads 20 images each from 31 categories in [Caltech-256](www.vision.caltech.edu/Image_Datasets/Caltech256/images/). If you'd like to download those, run:

	python download_images.py
	
Or if you want to download a set of animals from the same source, open `download_images.py` and change the line `categories = categories_random` to `categories = categories_animals`. 


#### gridding images 

`example-imagesGrid` is exactly as above but adds an extra step of assigning the t-SNE points to a grid and saving the output (as in below, [see here for high-res](https://www.flickr.com/photos/genekogan/24873243915/in/dateposted-public/)), using [ofxAssignment](https://github.com/kylemcdonald/ofxAssignment).

![t-SNE animals grid](https://c2.staticflickr.com/2/1511/24873243915_dd5220e41c_k.jpg)