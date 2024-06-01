from flask import Flask, request, render_template, jsonify
from flask_debugtoolbar import DebugToolbarExtension
from flask_cors import CORS


app = Flask(__name__)

app.debug = True
app.secret_key = "1"
DebugToolbarExtension(app)
CORS(app)


shared_data = {}


@app.route("/api/hello", methods=["POST", "GET"])
def hello():
    global shared_data
    data = request.get_json()
    value = data.get("value")
    shared_data["value"] = value
    print(data)
    return jsonify({"message": "Data received", "data": value})


@app.route("/api/get", methods=["GET"])
def get():
    global shared_data
    return jsonify(shared_data)


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
