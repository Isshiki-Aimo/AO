from get_data import *


def init_center(train_data, k):
    """
    Initialize the center of k clusters
    """
    data_len = len(train_data)
    choose_index = np.random.choice(data_len, k, replace=False)
    point_center = []
    for i in choose_index:
        point_center.append(train_data[i])
    point_center = np.array(point_center)
    return point_center


def compute_distance(point_matrix, point_center):
    """
    Compute the distance between point and center
    """
    distance = np.zeros((len(point_matrix), len(point_center)), dtype=np.float)
    for i in range(len(point_matrix)):
        for j in range(len(point_center)):
            distance[i][j] = np.linalg.norm(point_matrix[i] - point_center[j])
    return distance


def get_each_class_num(cluster, class_num):
    """
    Get the number of each class
    """
    each_class_num = np.zeros(class_num, dtype=np.int)
    for i in range(len(cluster)):
        each_class_num[cluster[i]] += 1
    return each_class_num


def get_each_class_distance(distance, cluster, class_num, each_class_num):
    """
    Get the distance of each class
    """
    each_class_distance = np.zeros((1, class_num), dtype=np.float)
    for i in range(len(distance)):
        each_class_distance[0][cluster[i]] += distance[i][cluster[i]]
    return each_class_distance


def get_cluster(distance):
    """
    Get the cluster of each point
    """
    cluster = np.argmin(distance, axis=1)
    return cluster


def compute_center(point_matrix, cluster, k):
    """
    Compute the center of each cluster
    """
    center = np.zeros((k, len(point_matrix[0])), dtype=np.float)
    dict = {}
    for i in range(len(cluster)):
        center[cluster[i]] += point_matrix[i]
        if cluster[i] not in dict.keys():
            dict[cluster[i]] = 1
        else:
            dict[cluster[i]] += 1
    for i in range(k):
        center[i] /= dict[i]
    return center


def val_cluster(cluster, true_label):
    """
    Compute the error of each cluster
    """
    error = 0
    for i in range(len(cluster)):
        if cluster[i] != true_label[i]:
            error += 1
    return error / len(cluster)


def get_true_label(distance, label_dict, label, cluster, K):
    """
    Get the true label of each point
    :param distance:距离矩阵
    :param label_dict:标签字典
    :param label:K聚类的标签
    :param cluster:每个点的簇
    :return:根据真实标签分类将K聚类标签划分为真实标签
    """
    change_dict = {}
    for i in range(len(label_dict)):
        K_length = []
        for j in range(len(distance)):
            K_length.append(distance[j][i])
        # 获取最近的K个点的索引
        k_index = []
        for k in range(K):
            k_index.append(K_length.index(min(K_length)))
            K_length.pop(k_index[k])
        # 获取K个点的真实标签
        true_lable = []
        for l in k_index:
            true_lable.append(label[l])
        # 最近K个点的类别即为该点的类别
        tag = max(set(true_lable), key=true_lable.count)
        change_dict[i] = tag
    # 将K聚类标签划分为真实标签
    for i in range(len(cluster)):
        cluster[i] = change_dict[cluster[i]]
    return cluster


if __name__ == '__main__':
    np.random.seed(8)
    data, label, label_dict = get_my_data("balance-scale.txt")
    data_matrix = get_data_matrix(data)
    center = init_center(data_matrix, 3)
    for i in range(100):
        distance = compute_distance(data_matrix, center)
        cluster = get_cluster(distance)
        next_center = compute_center(data_matrix, cluster, 3)
        if np.linalg.norm(next_center - center) < 0.001:
            break
        center = compute_center(data_matrix, cluster, 3)
    true_lable = get_true_label(distance, label_dict.keys(), label, cluster, 3)
    error = val_cluster(cluster, label)
    print("The error of K-means is:", error)
