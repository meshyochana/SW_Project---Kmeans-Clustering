import math

# global variables:
c_arr = [[]] # centroinds array [k*d]
p_arr = [[]] # points array [N*d]
K, N, d = 0, 0, 0


epsilon = 0.001
iterations = 200


def kmeans():
    '''Implement k-means clustering algorithm'''

    global p_arr, c_arr, K, N, d
    
    # to do

    # example:
    p_arr = [[1,2],[3,4],[5,6]]
    c_arr = [[0,0],[1,1]]
    d=2
    N=3
    K=2
    
    for i in range(iterations):
        a_i_dict = assign() # a_i_dict := {cluster index : [point indices]}
        delta_c = update(a_i_dict) # delta_c := maximum distance between the prev. and cur. centroids 
        if convergence(delta_c):
            break


def assign():
    '''Assign every point to the closest cluster'''

    a_i_dict = {i:[] for i in range(K)}
    for i in range(N):
        min_index = argmin_distance(c_arr,p_arr[i])
        a_i_dict[min_index].append(i) # optional: we can use an array instead.
    return a_i_dict


def update(a_i_dict):
    '''Update the centroids' coordinates to be the center of mass of their associated points'''

    delta_c = 0
    for i in range(K):
        length = len(a_i_dict[i])
        if length!=0:
            new_c = [sum([p_arr[a_i_dict[i][j]][m] for j in range(length)])/length for m in range(d)]
            delta_c = max(distance_pp(new_c,c_arr[i]),delta_c)
            c_arr[i] = new_c
    return delta_c


def convergence(delta_c):
    '''Check if the condition for convergence is met'''

    if delta_c < epsilon:
        return 1
    return 0


def distance_pp(p1,p2):
    '''Calculate the euclidean distance between two points in R^d'''

    return math.sqrt(sum([(p2[i]-p1[i])**2 for i in range(d)]))


def argmin_distance(c_arr,p):
    '''Input: c_arr-list of centroids [k*d], p-point in R^d. 
    Maintaining the minimum index from p to the centroids.'''

    min_index = 0
    d_min = distance_pp(c_arr[0],p)
    for i in range(K):
        d_cur = distance_pp(c_arr[i],p)
        if d_cur<d_min:
            min_index = i
            d_min = d_cur
    return min_index



     

