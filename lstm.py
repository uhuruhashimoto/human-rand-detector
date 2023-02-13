# LSTM from https://machinelearningmastery.com/time-series-prediction-lstm-recurrent-neural-networks-python-keras/
# Model code (configured) from https://github.com/ekzhang/char-rnn-keras/blob/master/model.py
# And https://medium.com/@dclengacher/keras-lstm-recurrent-neural-networks-c1f5febde03d
import os
import numpy as np
import tensorflow as tf
from tensorflow import keras
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import LSTM
from keras.layers import Activation
import matplotlib.pyplot as plt

MODEL_DIR = './model'

def save_weights(epoch, model):
    if not os.path.exists(MODEL_DIR):
        os.makedirs(MODEL_DIR)
    model.save_weights(os.path.join(MODEL_DIR, 'weights.{}.h5'.format(epoch)))

def load_weights(epoch, model):
    model.load_weights(os.path.join(MODEL_DIR, 'weights.{}.h5'.format(epoch)))


def char_to_int(c) -> int:
    if c == '1':
        return 1
    else:
        return 0

# This gives us a 30 x 1000 array of 1s and 0s (30 strings)
# and a 30 x 1 array of labels (0 or 1)
def read_data_from_csv():
    int_arr = np.ndarray(shape=(30, 1000), dtype=int)
    int_labels = []
    arr = np.loadtxt("labeled_data/training.csv",
                 delimiter=",", dtype=str)
    labels = np.loadtxt("labeled_data/labels.csv",
                    delimiter=",", dtype=str)
    # Convert labels to integers
    for i in range(len(labels)):
        int_labels.append(char_to_int(labels[i]))
    int_labels = np.asarray(int_labels)
    for i in range(len(arr)):
        for j in range(len(arr[i])):
            int_arr[i][j] = char_to_int(arr[i][j])
    return int_labels, int_arr

def load_final_data():
    int_arr = np.ndarray(shape=(50, 1000), dtype=int)
    arr = np.loadtxt("unlabeled_data/final.csv",
                 delimiter=",", dtype=str)
    for i in range(len(arr)):
        for j in range(len(arr[i])):
            int_arr[i][j] = char_to_int(arr[i][j])
    return int_arr


if __name__ == '__main__':
    labels, data = read_data_from_csv()
    model = Sequential()
    model.add(LSTM(8,input_shape=(1000,1),return_sequences=False))#True = many to many
    model.add(Dense(2, kernel_initializer='normal', activation='linear'))
    model.add(Dense(1,kernel_initializer='normal',activation='linear'))
    model.compile(loss='mse',optimizer ='adam',metrics=['accuracy'])
    print("Training model...")
    model.fit(data,labels,epochs=2000,batch_size=1000,validation_split=0.05,verbose=0)
    print("Evaluating model...")
    scores = model.evaluate(data,labels,verbose=1,batch_size=1000)
    print('Accuracy: {}'.format(scores[1]))
    predict=model.predict(data)
    plt.plot(labels, predict-labels, 'C2')
    plt.ylim(ymax = 3, ymin = -3)
    plt.show()

    # Now we load the final data and predict
    final_data = load_final_data()
    print("Predicting final data...")
    predict=model.predict(final_data)
    print(predict)