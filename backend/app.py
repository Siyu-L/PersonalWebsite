from flask import Flask, request, jsonify
import spamfilter

app = Flask(__name__)
@app.route("/classify", methods=["POST"])
def classify():
    data = request.get_json()
    text = data.get("text", "")
    sf = spamfilter.SpamFilter()
    prediction = sf.is_spam()
    