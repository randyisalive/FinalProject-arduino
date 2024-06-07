from flask import Flask, request, render_template, jsonify
from flask_debugtoolbar import DebugToolbarExtension
from flask_cors import CORS


app = Flask(__name__)

app.debug = True
app.secret_key = "1"
DebugToolbarExtension(app)
CORS(app)


shared_data = {"threshold": 50}


@app.route("/api/hello", methods=["POST", "GET"])
def hello():
    global shared_data
    data = request.get_json()
    value = data.get("value")
    shared_data["value"] = value
    print(data)
    return jsonify({"message": "Data received", "data": value})


# getting the data
@app.route("/api/get", methods=["GET"])
def get():
    global shared_data
    return jsonify(shared_data)


@app.route("/api/send_threshold", methods=["POST", "GET"])
def send_threshold():
    global shared_data
    data = request.get_json()
    threshold = int(data.get("threshold"))
    shared_data["threshold"] = threshold
    print(shared_data)
    return jsonify({"threshold": threshold})


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
