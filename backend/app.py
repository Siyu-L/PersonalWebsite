from flask import Flask, request, jsonify
import spamfilter

app = Flask(__name__)

@app.route("/classify_text", methods=["POST"])
def classify_text():
    data = request.get_json()
    text = data.get("text", "")
    sf = spamfilter.SpamFilter()
    prediction = sf.is_spam()
    return jsonify({"prediction": prediction})


@app.route("/classify_file", methods=["POST"])
def classify_file():
    if "file" not in request.files:
        return jsonify({"error": "No file provided"}), 400
    
    file = request.files["file"]
    sf = spamfilter.SpamFilter()
    prediction = sf.is_spam(file)
    return jsonify({"prediction": prediction})


if __name__ == "__main__":
    app.run(debug=True)
    