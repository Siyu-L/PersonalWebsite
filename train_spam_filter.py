import pickle
from SpamFilter.spamfilter import SpamFilter
from pathlib import Path


BASE_DIR = Path(__file__).resolve().parent
DATA_DIR = BASE_DIR/"SpamFilter"/"training_data"

def main():
    spam_filter = SpamFilter(
        ham_dir = str(DATA_DIR/"train"/"ham"),
        spam_dir = str(DATA_DIR/"train"/"spam"),
        smoothing = 1e-5
    )
    with open("spam_filter.pkl", "wb") as f:
        pickle.dump(spam_filter, f)

    print("Training complete.")

if __name__ == "__main__":
    main()