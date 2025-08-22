from flask import Flask, request, jsonify
import SpamFilter

app = Flask(__name__)
spam_filter = SpamFilter.SpamFilter(
    ham_dir = "SpamFilter\training_data\train\ham",
    spam_dir = "SpamFilter\training_data\train\spam",
    smoothing = 1e-5
)


@app.route("/classify_text", methods=["POST"])
def classify_text():
    data = request.get_json()
    text = data.get("text", "")
    prediction = spam_filter.is_spam(text)
    indicate_spam = spam_filter.most_indicative_spam(5)
    indicate_ham = spam_filter.most_indicative_ham(5)
    return jsonify({"prediction": prediction, 
                    "indicate spam": indicate_spam, 
                    "indicate ham": indicate_ham })


@app.route("/classify_file", methods=["POST"])
def classify_file():
    if "file" not in request.files:
        return jsonify({"error": "No file provided"}), 400
    
    file = request.files["file"]
    prediction = spam_filter.is_spam(file)
    indicate_spam = spam_filter.most_indicative_spam(5)
    indicate_ham = spam_filter.most_indicative_ham(5)    
    return jsonify({"prediction": prediction, 
                    "indicate spam": indicate_spam, 
                    "indicate ham": indicate_ham })


if __name__ == "__main__":
    app.run(debug=True)
    