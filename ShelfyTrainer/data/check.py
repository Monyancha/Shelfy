
import subprocess

CLASSIFIER_ID = 'beer_bottles_926855367'
API_KEY = '2f0f22f256565390733a5c2db81a712396c13f5b'

def run():
    print "Checking classifier status..."
    subprocess.call([
        "curl", "-X", "GET",
        "https://gateway-a.watsonplatform.net/visual-recognition/api/v3/classifiers/%s?api_key=%s&version=2016-05-20" % (CLASSIFIER_ID, API_KEY)])

if __name__=='__main__':
    run()
