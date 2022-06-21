import numpy as np


def get_my_data(file_name):
    data = []
    label = []
    label_dict = {}
    f = open(file_name)
    line = f.readline().strip()
    while line:
        line = line.split(",")
        attribute = []
        for i in range(len(line)):
            if i != len(line) - 1:
                attribute.append(float(line[i]))
            if i == len(line) - 1:
                data.append(attribute)
                label.append(line[i])
        line = f.readline().strip()
    tag = 1
    for i in label:
        if i not in label_dict.keys():
            label_dict[i] = tag
            tag += 1
    for i in label:
        label[label.index(i)] = label_dict[i]
    f.close()
    return data, label, label_dict


def get_data_matrix(data):
    data_matrix = np.array(data).reshape(-1, len(data[0]))
    return data_matrix


def find_max_min(data_matrix):
    max_list = []
    min_list = []
    for i in range(len(data_matrix[0])):
        max_list.append(max(data_matrix[:, i]))
        min_list.append(min(data_matrix[:, i]))
    return max_list, min_list




