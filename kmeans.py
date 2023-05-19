import math
import sys

iterations = 200
epsilon = 0.001

# read system args and check if valid
def get_sys_args():
    global iterations
    global k
    if len(sys.argv) == 1:
        print("An Error Has Occurred")
        sys.exit()
    # when len(sys.argv) > 1:
    try:
        k = int(sys.argv[1])
    except ValueError:
        try:
            k = float(sys.argv[1])
            print("Invalid number of clusters!")
            sys.exit()
        except ValueError:
            print("An Error Has Occurred")
            sys.exit()
    if len(sys.argv) == 3:
        file_name = sys.argv[2]
    elif len(sys.argv) == 4:
        try:
            iterations = int(sys.argv[2]) # iter is the second arg
            file_name = sys.argv[3]
        except ValueError:
            try:
                k = float(sys.argv[2])
                print("Invalid maximum iteration!")
                sys.exit()
            except ValueError:
                print("An Error Has Occurred")
                sys.exit()
    return file_name

# Open the file in read mode and load data to points
def read_file(file_name, points):
    with open(file_name, 'r') as file:
        file_contents = file.read()
        vectors = file_contents.split('\n')
        for i in range(len(vectors)-1):
            vector = vectors[i].split(',')
            for j in range(len(vector)):
                vector[j] = float(vector[j])
            points.append(vector)
    return

def create_centroids(centroids, points, k, d):
    # create centroids:
    for i in range(k):
        point = []
        for j in range(d):
            point.append(points[i][j])
        centroids.append(point)
    return centroids, points

def print_2d_mat(points):
    #print 2d matrix:
    for i in range(len(points)):
        for j in range(len(points[0])):
            print("%.4f" %points[i][j], end='')
            if j < len(points[0]) - 1:
                print(",", end='')
        print()


def kmeans(points, centroids, n, k, d):
    '''Implement k-means clustering algorithm'''
    
    for i in range(iterations):
        a_i_arr = assign(points, centroids, n, k, d) # a_i_dict := {cluster index : [point indices]}
        delta_c = update(a_i_arr, points, centroids, k, d) # delta_c := maximum distance between the prev. and cur. centroids 
        if convergence(delta_c):
            break


def assign(points, centroids, n, k, d):
    '''Assign every point to the closest cluster'''

    a_i_arr = [[] for i in range(k)]
    for i in range(n):
        min_index = argmin_distance(centroids,points[i], k, d)
        a_i_arr[min_index].append(i) 
    return a_i_arr


def update(a_i_arr, points, centroids, k, d):
    '''Update the centroids' coordinates to be the center of mass of their associated points'''

    delta_c = 0
    for i in range(k):
        length = len(a_i_arr[i])
        if length!=0:
            new_c = [sum([points[a_i_arr[i][j]][m] for j in range(length)])/length for m in range(d)]
            delta_c = max(distance_pp(new_c,centroids[i], d),delta_c)
            centroids[i] = new_c
    return delta_c


def convergence(delta_c):
    '''Check if the condition for convergence is met'''

    if delta_c < epsilon:
        return 1
    return 0


def distance_pp(p1, p2, d):
    '''Calculate the euclidean distance between two points in R^d'''

    return math.sqrt(sum([(p2[i]-p1[i])**2 for i in range(d)]))


def argmin_distance(centroids, p, k, d):
    '''Input: centroids-list of centroids [k*d], p-point in R^d. 
    Maintaining the minimum index from p to the centroids.'''

    min_index = 0
    d_min = distance_pp(centroids[0],p, d)
    for i in range(k):
        d_cur = distance_pp(centroids[i],p, d)
        if d_cur<d_min:
            min_index = i
            d_min = d_cur
    return min_index


def main():
    
    points = []
    centroids = []

    file_name = get_sys_args()

    # ------------------- for debug only - cmd:-----------------
    # python .\kmeans.py 3 100 input_1.txt
    # python .\kmeans.py 7 input_2.txt
    # python .\kmeans.py 15 300 input_3.txt
    # ----------------------------------------------------------    

    read_file(file_name, points)
    
    # check k and iter validity
    n = len(points) 
    d = len(points[0])
    if k<2 or n <= k:
        print("Invalid number of clusters!")
        sys.exit()
    if iterations < 2 or 999 < iterations:
        print("Invalid maximum iteration!")
        sys.exit()

    centroids, points = create_centroids(centroids, points, k, d)

    kmeans(points, centroids, n, k, d)
    print_2d_mat(centroids)

# Check if this module is being run as the main module
if __name__ == '__main__':
    # Call the main function
    main()

     


