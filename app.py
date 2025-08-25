from pathlib import Path
from flask import Flask, request, jsonify, render_template
from SpamFilter.spamfilter import SpamFilter

BASE_DIR = Path(__file__).resolve().parent
DATA_DIR = BASE_DIR/"SpamFilter"/"training_data"


app = Flask(__name__)
spam_filter = SpamFilter(
    ham_dir = str(DATA_DIR/"train"/"ham"),
    spam_dir = str(DATA_DIR/"train"/"spam"),
    smoothing = 1e-5
)


@app.route("/python_projects")
def python_projects():
    return render_template("python_projects.html")



@app.route("/classify_text", methods=["POST"])
def classify_text():
    data = request.get_json(silent=True) or {}
    text = data.get("text", "")
    prediction = "Spam" if spam_filter.is_spam(email_path=None, text_input=text) else "Ham"
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
    prediction = "Spam" if spam_filter.is_spam(email_path=file, text_input=None) else "Ham"
    indicate_spam = spam_filter.most_indicative_spam(5)
    indicate_ham = spam_filter.most_indicative_ham(5)    
    return jsonify({"prediction": prediction, 
                    "indicate spam": indicate_spam, 
                    "indicate ham": indicate_ham })


@app.route("/")
def home():
    return render_template("index.html")

if __name__ == "__main__":
    app.run(debug=True)
    