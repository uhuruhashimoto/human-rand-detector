# LSTM from https://machinelearningmastery.com/time-series-prediction-lstm-recurrent-neural-networks-python-keras/
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras.layers import LSTM
from sklearn.preprocessing import MinMaxScaler
from sklearn.metrics import mean_squared_error
import argparse

parser = argparse.ArgumentParser(description='LSTM')
parser.add_argument('-n', '--num_chars', type=int, default=1, help='Number of chars in each string')
args = parser.parse_args()

if __name__ == "__main__":
    print(f"Number of chars in each string: {args.num_chars}")
    n_test_str = 50
    # load the training dataset
    # Train dataset is 10 strings with labels
    # Test set is 50 strings without labels

    # Normalize strings by zero padding
    n_hidden = 4
    rnn_cell = LSTM(n_hidden)