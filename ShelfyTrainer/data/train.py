
import subprocess

API_KEY = '2f0f22f256565390733a5c2db81a712396c13f5b'

def run():
    print "Starting classifier"
    subprocess.call([
        "curl", "-X", "POST",
        "-F", "shocktop_positive_examples=@shock.zip",
        "-F", "stella_positive_examples=@stella.zip",
        "-F", "negative_examples=@neg.zip",
        "-F", "name=beer_bottles",
        "https://gateway-a.watsonplatform.net/visual-recognition/api/v3/classifiers?api_key=%s&version=2016-05-20" % API_KEY
    ])

if __name__=='__main__':
    run()
