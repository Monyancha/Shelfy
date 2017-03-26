import subprocess

from flask import Flask
from flask import send_from_directory

app = Flask(__name__)

@app.route('/getImage')
def send_image():
    result_success = subprocess.check_output(
        ["raspistill -o ./images/photo.jpg --timeout 1"], shell=True)
    return send_from_directory('./images/', 'photo.jpg')


if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True)
