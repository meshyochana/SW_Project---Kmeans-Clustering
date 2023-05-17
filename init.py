import sys

def main():
    k = 0
    iter = 200
    n = 0
    d = 0
    points = []
    centroids = []
    centroids_index = []
    # if len(sys.argv) == 1:
    #     print("An Error Has Occurred")
    #     sys.exit()
    # # len(sys.argv) > 1:
    # try:
    #     k = int(sys.argv[1])
    # except ValueError:
    #     print("An Error Has Occurred")
    #     sys.exit()
    # if len(sys.argv) == 3:
    #     file_name = sys.argv[2]
    # elif len(sys.argv) == 4:
    #     try:
    #         iter = int(sys.argv[2]) # iter is the second arg
    #         file_name = sys.argv[3]
    #     except ValueError:
    #         print("An Error Has Occurred")
    #         sys.exit()
    # ------------------- for debug only: ----------------------
    file_name = "input_1.txt"
    # ----------------------------------------------------------
    # Open the file in read mode and load data to points
    with open(file_name, 'r') as file:
        file_contents = file.read()
        vectors = file_contents.split('\n')
        for i in range(len(vectors)-1):
            vector = vectors[i].split(',')
            for j in range(len(vector)):
                vector[j] = float(vector[j])
            points.append(vector)
    # ------------------- important --------------------------
    n = len(points) # add check for valid k and iter values
    d = len(points[0])
    # create centroids:
    for i in range(k):
        point = []
        for j in range(d):
            point.append(points[i][j])
        centroids.append(point)
    centroids_index = [i for i in range(k)]
    print(centroids_index)
    # ------------------------ print data: ---------------------
    print("data:")
    for i in range(len(points)):
        print()
        for j in range(len(points[0])):
            print("%.4f" %points[i][j], end='')
            if j < len(points[0]) - 1:
                print(",", end='')

# Check if this module is being run as the main module
if __name__ == '__main__':
    # Call the main function
    main()