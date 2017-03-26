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
from pyrebase import pyrebase

test_data = {
    'stella': [
        'image_378_1778.jpg',
        'image_1428_1836.jpg',
    ],
    'shocktop':[
        'image_364_464.jpg',
        'image_1534_576.jpg',
        'image_2716_1900.jpg',
        'image_2720_672.jpg'
    ]
}


firebaseConfig = {
    "apiKey": 'AIzaSyCkER-Uj4lU5EfZq8J-MmNl_J5qlRP7r3Q',
    "authDomain": 'shelfie-cc23e.firebaseapp.com',
    "storageBucket": "shelfie-cc23e.appspot.com",
    "databaseURL": 'https://shelfie-cc23e.firebaseio.com/'
}

firebase = pyrebase.initialize_app(firebaseConfig)

def orderBottles(dataset):
    sorted_by_x = sorted(dataset, key=lambda tup: tup[1])
    top_row = []
    bottom_row = []
    for x in sorted_by_x:
        if x[2] > 1000:
            top_row.append(x)
        else:
            bottom_row.append(x)

    return top_row, bottom_row


def sendToFirebase(top_row, bottom_row):
    data = {
        '0_0': None,
        '0_1': None,
        '0_2': None,
        '1_0': None,
        '1_1': None,
        '1_2': None
    }
    for index, x in enumerate(top_row):
        data['0_' + str(index)] = x[0]

    for index, x in enumerate(bottom_row):
        data['1_' + str(index)] = x[0]
    db = firebase.database()
    db.child("realtime").child("bottles").set(data)


def run(dataset):
    aggregate = []
    for k,v in dataset.iteritems():
        beer = k
        for x in v:
            params = x.split('_')
            x = int(params[1])
            y = int(params[2].split('.')[0])
            aggregate.append((beer, x, y))

    top_row, bottom_row = orderBottles(aggregate)
    sendToFirebase(top_row, bottom_row)