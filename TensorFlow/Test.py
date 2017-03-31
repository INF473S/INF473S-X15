# Some basic tools
import time, os, argparse, io
dir = os.path.dirname(os.path.realpath(__file__))

# Tensorflow and numpy!
#import tensorflow as tf
import numpy as np
    
# Matplotlib, so we can graph our functions
import matplotlib
import matplotlib.pyplot as plt

if __name__ == '__main__': # When we call the script directly ...
	# ... we parse a potentiel --nb_neurons argument 
	parser = argparse.ArgumentParser()
	parser.add_argument("--input", required = True, help = "The file containing sequences and distances")
	args = parser.parse_args()
	
	print('Loading input file ', args.input)
	inputFile = open(args.input, "r")
	
	#read the header
	for i in range (10):
		print(inputFile.readline())	
    