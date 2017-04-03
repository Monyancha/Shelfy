#!/usr/bin/env python
# 
# The MIT License (MIT)
# Copyright (c) 2016 Saj Arora
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy 
# of this software and associated documentation files (the "Software"), to 
# deal in the Software without restriction, including without limitation the 
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
# copies of the Software, and to permit persons to whom the Software is furnished to 
# do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all 
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
# INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
# PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
# CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR 
# THE USE OR OTHER DEALINGS IN THE SOFTWARE.

"""
Project: 
Author: Saj Arora
Description: 
"""
import json
import os
from time import sleep

import requests
import shutil
import subprocess
import algorithm

from os.path import isfile, join
from watson_developer_cloud import VisualRecognitionV3
visual_recognition = VisualRecognitionV3('2016-05-20', api_key='2f0f22f256565390733a5c2db81a712396c13f5b')


dir_path = os.path.dirname(os.path.realpath(__file__))
shelfyDetector = os.path.join(dir_path, "..", "ShelfyDetector", "bin", "ShelfyDetector")
image = os.path.join(dir_path, "image.jpg")
params = os.path.join(dir_path, "params.json")
output = os.path.join(dir_path, "result")


classifier_id = "beer_bottles_926855367"


def run():
    print "Starting server..."
    while (True):
        cleanOutputDir()
        dataset = {}
        print "Capturing image..."
        r = requests.get('http://10.0.150.149:5000/getImage', stream=True)
        if r.status_code == 200:
            with open('./image.jpg', 'wb') as f:
                for chunk in r.iter_content(4024):
                    f.write(chunk)
        print 'Image updated from server...Processing.'
        # # call the c++ program
        result = subprocess.call([shelfyDetector, image, output])
        if (int(result) == 2):
            files = [(join(output, f)) for f in os.listdir(output) if isfile(join(output, f))]
            for file in files:
                beer, confidence = classifyImage(file, dataset)
                print beer, confidence

        algorithm.run(dataset)
        sleep(2)

def cleanOutputDir():
    print "Clean previous dataset..."
    [os.unlink(join(output, f)) for f in os.listdir(output) if isfile(join(output, f))]

def classifyImage(imagePath, dataset):
    with open(imagePath) as f:
        result = (visual_recognition.classify(
            images_file=f, classifier_ids=[classifier_id]))
    return processResult(result, dataset)

def processResult(result, dataset):
    beerType = None
    confidence = 0
    imageName = None
    if result and 'images' in result:
        for image in result.get('images'):
            imageName = image.get('image')
            if 'classifiers' in image and len(image.get('classifiers')) > 0:
                beerClassifier = image.get('classifiers')[0]
                if 'classes' in beerClassifier and len(beerClassifier.get('classes')) > 0:
                    beerType = beerClassifier.get('classes')[0].get('class')
                    confidence = beerClassifier.get('classes')[0].get('score')

    if confidence > 0.5:
        if not beerType in dataset:
            dataset[beerType] = []
        dataset[beerType].append(imageName)
    return beerType, confidence



if __name__=='__main__':
    run()