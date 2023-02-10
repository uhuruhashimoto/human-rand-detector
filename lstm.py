# LSTM from https://machinelearningmastery.com/time-series-prediction-lstm-recurrent-neural-networks-python-keras/
import numpy as np
import matplotlib.pyplot as plt
import numpy as np
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers
import argparse

# These may change with better training data
parser = argparse.ArgumentParser(description='LSTM')
parser.add_argument('-n', '--num_chars', type=int, default=1, help='Number of chars in each string')
parser.add_argument('-l', '--num_lines', type=int, default=1, help='Number of lines (total strings)')
args = parser.parse_args()


if __name__ == "__main__":
    print(f"Number of chars in each string: {args.num_chars}")
    print(f"Number of strings: {args.num_lines}")
    train_num = args.num_lines
    train_len = args.num_chars

    # TODO: load the training dataset and labels

    # Used https://www.tensorflow.org/guide/keras/rnn as tutorial
    model = keras.Sequential()
    model.add(layers.Embedding(input_dim=1000, output_dim=64))

    # The output of GRU will be a 3D tensor of shape (batch_size, timesteps, 256)
    model.add(layers.GRU(256, return_sequences=True))

    # The output of SimpleRNN will be a 2D tensor of shape (batch_size, 128)
    model.add(layers.SimpleRNN(128))

    model.add(layers.Dense(10))

    model.summary()