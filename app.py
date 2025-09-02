import pickle
from flask import Flask, request, jsonify, render_template
from SpamFilter.spamfilter import SpamFilter
from tilepuzzle import TilePuzzle
from tilepuzzle import create_tile_puzzle


app = Flask(__name__)
with open("spam_filter.pkl", "rb") as f:
    spam_filter = pickle.load(f)


# Page Rendering

@app.route("/")
def home():
    return render_template("index.html")


@app.route("/python_projects")
def python_projects():
    return render_template("python_projects.html")

# Tile Puzzle

@app.route("/init_board", methods=["POST"])
def init_board():
    data = request.json
    row = data["row"]
    col = data["col"]
    global puzzle 
    puzzle = create_tile_puzzle(row, col)
    return jsonify({"board": puzzle.get_board()})


@app.route("/get_board", methods=["GET"])
def get_board():
    return jsonify({"board": puzzle.get_board()})

@app.route("/move", methods=["POST"])
def move():
    data = request.json
    direction = data["direction"]
    success = puzzle.perform_move(direction)
    return jsonify({"success": success, "board": puzzle.get_board()})

@app.route("/solve_iddfs", methods=["POST"])
def solve_iddfs():
    solution = list(puzzle.find_solutions_iddfs())
    return jsonify({"solution": solution})

@app.route("/solve_a_star", methods=["POST"])
def solve_a_star():
    solution = list(puzzle.find_solution_a_star())
    return jsonify({"solution": solution})


# Spam Filter

@app.route("/classify_text", methods=["POST"])
def classify_text():
    data = request.get_json(silent=True) or {}
    text = data.get("text", "")
    prediction = "Spam" if spam_filter.is_spam(email_path=None, text_input=text) else "Ham"

    return jsonify({"prediction": prediction})


@app.route("/classify_file", methods=["POST"])
def classify_file():
    if "file" not in request.files:
        return jsonify({"error": "No file provided"}), 400
    
    file = request.files.get("file")
    content = file.read().decode("utf-8")
    prediction = "Spam" if spam_filter.is_spam(email_path=None, text_input=content) else "Ham"   
    return jsonify({"prediction": prediction})

@app.route("/indicative_word", methods=["POST"])
def get_indicative_words():
    data = request.get_json(silent=True) or {}
    num = data.get("num", "")
    indicate_spam = spam_filter.most_indicative_spam(num)
    indicate_ham = spam_filter.most_indicative_ham(num)
    return jsonify({"spam_ind": indicate_spam, 
                    "ham_ind": indicate_ham })


if __name__ == "__main__":
    app.run(debug=True)
    