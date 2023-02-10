# LSTM from https://machinelearningmastery.com/time-series-prediction-lstm-recurrent-neural-networks-python-keras/
# Model code (configured) from https://github.com/ekzhang/char-rnn-keras/blob/master/model.py
import os
import numpy as np
import tensorflow as tf
from tensorflow import keras
from keras.models import Sequential, load_model
from keras.layers import LSTM, Dropout, TimeDistributed, Dense, Activation, Embedding
import argparse

# These may change with better training data
# parser = argparse.ArgumentParser(description='LSTM')
# parser.add_argument('-n', '--num_chars', type=int, default=1, help='Number of chars in each string')
# parser.add_argument('-l', '--num_lines', type=int, default=1, help='Number of lines (total strings)')
# args = parser.parse_args()

MODEL_DIR = './model'
# TODO: temporary
BATCH_SIZE = 64
SEQ_LENGTH = 50

def save_weights(epoch, model):
    if not os.path.exists(MODEL_DIR):
        os.makedirs(MODEL_DIR)
    model.save_weights(os.path.join(MODEL_DIR, 'weights.{}.h5'.format(epoch)))

def load_weights(epoch, model):
    model.load_weights(os.path.join(MODEL_DIR, 'weights.{}.h5'.format(epoch)))

def build_model(batch_size, seq_len, vocab_size):
    model = Sequential()
    model.add(Embedding(vocab_size, 512, batch_input_shape=(batch_size, seq_len)))
    for i in range(3):
        model.add(LSTM(256, return_sequences=True, stateful=True))
        model.add(Dropout(0.2))

    model.add(TimeDistributed(Dense(vocab_size)))
    model.add(Activation('softmax'))
    return model

def char_to_int(c) -> int:
    if c == '1':
        return 1
    else:
        return 0

def read_batches(T, vocab_size):
    # TODO: configure to read n strings of [1, 0] from csv file
    length = T.shape[0]
    batch_chars = length // BATCH_SIZE

    for start in range(0, batch_chars - SEQ_LENGTH, SEQ_LENGTH):
        X = np.zeros((BATCH_SIZE, SEQ_LENGTH))
        Y = np.zeros((BATCH_SIZE, SEQ_LENGTH, vocab_size))
        for batch_idx in range(0, BATCH_SIZE):
            for i in range(0, SEQ_LENGTH):
                X[batch_idx, i] = T[batch_chars * batch_idx + start + i]
                Y[batch_idx, i, T[batch_chars * batch_idx + start + i + 1]] = 1
        yield X, Y

def train(model, data, epochs=1, batch_size=64, seq_len=50, vocab_size=2):

    model = build_model(batch_size, seq_len, vocab_size)
    model.summary()
    model.compile(loss='categorical_crossentropy',
                  optimizer='adam', metrics=['accuracy'])
    for i in range(epochs):
        print(f"Epoch {i}")
        T = np.asarray([char_to_int[c] for c in text], dtype=np.int32)
        losses, accs = [], []
        for i, (X, Y) in enumerate(read_batches(T, vocab_size)):
            loss, acc = model.train_on_batch(X, Y)
            print('Batch {}: loss = {:.4f}, acc = {:.5f}'.format(i + 1, loss, acc))
            losses.append(loss)
            accs.append(acc)

        model.fit(data, data, batch_size=batch_size, epochs=1)
        save_weights(i, model)

if __name__ == '__main__':
    model = build_model(64, 50, 2)
    model.summary()