import sys

n = 0
k = 0
d = 0
iter = 200

# read system args and check if valid
def get_sys_args():
    global iter
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
            iter = int(sys.argv[2]) # iter is the second arg
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

def create_centroids(centroids):
    # create centroids:
    for i in range(k):
        point = []
        for j in range(d):
            point.append(points[i][j])
        centroids.append(point)
    return

def print_2d_mat(points):
    #print 2d matrix:
    for i in range(len(points)):
        for j in range(len(points[0])):
            print("%.4f" %points[i][j], end='')
            if j < len(points[0]) - 1:
                print(",", end='')
        print()

def main():
    points = []
    centroids = []
    centroids_index = []
    file_name = get_sys_args()
    # file_name = "input_1.txt"
    # k = 3
    # iter = 100
    read_file(file_name, points)

    # ------------------- for debug only: ----------------------
    # file_name = "input_1.txt"
    # ----------------------------------------------------------
    
    # check k and iter validity
    n = len(points) 
    d = len(points[0])
    if k<2 or n <= k:
        print("Invalid number of clusters!")
        sys.exit()
    if iter < 2 or 999 < iter:
        print("Invalid maximum iteration!")
        sys.exit()

    create_centroids(centroids)
    centroids_index = [i for i in range(k)]

    print_2d_mat(points)

# Check if this module is being run as the main module
if __name__ == '__main__':
    # Call the main function
    main()